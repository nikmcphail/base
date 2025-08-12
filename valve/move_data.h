#pragma once

#include "valve/vector3.h"
#include "valve/qangle.h"

#pragma pack(push, 1)
class move_data_t {
public:
  bool      first_run_of_functions;  // 0x0
  bool      game_code_moved_player;  // 0x1
  char      pad[2];                  // 0x2
  int       player_handle;           // 0x4
  int       impulse_command;         // 0x8
  qangle_t  view_angles;             // 0xc
  qangle_t  abs_view_angles;         // 0x18
  int       buttons;                 // 0x24
  int       old_buttons;             // 0x28
  float     forward_move;            // 0x2c
  float     old_forward_move;        // 0x30
  float     side_move;               // 0x34
  float     up_move;                 // 0x38
  float     max_speed;               // 0x3c
  float     client_max_speed;        // 0x40
  vector3_t velocity;                // 0x44
  qangle_t  angles;                  // 0x50
  qangle_t  old_angles;              // 0x5c
  float     out_step_height;         // 0x68
  vector3_t out_wish_vel;            // 0x6c
  vector3_t out_jump_vel;            // 0x78
  vector3_t constraint_center;       // 0x84
  float     contraint_radius;        // 0x90
  float     constraint_width;        // 0x94
  float     constraint_speed_factor; // 0x98
  vector3_t abs_origin;              // 0x9c
}; // Size: 0xa8
#pragma pack(pop)