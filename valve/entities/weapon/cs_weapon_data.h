#pragma once

#include <cstdint>

class cs_weapon_data_t {
public:
  char pad_0000[0x005A]; // 0x0000
  char print_name[80];   // 0x005A (90)
  char view_model[80];   // 0x00C8 (170)
  char player_model[80]; // 0x0168 (250)
  char anim_prefix[16];  // 0x0208 (330)

  char pad_0254[0x05CE]; // 0x015A → 0x0728

  float max_speed;        // 0x0728
  char  pad_072C[0x0188]; // 0x072C → 0x08B4

  int32_t penetration;        // 0x08B4
  int32_t damage;             // 0x08B8
  float   range;              // 0x08BC
  float   range_modifier;     // 0x08C0
  int32_t bullets;            // 0x08C4
  float   cycle_time;         // 0x08C8
  bool    accuracy_quadratic; // 0x08CC

  float accuracy_divisor; // 0x08CD
  float accuracy_offset;  // 0x08D1
  float max_inaccuracy;   // 0x08D5

  float spread[2];            // 0x08D9
  float inaccuracy_crouch[2]; // 0x08E1
  float inaccuracy_stand[2];  // 0x08E9
  float inaccuracy_jump[2];   // 0x08F1
  float inaccuracy_land[2];   // 0x08F9
  float inaccuracy_ladder[2]; // 0x0901
  float inaccuracy_fire[2];   // 0x0909
  float inaccuracy_move[2];   // 0x0911

  float recovery_time_stand;     // 0x0919
  float recovery_time_crouch;    // 0x091D
  float inaccuracy_reload;       // 0x0921
  float inaccuracy_alt_switch;   // 0x0925
  float time_to_idle_after_fire; // 0x0929
  float idle_interval;           // 0x092D

  int32_t weapon_price;   // 0x0931
  int32_t default_price;  // 0x0935
  int32_t previous_price; // 0x0939

  char pad_093D[0x012F]; // 0x093D → 0x0B3C

  bool melee_weapon; // 0x0B3C (1740)
};
