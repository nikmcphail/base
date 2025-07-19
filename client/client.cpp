#include "client.h"

#include "client/core/menu/menu.h"

#include <Windows.h>
#include <d3d9.h>
#include "valve/cusercmd.h"
#include "valve/client_local_player.h"
#include "valve/model_info.h"
#include "valve/studio_header.h"
#include "valve/global_vars_base.h"

bool client::initialize() {
  g_console.open_console();

  client::g_console.print("initializing interfaces", console_color_white);
  if (!g_interfaces.collect_interfaces())
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

  client::g_console.print("initializing global addresses", console_color_white);
  if (!g_addresses.collect_addresses())
    return false;

  client::g_console.print("initializing offsets", console_color_white);
  if (!g_offsets.get_offsets())
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
  menu::present();
  g_render.finish();
}

void test() {
  client_local_player_t* local_player = client_base_entity_t::get_local_player();
  if (!local_player || !local_player->is_alive())
    return;

  const model_t* model = local_player->get_model();
  if (!model)
    return;
  client::g_console.print("got model!");

  studio_header_t* header = client::g_interfaces.model_info->get_studio_model(model);
  if (!header)
    return;
  client::g_console.printf("header pointer: %p", header);

  int hitbox_set_index = local_player->hitbox_set();
  client::g_console.printf("hitbox set index: %d", hitbox_set_index);

  studio_hitbox_set_t* hitbox_set_ptr = header->get_hitbox_set(hitbox_set_index);
  if (!hitbox_set_ptr)
    return;
  client::g_console.printf("hitbox set ptr: %p", hitbox_set_ptr);

  studio_bbox_t* hitbox = header->get_hitbox(12, hitbox_set_index);
  if (!hitbox)
    return;
  client::g_console.printf("hitbox pointer: %p", hitbox);
}

bool client::on_create_move(usercmd_t* cmd) {
  if (!cmd || !cmd->command_number)
    return false;

  test();

  g_prediction.start_prediction(cmd);

  // Do stuff here

  g_prediction.finish_prediction();

  return false;
}
