#pragma once

#include <cstdint>

struct offsets_t {
  bool get_offsets();

  struct {
    struct {
      uintptr_t origin, team_number, vec_mins, vec_maxs, move_type, dormant;
    } base_entity;

    struct {
      uint32_t health, tick_base, life_state, flags, hitbox_set, flash_max_alpha, view_offset,
          aim_punch_angle;
    } base_player;
  } client;

} inline offsets;