#pragma once

#include <cstdint>

class cs_weapon_data_t {
public:
  char pad_0000[0x0728]; // 0x0000

  float max_speed; // 0x0728
  char  pad_072C[0x018C];

  int32_t penetration;    // 0x08B4
  int32_t damage;         // 0x08B8
  float   range;          // 0x08BC
  float   range_modifier; // 0x08C0
  int32_t bullets;        // 0x08C4
  float   cycle_time;     // 0x08C8
};
