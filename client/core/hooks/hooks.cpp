#include "hooks.h"
#include <d3d9.h>

#include "client/client.h"
#include "valve/cusercmd.h"
#include "valve/view_setup.h"

class hooked_d3d9_device_t : IDirect3DDevice9 {
public:
  HRESULT hooked_present(IDirect3DDevice9* device, RECT* source_rect, RECT* dest_rect,
                         HWND dest_window_override, RGNDATA* dirty_region) {
    client::on_present();
    return client::g_hooks.d3d9_present_hook.thiscall<HRESULT>(
        this, device, source_rect, dest_rect, dest_window_override, dirty_region);
  }

  HRESULT hooked_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_parameters) {
    HRESULT result;

    {
      std::scoped_lock _{client::g_render.imgui_mutex};
      client::g_render.detach();
      result =
          client::g_hooks.d3d9_reset_hook.thiscall<HRESULT>(this, device, present_parameters);
      client::get_window_handle();
      client::g_render.initialize();
    }

    return result;
  }
};

class hooked_client_mode {
public:
  bool hooked_create_move(float input_sample_time, usercmd_t* cmd) {
    if (!cmd->command_number)
      return false;

    return false;
  }

  void hooked_override_view(view_setup_t* setup) {
    client::g_hooks.override_view_hook.thiscall(this, setup);
  }
};

bool hooks_t::initialize() {
  this->d3d9_device_hook = safetyhook::create_vmt(client::g_interfaces.d3d9_device);
  client::g_console.printf("\td3d9_device:", console_color_light_yellow);
  this->d3d9_present_hook =
      safetyhook::create_vm(this->d3d9_device_hook, 17, &hooked_d3d9_device_t::hooked_present);
  client::g_console.printf("\t\tpresent hooked", console_color_light_aqua);
  this->d3d9_reset_hook =
      safetyhook::create_vm(this->d3d9_device_hook, 16, &hooked_d3d9_device_t::hooked_reset);
  client::g_console.printf("\t\treset hooked", console_color_light_aqua);

  this->client_mode_hook = safetyhook::create_vmt(client::g_interfaces.client_mode);
  client::g_console.printf("\tclient_mode:", console_color_light_yellow);
  this->create_move_hook = safetyhook::create_vm(this->client_mode_hook, 21,
                                                 &hooked_client_mode::hooked_create_move);
  client::g_console.printf("\t\tcreatemove hooked", console_color_light_aqua);
  this->override_view_hook = safetyhook::create_vm(this->client_mode_hook, 16,
                                                   &hooked_client_mode::hooked_override_view);
  client::g_console.printf("\t\toverrideview hooked", console_color_light_aqua);

  client::g_console.print("\thooks initialized", console_color_gray);
  return true;
}

void hooks_t::unload() {
  d3d9_device_hook = {};
  client_mode_hook = {};
}