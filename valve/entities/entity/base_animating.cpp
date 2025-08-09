#include "base_animating.h"

#include "valve/global_vars_base.h"
#include "valve/bone.h"
#include "valve/vector3.h"

animation_layer_t* base_animating_t::get_anim_overlay(int i) {
  static auto func = (animation_layer_t * (__fastcall*)(void*, unsigned int))
                         client::g_addresses.client.functions.get_anim_overlay;
  return func(this, i);
}

float base_animating_t::get_pose_parameter(int i) {
  uintptr_t base = reinterpret_cast<uintptr_t>(this);
  float*    pose_parameters =
      reinterpret_cast<float*>(base + client::g_offsets.client.base_animating.pose_parameter);
  return pose_parameters[i];
}

bool base_animating_t::get_bone_cache(matrix_3x4_t* out) {
  return setup_bones(out, 128, BONE_USED_BY_HITBOX, client::g_interfaces.global_vars->cur_time);
}

bool base_animating_t::get_bone_vector(int bone, vector3_t& out) {
  matrix_3x4_t matrix[128];
  if (!get_bone_cache(matrix))
    return false;

  out.x = matrix[bone][0][3];
  out.y = matrix[bone][1][3];
  out.z = matrix[bone][2][3];

  return !(out.is_zero());
}

void base_animating_t::draw_client_boxes(float duration, bool mono_color) {
  static auto func = (void(__fastcall*)(
      void*, float, bool))client::g_addresses.client.functions.draw_client_hitboxes;

  func(this, duration, mono_color);
}