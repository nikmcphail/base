#pragma once

#include <cstdint>

#include "library/math.h"
#include "library/utils.h"
#include "client/client.h"

#include "valve/engine_client.h"
#include "valve/entity_list.h"
#include "client/core/global_addresses/global_addresses.h"

class client_player_t;
class client_local_player_t;

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
    return utils::get_virtual_function<bool(__thiscall*)(client_base_entity_t*)>(this,
                                                                                 132)(this);
  }

  static client_local_player_t* get_local_player() {
    return (client_local_player_t*)client::g_interfaces.entity_list->get_client_entity(
        client::g_interfaces.engine_client->get_local_player_index());
  }

  void set_prediction_random_seed(const usercmd_t* cmd) {
    static auto func = (__int64(__fastcall*)(
        const usercmd_t*))client::g_addresses.client.functions.set_prediction_random_seed;
    func(cmd);
  }

  netvar_value_func(vector3_t, origin, client::g_offsets.client.base_entity.origin);
  netvar_value_func(int, team_number, client::g_offsets.client.base_entity.team_number);
  netvar_value_func(vector3_t, vec_mins, client::g_offsets.client.base_entity.vec_mins);
  netvar_value_func(vector3_t, vec_maxs, client::g_offsets.client.base_entity.vec_maxs);
};