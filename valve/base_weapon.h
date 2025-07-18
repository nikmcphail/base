#pragma once

#include "library/utils.h"

#include "client_base_entity.h"

enum weapon_id_e {
  WEAPON_NONE = 0,

  WEAPON_P228,
  WEAPON_GLOCK,
  WEAPON_SCOUT,
  WEAPON_HEGRENADE,
  WEAPON_XM1014,
  WEAPON_C4,
  WEAPON_MAC10,
  WEAPON_AUG,
  WEAPON_SMOKEGRENADE,
  WEAPON_ELITE,
  WEAPON_FIVESEVEN,
  WEAPON_UMP45,
  WEAPON_SG550,

  WEAPON_GALIL,
  WEAPON_FAMAS,
  WEAPON_USP,
  WEAPON_AWP,
  WEAPON_MP5NAVY,
  WEAPON_M249,
  WEAPON_M3,
  WEAPON_M4A1,
  WEAPON_TMP,
  WEAPON_G3SG1,
  WEAPON_FLASHBANG,
  WEAPON_DEAGLE,
  WEAPON_SG552,
  WEAPON_AK47,
  WEAPON_KNIFE,
  WEAPON_P90,

  WEAPON_SHIELDGUN, // BOTPORT: Is this still needed?

  WEAPON_KEVLAR,
  WEAPON_ASSAULTSUIT,
  WEAPON_NVG,

  WEAPON_MAX, // number of weapons weapon index
};

class base_weapon_t {
public:
  weapon_id_e get_weapon_id() {
    return utils::get_virtual_function<weapon_id_e(__thiscall*)(base_weapon_t*)>(this,
                                                                                 371)(this);
  }
};