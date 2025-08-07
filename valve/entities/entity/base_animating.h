#pragma once

#include "base_entity.h"

class animation_layer_t;

class base_animating_t : public base_entity_t {
public:
  animation_layer_t* get_anim_overlay(int i);

  float get_pose_parameter(int i);

  bool get_bone_cache(matrix_3x4_t* out);
  bool get_bone_vector(int bone, vector3_t& out);

  netvar_value_func(int, hitbox_set, client::g_offsets.client.base_animating.hitbox_set);
  netvar_value_func(int, sequence, client::g_offsets.client.base_animating.sequence);
  netvar_value_func(float, cycle, client::g_offsets.client.base_animating.cycle);
};