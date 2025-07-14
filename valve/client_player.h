#pragma once

#include "client_base_entity.h"

#include "client/client.h"
#include "library/utils.h"
#include "valve/entity_list.h"

class client_player_t : public client_base_entity_t {
public:
  static client_player_t* get_local_player() {
    return (client_player_t*)client::g_interfaces.entity_list->get_client_entity(1);
  }

  bool is_alive() {
    return utils::get_virtual_function<bool(__thiscall*)(client_player_t*)>(this, 121)(this);
  }

  netvar_value_func(int, health, client::g_offsets.client.base_player.health);
};