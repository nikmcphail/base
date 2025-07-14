#include "global_addresses.h"

#include "client/client.h"
#include "library/pe.h"

bool global_addresses_t::collect_addresses() {
  pe::module_t client_dll;
  if (!pe::get_module("client.dll", client_dll))
    return false;

  {
    this->client.structures.datamaps = client_dll.find_all_pattern_in_memory(
        "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? 48 89 ?? ?? ?? ?? ?? C3");
  }

  client::g_console.print("\taddresses initialized", console_color_light_aqua);
  return true;
}