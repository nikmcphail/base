#pragma once

#include "library/utils.h"

#include "library/math.h"
#include "player_info.h"

class engine_client_t {
public:
  void get_screen_size(int& width, int& height) {
    utils::get_virtual_function<void(__thiscall*)(engine_client_t*, int&, int&)>(this, 5)(
        this, width, height);
  }

  bool get_player_info(int ent_num, player_info_t* info) {
    return utils::get_virtual_function<bool(__thiscall*)(
        engine_client_t*, int, player_info_t*)>(this, 8)(this, ent_num, info);
  }

  int get_local_player_index() {
    return utils::get_virtual_function<int(__thiscall*)(engine_client_t*)>(this, 12)(this);
  }

  void get_view_angles(vector3_t& angles) {
    utils::get_virtual_function<void(__thiscall*)(engine_client_t*, vector3_t&)>(this, 19)(
        this, angles);
  }

  void set_view_angles(vector3_t& angles) {
    utils::get_virtual_function<void(__thiscall*)(engine_client_t*, vector3_t&)>(this, 20)(
        this, angles);
  }

  bool is_in_game() {
    return utils::get_virtual_function<bool(__thiscall*)(engine_client_t*)>(this, 26)(this);
  }
};