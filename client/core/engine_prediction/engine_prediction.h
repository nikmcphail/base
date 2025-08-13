#pragma once

#include "valve/move_data.h"

class usercmd_t;
class cs_player_t;
class base_entity_t;

class engine_prediction_t {
public:
  float old_curtime{};
  float old_frametime{};
  int   old_tickcount{};

  int  old_flags{};
  void run_pre_think(cs_player_t* player);
  void run_think(cs_player_t* player);
  void update();
  void restore();
  void suppress_events(base_entity_t* entity);
  void start_command(cs_player_t* player, usercmd_t* cmd);
  void check_moving_ground(cs_player_t* player, double frametime);
  void run_command(cs_player_t* player, usercmd_t* cmd);
  void finish_command(cs_player_t* player);
};