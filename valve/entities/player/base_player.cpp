#include "base_player.h"

base_player_t* base_player_t::get_base_player(int index) {
  auto base_entity = base_entity_t::get_base_entity(index);
  return to_base_player(base_entity);
}

void base_player_t::set_current_command(usercmd_t* cmd) { *(usercmd_t**)(this + 0x15B8) = cmd; }

void base_player_t::select_item(const char* str, int sub_type) {
  utils::get_virtual_function<void(__fastcall*)(void*, const char*, int)>(this, 268)(this, str,
                                                                                     sub_type);
}

void base_player_t::update_button_state(int button_mask) {
  static auto func =
      (void(__fastcall*)(void*, int))client::g_addresses.client.functions.update_button_state;
  func(this, button_mask);
}

void base_player_t::set_local_view_angles(const qangle_t& angles) {
  utils::get_virtual_function<void(__fastcall*)(void*, const qangle_t&)>(this, 298)(this,
                                                                                    angles);
}

void base_player_t::pre_think() {
  utils::get_virtual_function<void(__fastcall*)(void*)>(this, 258)(this);
}

void base_player_t::eye_vectors(vector3_t* forward, vector3_t* right, vector3_t* up) {
  static auto func =
      (void(__fastcall*)(void*, vector3_t*, vector3_t*,
                         vector3_t*))client::g_addresses.client.functions.eye_vectors;

  func(this, forward, right, up);
}