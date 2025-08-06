#include "client.h"

#include "client/core/menu/menu.h"

#include <Windows.h>
#include <d3d9.h>
#include "valve/cusercmd.h"
#include "valve/entities/player/cs_player.h"
#include "valve/client_state.h"
#include "valve/client_frame_stage.h"

#include "fmt/core.h"

bool client::initialize() {
  g_console.open_console();

  client::g_console.print("initializing interfaces", console_color_white);
  if (!g_interfaces.collect_interfaces())
    return false;

  client::g_console.print("initializing global addresses", console_color_white);
  if (!g_addresses.collect_addresses())
    return false;

  client::g_console.print("initializing atlas", console_color_white);
  if (!g_atlas.initialize())
    return false;

  client::g_console.print("initializing offsets", console_color_white);
  if (!g_offsets.get_offsets())
    return false;

  get_window_handle();

  client::g_console.print("initializing renderer", console_color_white);
  if (!g_render.initialize())
    return false;

  client::g_console.print("initializing input", console_color_white);
  g_render.setup_input();

  client::g_console.print("initializing hooks", console_color_white);
  if (!g_hooks.initialize())
    return false;

  attached = true;
  return true;
}

bool client::should_unload() { return (GetAsyncKeyState(VK_DELETE) & 1); }

void client::unload() {
  g_render.detach_input();
  g_hooks.unload();
  g_render.detach();
  g_console.close_console();
}

void client::get_window_handle() {
  D3DDEVICE_CREATION_PARAMETERS creation_params;

  // get the window handler for renderer and input
  g_interfaces.d3d9_device->GetCreationParameters(&creation_params);

  g_window = creation_params.hFocusWindow;
}

bool client::check_insecure() {
  int     argc;
  LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  if (!argv)
    return false;

  bool insecure = false;
  for (int i = 0; i < argc; ++i) {
    insecure = !wcscmp(argv[i], L"-insecure");

    if (insecure)
      break;
  }

  if (!insecure)
    MessageBoxA(nullptr, "Please add -insecure to your launch options.",
                "Incorrect Launch Options", MB_ICONERROR);

  LocalFree(argv);
  return insecure;
}

void client::on_present() {
  g_render.begin();
  g_drawing.copy_from_intermediary();
  g_drawing.draw();
  menu::present();
  g_render.finish();
}

bool client::get_local_player_global() {
  g_local_player = cs_player_t::get_local_player();

  if (!g_local_player->is_local_player())
    return false;

  return true;
}

void client::on_create_move(usercmd_t* cmd, bool* send_packet) {
  if (!get_local_player_global())
    return;

  g_prediction.update();
  g_prediction.store_old_global_variables();
  g_prediction.start_prediction(cmd);

  g_prediction.finish_prediction();
}

typedef bool(__stdcall* host_should_run_func)();
host_should_run_func host_should_run =
    (host_should_run_func)(client::g_addresses.engine.functions.host_should_run);

void client::on_cl_move() {
  if (!(client::g_interfaces.client_state->signon_state >= 2))
    return;

  if (!host_should_run())
    return;

  bool send_packet = true;
}

void client::on_level_shutdown() { g_local_player = nullptr; }

void client::on_paint() {
  g_drawing.clear_initial();
  g_render.get_view_matrix();

  g_drawing.copy_to_intermediary();
}

void client::on_frame_stage_notify(int stage) {
  switch (stage) {
    case FRAME_NET_UPDATE_POSTDATAUPDATE_START: {
      g_lag_compensation.on_frame_stage_notify();
      break;
    }

    default:
      break;
  }
}