#pragma once

#include "base_animating.h"

class cs_weapon_t;

class base_combat_character_t : public base_animating_t {
public:
  cs_weapon_t* get_active_weapon() {
    return utils::get_virtual_function<cs_weapon_t*(__thiscall*)(void*)>(this, 227)(this);
  }
};