#pragma once

#include <cstdint>

struct offsets_t {
  bool get_offsets();

  struct {
    struct {

    } base_entity;

    struct {
      uint32_t health, tick_base, life_state;
    } base_player;
  } client;

} inline offsets;