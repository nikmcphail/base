#include "global_addresses.h"

#include "client/client.h"
#include "library/pe.h"

bool global_addresses_t::collect_addresses() {
  pe::module_t client_dll;
  if (!pe::get_module("client.dll", client_dll))
    return false;

  pe::module_t engine_dll;
  if (!pe::get_module("engine.dll", engine_dll))
    return false;

  {
    this->client.functions.run_command = client_dll.find_pattern_in_memory(
        "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 4C 89 74 24 ? 41 57 48 83 EC ? 0F 29 74 24");
    this->client.functions.restore_entity_to_predicted_frame =
        client_dll.find_pattern_in_memory("40 55 48 83 EC ? 8B EA");
    this->client.functions.set_prediction_random_seed = client_dll.find_pattern_in_memory(
        "48 85 C9 75 0B C7 05 ? ? ? ? FF FF FF FF C3 8B 41 38 89 05 ? ? ? ? C3");
    this->client.functions.get_weapon_data =
        client_dll.find_pattern_in_memory("E9 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC 48 8D "
                                          "05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 40 53 57");
  }

  {
    this->client.structures.datamaps = client_dll.find_all_pattern_in_memory(
        "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? 48 89 ?? ?? ?? ?? ?? C3");
  }

  {
    this->engine.functions.cl_move = engine_dll.find_pattern_in_memory(
        "40 55 53 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 83 3D");
    this->engine.functions.host_should_run = engine_dll.find_pattern_in_memory(
        "48 83 EC ? 48 8B 05 ? ? ? ? 83 78 ? ? 74 ? 48 8B 05");
  }

  client::g_console.print("\taddresses initialized", console_color_light_aqua);
  return true;
}