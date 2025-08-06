#pragma once

#include <cstdint>

struct offsets_t {
  bool get_offsets();

  struct {
    struct {
      uintptr_t origin, vec_mins, vec_maxs, move_type, abs_origin, simulation_time;
    } base_entity;

    struct {
      uintptr_t health, tick_base, life_state, flags, flash_max_alpha, view_offset, eye_angles,
          team_number, velocity;
    } base_player;

    struct {
      uintptr_t clip;
    } base_weapon;

    struct {
      uintptr_t sequence, hitbox_set, cycle, pose_parameter;
    } base_animating;

  } client;

} inline offsets;