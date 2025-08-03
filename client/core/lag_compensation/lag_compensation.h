#pragma once

#include "valve/lag_record.h"
#include <deque>

#define LC_NONE  0
#define LC_ALIVE (1 << 0)

#define LC_ORIGIN_CHANGED    (1 << 8)
#define LC_ANGLES_CHANGED    (1 << 9)
#define LC_SIZE_CHANGED      (1 << 10)
#define LC_ANIMATION_CHANGED (1 << 11)

class client_player_t;
class convar_t;

class lag_compensation_t {
public:
  void on_frame_stage_notify();
  void clear_history();

  std::deque<lag_record_t> player_track[64]{};
  client_player_t*         current;
  float                    teleport_distance_sqr;
};