#pragma once

#include "client_base_entity.h"

#include "client/client.h"
#include "library/utils.h"
#include "valve/entity_list.h"
#include "valve/engine_client.h"

class client_player_t : public client_base_entity_t {
public:
  static client_player_t* get_local_player() {
    return (client_player_t*)client::g_interfaces.entity_list->get_client_entity(
        client::g_interfaces.engine_client->get_local_player_index());
  }

  netvar_value_func(int, health, client::g_offsets.client.base_player.health);
  netvar_value_func(int, tick_base, client::g_offsets.client.base_player.tick_base);
};