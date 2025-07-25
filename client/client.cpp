#include "client.h"

#include "client/core/menu/menu.h"

#include <Windows.h>
#include <d3d9.h>
#include "valve/cusercmd.h"
#include "valve/client_local_player.h"

#include "valve/tracing/engine_trace.h"
#include "valve/tracing/trace.h"

bool client::initialize() {
  g_console.open_console();

  client::g_console.print("initializing interfaces", console_color_white);
  if (!g_interfaces.collect_interfaces())
    return false;

  client::g_console.print("initializing global addresses", console_color_white);
  if (!g_addresses.collect_addresses())
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
  g_drawing.draw();
  menu::present();
  g_render.finish();
}

bool client::get_local_player_global() {
  g_local_player = client_base_entity_t::get_local_player();

  if (!g_local_player)
    return false;

  return true;
}

void test() {
  client_local_player_t* local = client::g_local_player;
  if (!local || !local->is_alive())
    return;

  if (GetAsyncKeyState(VK_PRIOR) & 1) {
    const vector3_t origin = local->origin();
    const vector3_t end    = local->origin() + vector3_t{180.f, 0.f, 0.f};
    trace_filter_t  filter(local);
    trace_t         trace;
    client::g_interfaces.engine_trace->trace_ray({origin, end}, MASK_SHOT, &filter, &trace);

    if (!trace.entity || !trace.did_hit())
      return;

    client::g_console.printf("%d", trace.entity->is_player());
  }
}

void client::on_create_move(usercmd_t* cmd, bool* send_packet) {
  if (!get_local_player_global())
    return;

  if (client::g_local_player->is_alive())
    test();

  g_prediction.update();
  g_prediction.start_prediction(cmd);

  // Do stuff here

  g_prediction.finish_prediction();
}

bool client::on_cl_move() { return true; }

void client::on_level_shutdown() { g_local_player = nullptr; }