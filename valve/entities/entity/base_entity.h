#pragma once

#include "client_entity.h"
#include "client/client.h"

class usercmd_t;
class matrix_3x4_t;
class vector3_t;

class base_entity_t : public client_entity_t {
  friend class base_player_t;
  friend class base_animating_t;
  friend class cs_player_t;

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
  static base_entity_t* get_base_entity(int index);
  static void           set_prediction_random_seed(usercmd_t* cmd);
  bool                  is_alive();
  bool                  is_player();
  bool           setup_bones(matrix_3x4_t* bone_to_world_out, int max_bones, int bone_mask,
                             float current_time);
  vector3_t      get_eye_position();
  base_entity_t* get_observer_target();
  vector3_t      get_hitbox_pos(int id);
  int            get_observer_mode();

  netvar_value_func(vector3_t, origin, client::g_offsets.client.base_entity.origin);
  netvar_value_func(vector3_t, vec_mins, client::g_offsets.client.base_entity.vec_mins);
  netvar_value_func(vector3_t, vec_maxs, client::g_offsets.client.base_entity.vec_maxs);
  netvar_value_func(unsigned char, move_type, client::g_offsets.client.base_entity.move_type);
  netvar_value_func(vector3_t, abs_origin, client::g_offsets.client.base_entity.abs_origin);
  netvar_value_func(float, simulation_time,
                    client::g_offsets.client.base_entity.simulation_time);
};