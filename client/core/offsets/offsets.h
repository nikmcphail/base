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
          team_number, velocity, is_defusing, shots_fired, punch_angle, punch_angle_vel;
    } base_player;

    struct {
      uintptr_t clip_one, clip_two, primary_ammo_type, secondary_ammo_type, next_primary_attack,
          next_secondary_attack;
    } base_weapon;

    struct {
      uintptr_t sequence, hitbox_set, cycle, pose_parameter;
    } base_animating;

  } client;

} inline offsets;