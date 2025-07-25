#pragma once

#include "client_player.h"

class client_local_player_t : public client_player_t {
public:
  vector3_t get_eye_position() { return this->origin() + this->view_offset(); }

  netvar_value_func(float, flash_max_alpha,
                    client::g_offsets.client.base_player.flash_max_alpha);
  netvar_value_func(vector3_t, view_offset, client::g_offsets.client.base_player.view_offset);
  netvar_value_func(vector3_t, aim_punch_angle,
                    client::g_offsets.client.base_player.aim_punch_angle);
};