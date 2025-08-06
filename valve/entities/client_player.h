#pragma once

#include "client_base_entity.h"

#include "library/utils.h"
#include "valve/qangle.h"

#define LIFE_ALIVE       0
#define LIFE_DYING       1
#define LIFE_DEAD        2
#define LIFE_RESPAWNABLE 3
#define LIFE_DISCARDBODY 4

class base_weapon_t;
class animation_layer_t;

class client_player_t : public client_base_entity_t {
public:
  base_weapon_t* get_active_weapon() {
    return utils::get_virtual_function<base_weapon_t*(__thiscall*)(client_player_t*)>(
        this, 227)(this);
  }

  animation_layer_t* get_anim_overlay(unsigned int i) {
    static auto func = (animation_layer_t * (__fastcall*)(void*, unsigned int))
                           client::g_addresses.client.functions.get_anim_overlay;
    return func(this, i);
  }

  float get_pose_parameter(int i) {
    uintptr_t base = reinterpret_cast<uintptr_t>(this);
    float*    pose_parameters =
        reinterpret_cast<float*>(base + client::g_offsets.client.base_player.pose_parameter);
    return pose_parameters[i];
  }

  netvar_value_func(int, health, client::g_offsets.client.base_player.health);
  netvar_value_func(int, tick_base, client::g_offsets.client.base_player.tick_base);
  netvar_value_func(char, life_state, client::g_offsets.client.base_player.life_state);
  netvar_value_func(int, flags, client::g_offsets.client.base_player.flags);
  netvar_value_func(qangle_t, eye_angles, client::g_offsets.client.base_player.eye_angles);
  netvar_value_func(vector3_t, view_offset, client::g_offsets.client.base_player.view_offset);
  netvar_value_func(int, sequence, client::g_offsets.client.base_player.sequence);
  netvar_value_func(float, cycle, client::g_offsets.client.base_player.cycle);
  netvar_value_func(int, team_number, client::g_offsets.client.base_player.team_number);
};