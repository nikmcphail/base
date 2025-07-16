#pragma once

#include <cstdint>

#include "library/math.h"

class client_player_t;

class client_base_entity_t {
  friend client_player_t;

  template <typename T> inline T get_ptr_at_offset(uint32_t offset) noexcept {
    return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(this) + offset);
  }

  template <typename T> inline T& get_value_at_offset(uint32_t offset) noexcept {
    return *get_ptr_at_offset<T*>(offset);
  }

#define netvar_value_func(type, name, offset)                                                  \
  type& name() noexcept { return get_value_at_offset<type>(offset); }
#define get_ptr_value_func(type, name, offset)                                                 \
  type name() noexcept { return get_ptr_at_offset<type>(offset); }

public:
  bool is_player() {
    return utils::get_virtual_function<bool(__thiscall*)(client_base_entity_t*)>(
        this, 131)(this);
  }

  netvar_value_func(vector3_t, origin, client::g_offsets.client.base_entity.origin);
  netvar_value_func(int, team_number, client::g_offsets.client.base_entity.team_number);
  netvar_value_func(vector3_t, vec_mins, client::g_offsets.client.base_entity.vec_mins);
  netvar_value_func(vector3_t, vec_maxs, client::g_offsets.client.base_entity.vec_maxs);
};