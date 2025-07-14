#pragma once

#include "client_base_entity.h"

#include "client/client.h"

class client_player_t : public client_base_entity_t {
public:
  static client_player_t* get_local_player() {
    return *reinterpret_cast<client_player_t**>(
        client::g_addresses.client.structures.local_player);
  }

  netvar_value_func(int, health, client::g_offsets.client.base_player.health);
};