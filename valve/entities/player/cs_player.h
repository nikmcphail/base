#pragma once

#include "base_player.h"

class cs_player_t : public base_player_t {
public:
  static cs_player_t* get_cs_player(int index);
  static cs_player_t* get_local_player();

  bool is_local_player();
  bool is_valid();

  netvar_value_func(float, flash_max_alpha,
                    client::g_offsets.client.base_player.flash_max_alpha);
  netvar_value_func(qangle_t, eye_angles, client::g_offsets.client.base_player.eye_angles);
};

inline cs_player_t* to_cs_player(base_entity_t* base_entity) {
  return reinterpret_cast<cs_player_t*>(to_base_player(base_entity));
}