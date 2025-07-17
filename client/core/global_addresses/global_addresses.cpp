#include "global_addresses.h"

#include "client/client.h"
#include "library/pe.h"

bool global_addresses_t::collect_addresses() {
  pe::module_t client_dll;
  if (!pe::get_module("client.dll", client_dll))
    return false;

  {
    this->client.functions.run_command = client_dll.find_pattern_in_memory(
        "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 4C 89 74 24 ? 41 57 48 83 EC ? 0F 29 74 24");
    this->client.functions.restore_entity_to_predicted_frame =
        client_dll.find_pattern_in_memory("40 55 48 83 EC ? 8B EA");
  }

  {
    this->client.structures.datamaps = client_dll.find_all_pattern_in_memory(
        "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? 48 89 ?? ?? ?? ?? ?? C3");
  }

  client::g_console.print("\taddresses initialized", console_color_light_aqua);
  return true;
}