#pragma once

#include "library/math.h"

class move_data_t {
public:
  bool first_run_of_functions : 1;
  bool game_code_moved_player : 1;

  unsigned int player_handle;

  int       impulse;
  vector3_t view_angles;
  vector3_t abs_view_angles;
  int       buttons;
  int       old_buttons;
  float     forward_move;
  float     old_forward_move;
  float     side_move;
  float     up_move;

  float max_speed;
  float client_max_speed;

  vector3_t velocity;
  vector3_t angles;
  vector3_t old_angles;

  float     out_step_height;
  vector3_t out_wish_vel;
  vector3_t out_jump_vel;

  vector3_t constraight_center;
  float     constraint_radius;
  float     constraint_width;
  float     constraint_speed_factor;

private:
  vector3_t abs_origin;
};