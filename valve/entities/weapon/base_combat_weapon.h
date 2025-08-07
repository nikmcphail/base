#pragma once

#include "valve/entities/entity/base_entity.h"

class base_combat_weapon_t : public base_entity_t {
public:
  netvar_value_func(int, clip_one, client::g_offsets.client.base_weapon.clip_one);
  netvar_value_func(int, clip_two, client::g_offsets.client.base_weapon.clip_two);
  netvar_value_func(int, primary_ammo_type,
                    client::g_offsets.client.base_weapon.primary_ammo_type);
  netvar_value_func(int, secondary_ammo_type,
                    client::g_offsets.client.base_weapon.secondary_ammo_type);
  netvar_value_func(float, next_primary_attack,
                    client::g_offsets.client.base_weapon.next_primary_attack);
  netvar_value_func(float, next_secondary_attack,
                    client::g_offsets.client.base_weapon.next_secondary_attack);
};