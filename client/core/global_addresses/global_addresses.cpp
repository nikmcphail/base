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

    this->client.structures.local_player =
        client_dll.find_pattern_in_memory("48 8B 1D ? ? ? ? 48 85 DB 0F 84 ? ? ? ? 48 89 7C 24")
            .rel32<uintptr_t>(0x3);
  }

  client::g_console.print("\taddresses initialized", console_color_light_aqua);
  return true;
}