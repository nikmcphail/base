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
    this->client.functions.set_prediction_random_seed =
        client_dll.find_pattern_in_memory("48 85 C9 75 ? C7 05 ? ? ? ? ? ? ? ? C3");
    this->client.functions.get_weapon_data =
        client_dll.find_pattern_in_memory("E9 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC 48 8D "
                                          "05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 40 53 57");
    this->client.functions.key_values_init =
        client_dll.find_pattern_in_memory("40 53 48 83 EC ? 48 8B D9 C7 01");
    this->client.functions.load_from_buffer =
        client_dll.find_pattern_in_memory("4C 89 4C 24 ? 48 89 4C 24 ? 55 56 48 81 EC");
    this->client.functions.eye_vectors = client_dll.find_pattern_in_memory(
        "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 44 8B 91 ? ? ? ? 49 8B F9");
    this->client.functions.get_anim_overlay =
        client_dll.find_pattern_in_memory("8B C2 48 6B C0");
    this->client.functions.weapon_id_to_alias =
        client_dll.find_pattern_in_memory("4C 8D 05 ? ? ? ? 33 D2 49 8B C0");
    this->client.functions.draw_client_hitboxes =
        client_dll.find_pattern_in_memory("44 88 44 24 ? 55");
    this->client.functions.update_button_state =
        client_dll.find_pattern_in_memory("44 8B 81 ? ? ? ? 89 91");
    this->client.functions.apply_abs_velocity_impulse =
        client_dll.find_pattern_in_memory("48 89 5C 24 ? 57 48 83 EC ? F3 0F 10 05");
    this->client.functions.physics_run_think =
        client_dll.find_pattern_in_memory("4C 8B DC 49 89 73 ? 57 48 81 EC ? ? ? ? 8B 81");
    this->client.functions.get_next_think_tick =
        client_dll.find_pattern_in_memory("40 53 48 83 EC ? 48 8B D9 48 85 D2 75 ? 8B 81");
    this->client.functions.set_next_think =
        client_dll.find_pattern_in_memory("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F 2E 0D");
    this->client.functions.md5_pseudo_random =
        client_dll.find_pattern_in_memory("89 4C 24 ? 55 48 8B EC 48 81 EC");
    this->client.functions.reset_instance_counters =
        client_dll.find_pattern_in_memory("33 D2 C7 05 ? ? ? ? ? ? ? ? 41 B8");
    this->client.functions.set_collision_bounds = client_dll.find_pattern_in_memory(
        "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 81 EC ? ? ? ? F3 0F 10 0A");
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
    this->engine.functions.send_datagram =
        engine_dll.find_pattern_in_memory("40 55 57 41 56 48 8D AC 24");
    this->engine.functions.start_dynamic_sound =
        engine_dll.find_pattern_in_memory("4C 8B DC 57 48 81 EC");
  }

  client::g_console.print("\taddresses initialized", console_color_gray);
  return true;
}