#include "interfaces.h"

#include "library/pe.h"

#include "client/client.h"

bool interfaces_t::collect_interfaces() {

  client::g_console.printf("\tmodules:", console_color_light_yellow);
  pe::module_t shaderapidx9_dll;
  if (!pe::get_module("shaderapidx9.dll", shaderapidx9_dll)) {
    client::g_console.print("\t\tfailed to find shader api", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound shader api", console_color_light_aqua);

  pe::module_t vstdlib_dll;
  if (!pe::get_module("vstdlib.dll", vstdlib_dll)) {
    client::g_console.print("\t\tfailed to find vstdlib", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound vstdlib", console_color_light_aqua);

  pe::module_t client_dll;
  if (!pe::get_module("client.dll", client_dll)) {
    client::g_console.print("\t\tfailed to find client", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound client", console_color_light_aqua);

  client::g_console.printf("\taddresses:", console_color_light_yellow);
  this->d3d9_device = *(shaderapidx9_dll.find_pattern_in_memory("48 89 1D ?? ?? ?? ?? 48 8B CF")
                            .rel32<IDirect3DDevice9**>(0x3));
  if (!this->d3d9_device) {
    client::g_console.print("\t\tfailed to find d3d9 device", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound d3d9 device", console_color_light_aqua);

  client::g_console.printf("\tinterfaces:", console_color_light_yellow);

  this->cvar = vstdlib_dll.get_interface<cvar_t*>(HASH("VEngineCvar004"));
  if (!this->cvar) {
    client::g_console.print("\t\tfailed to find cvar", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound cvar", console_color_light_aqua);

  this->base_client = client_dll.get_interface<base_client_dll_t*>(HASH("VClient017"));
  if (!this->base_client) {
    client::g_console.print("\t\tfailed to find base_client_dll", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound base_client_dll", console_color_light_aqua);

  client::g_console.print("\tinterfaces initialized", console_color_gray);
  return true;
}