#include "hooks.h"
#include <d3d9.h>

#include "client/client.h"

class hooked_d3d9_device_t : IDirect3DDevice9 {
public:
  HRESULT hooked_present(IDirect3DDevice9* device, RECT* source_rect, RECT* dest_rect,
                         HWND dest_window_override, RGNDATA* dirty_region) {
    return client::g_hooks.d3d9_present_hook.thiscall<HRESULT>(
        this, device, source_rect, dest_rect, dest_window_override, dirty_region);
  }

  HRESULT hooked_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_parameters) {
    HRESULT result;

    result =
        client::g_hooks.d3d9_reset_hook.thiscall<HRESULT>(this, device, present_parameters);

    return result;
  }
};

bool hooks_t::initialize() {
  this->d3d9_device_hook = safetyhook::create_vmt(client::g_interfaces.d3d9_device);
  this->d3d9_present_hook =
      safetyhook::create_vm(this->d3d9_device_hook, 17, &hooked_d3d9_device_t::hooked_present);
  this->d3d9_reset_hook =
      safetyhook::create_vm(this->d3d9_device_hook, 16, &hooked_d3d9_device_t::hooked_reset);

  client::g_console.print("hooks initialized", console_color_green);
  return true;
}

void hooks_t::unload() { d3d9_device_hook = {}; }