#pragma once

#include "base_entity.h"

class animation_layer_t;

class base_animating_t : public base_entity_t {
public:
  animation_layer_t* get_anim_overlay(int i) {
    static auto func = (animation_layer_t * (__fastcall*)(void*, unsigned int))
                           client::g_addresses.client.functions.get_anim_overlay;
    return func(this, i);
  }

  float get_pose_parameter(int i) {
    uintptr_t base = reinterpret_cast<uintptr_t>(this);
    float*    pose_parameters =
        reinterpret_cast<float*>(base + client::g_offsets.client.base_animating.pose_parameter);
    return pose_parameters[i];
  }

  netvar_value_func(int, hitbox_set, client::g_offsets.client.base_animating.hitbox_set);
  netvar_value_func(int, sequence, client::g_offsets.client.base_animating.sequence);
  netvar_value_func(float, cycle, client::g_offsets.client.base_animating.cycle);
};