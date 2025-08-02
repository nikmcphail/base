#pragma once

#include "client_player.h"
#include "valve/qangle.h"

class client_local_player_t : public client_player_t {
public:
  netvar_value_func(float, flash_max_alpha,
                    client::g_offsets.client.base_player.flash_max_alpha);
  netvar_value_func(qangle_t, aim_punch_angle,
                    client::g_offsets.client.base_player.aim_punch_angle);
};