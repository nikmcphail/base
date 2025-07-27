#pragma once

#include <cstdint>

#include "library/math.h"
#include "library/utils.h"
#include "client/client.h"

#include "valve/engine_client.h"
#include "valve/entity_list.h"
#include "client/core/global_addresses/global_addresses.h"
#include "valve/studio_header.h"
#include "valve/model_info.h"
#include "valve/bone.h"
#include "valve/global_vars_base.h"
#include "valve/vector3.h"
#include "valve/matrix3x4.h"

class client_player_t;
class client_local_player_t;
class model_t;

class client_base_entity_t {
  friend client_player_t;
  friend client_local_player_t;

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
  bool is_alive() {
    return utils::get_virtual_function<bool(__thiscall*)(client_base_entity_t*)>(this,
                                                                                 131)(this);
  }

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

  void* get_client_renderable() {
    return utils::get_virtual_function<void*(__thiscall*)(client_base_entity_t*)>(this,
                                                                                  5)(this);
  }

  model_t* get_model() {
    void* client_renderable = this->get_client_renderable();
    if (!client_renderable)
      return nullptr;

    return utils::get_virtual_function<model_t*(__thiscall*)(void*)>(client_renderable,
                                                                     9)(client_renderable);
  }

  studio_bbox_t* get_hitbox(int index) {
    model_t* model = this->get_model();
    if (!model)
      return nullptr;

    studio_header_t* header = client::g_interfaces.model_info->get_studio_model(model);
    if (!header)
      return nullptr;

    studio_hitbox_set_t* hitbox_set = header->get_hitbox_set(this->hitbox_set());
    if (!hitbox_set)
      return nullptr;

    studio_bbox_t* hitbox = header->get_hitbox(index, this->hitbox_set());
    if (!hitbox)
      return nullptr;

    return hitbox;
  }

  vector3_t get_bone_pos(int index) {
    matrix_3x4_t bones[128];
    if (setup_bones(bones, 128, 256, 0.0f))
      return vector3_t{bones[index][0][3], bones[index][1][3], bones[index][2][3]};
    else
      return vector3_t{};
  }

  bool setup_bones(matrix_3x4_t* bone_to_world_out, int max_bones, int bone_mask,
                   float current_time) {
    void* client_renderable = this->get_client_renderable();
    if (!client_renderable)
      return false;

    return utils::get_virtual_function<bool(__thiscall*)(void*, matrix_3x4_t*, int, int,
                                                         float)>(client_renderable, 16)(
        client_renderable, bone_to_world_out, max_bones, bone_mask, current_time);
  }

  netvar_value_func(vector3_t, origin, client::g_offsets.client.base_entity.origin);
  netvar_value_func(int, team_number, client::g_offsets.client.base_entity.team_number);
  netvar_value_func(vector3_t, vec_mins, client::g_offsets.client.base_entity.vec_mins);
  netvar_value_func(vector3_t, vec_maxs, client::g_offsets.client.base_entity.vec_maxs);
  netvar_value_func(int, hitbox_set, client::g_offsets.client.base_player.hitbox_set);
  netvar_value_func(unsigned char, move_type, client::g_offsets.client.base_entity.move_type);
  netvar_value_func(bool, dormant, client::g_offsets.client.base_entity.dormant);
  netvar_value_func(vector3_t, abs_origin, client::g_offsets.client.base_entity.abs_origin);
};