#pragma once

#include "valve/move_data.h"

class usercmd_t;

typedef void(__fastcall* set_prediction_random_seed)(usercmd_t*);

class engine_prediction_t {
public:
  move_data_t move_data{};
  float       old_curtime{};
  float       old_frametime{};
  int         old_tickcount{};
  int         old_flags{};

  void start_prediction(usercmd_t* cmd);
  void finish_prediction();
};