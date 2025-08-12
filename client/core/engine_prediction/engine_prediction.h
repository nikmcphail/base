#pragma once

#include "valve/move_data.h"

class usercmd_t;

class engine_prediction_t {
public:
  move_data_t move_data{};
  float       old_curtime{};
  float       old_frametime{};
  int         old_tickcount{};

  int       old_flags{};
  vector3_t old_velocity{};
  void      start_prediction(usercmd_t* cmd, bool first = true);
  void      finish_prediction();
  void      run_pre_think();
  void      run_think();
  void      update();
  void      restore();
};