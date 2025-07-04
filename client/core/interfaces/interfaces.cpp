#include "interfaces.h"

#include "library/pe.h"

#include "client/client.h"

bool interfaces_t::collect_interfaces() {

  pe::module_t shaderapidx9_dll;
  if (!pe::get_module("shaderapidx9.dll", shaderapidx9_dll)) {
    client::g_console.print("failed to find shader api", console_colors_e::console_color_red);
    return false;
  }
  client::g_console.print("found shader api", console_colors_e::console_color_beige);

  this->d3d9_device = *(shaderapidx9_dll.find_pattern_in_memory("48 89 1D ?? ?? ?? ?? 48 8B CF")
                            .rel32<IDirect3DDevice9**>(0x3));
  if (!this->d3d9_device) {
    client::g_console.print("failed to find d3d9 device", console_color_red);
    return false;
  }
  client::g_console.print("found d3d9 device", console_color_cyan);

  return true;
}