#pragma once

#include "client_base_entity.h"

#include "client/client.h"
#include "library/utils.h"
#include "valve/entity_list.h"
#include "valve/engine_client.h"

#define LIFE_ALIVE       0
#define LIFE_DYING       1
#define LIFE_DEAD        2
#define LIFE_RESPAWNABLE 3
#define LIFE_DISCARDBODY 4

class base_weapon_t;

class client_player_t : public client_base_entity_t {
public:
  static client_player_t* get_local_player() {
    return (client_player_t*)client::g_interfaces.entity_list->get_client_entity(
        client::g_interfaces.engine_client->get_local_player_index());
  }

  bool is_alive() { return this->life_state() == LIFE_ALIVE; }

  base_weapon_t* get_active_weapon() {
    return utils::get_virtual_function<base_weapon_t*(__thiscall*)(client_player_t*)>(
        this, 227)(this);
  }
  netvar_value_func(int, health, client::g_offsets.client.base_player.health);
  netvar_value_func(int, tick_base, client::g_offsets.client.base_player.tick_base);
  netvar_value_func(char, life_state, client::g_offsets.client.base_player.life_state);
  netvar_value_func(int, flags, client::g_offsets.client.base_player.flags);
};