#pragma once

#include "valve/entities/entity/base_combat_character.h"

#define LIFE_ALIVE       0
#define LIFE_DYING       1
#define LIFE_DEAD        2
#define LIFE_RESPAWNABLE 3
#define LIFE_DISCARDBODY 4

class base_player_t : public base_combat_character_t {
public:
  static base_player_t* get_base_player(int index);

  void set_current_command(usercmd_t* cmd);

  netvar_value_func(char, life_state, client::g_offsets.client.base_player.life_state);
  netvar_value_func(int, flags, client::g_offsets.client.base_player.flags);
  netvar_value_func(int, health, client::g_offsets.client.base_player.health);
  netvar_value_func(int, tick_base, client::g_offsets.client.base_player.tick_base);
  netvar_value_func(vector3_t, velocity, client::g_offsets.client.base_player.velocity);
  netvar_value_func(vector3_t, view_offset, client::g_offsets.client.base_player.view_offset);
  netvar_value_func(int, team_number, client::g_offsets.client.base_player.team_number);
};

inline base_player_t* to_base_player(base_entity_t* base_entity) {
  if (!base_entity || !base_entity->is_player())
    return nullptr;

  return reinterpret_cast<base_player_t*>(base_entity);
}