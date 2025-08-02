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

enum weapon_type_e {
  WEAPONTYPE_KNIFE = 0,
  WEAPONTYPE_PISTOL,
  WEAPONTYPE_SUBMACHINEGUN,
  WEAPONTYPE_RIFLE,
  WEAPONTYPE_SHOTGUN,
  WEAPONTYPE_SNIPER_RIFLE,
  WEAPONTYPE_MACHINEGUN,
  WEAPONTYPE_C4,
  WEAPONTYPE_GRENADE,
  WEAPONTYPE_UNKNOWN
};

class weapon_info_t {
public:
  char pad_0000[1836];
  int  type;
  bool full_auto;
};

class base_weapon_t {

  template <typename T> inline T get_ptr_at_offset(uint32_t offset) noexcept {
    return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(this) + offset);
  }

  template <typename T> inline T& get_value_at_offset(uint32_t offset) noexcept {
    return *get_ptr_at_offset<T*>(offset);
  }

#define netvar_value_func(type, name, offset)                                                  \
  type& name() noexcept { return get_value_at_offset<type>(offset); }
#define get_ptr_value_func(type, name, offset)                                                 \
  type name() noexcept { return get_ptr_at_offset<type>(offset); }

public:
  weapon_info_t& get_weapon_data() {
    typedef weapon_info_t& (*get_weapon_data_func)(base_weapon_t*);
    return ((get_weapon_data_func)client::g_addresses.client.functions.get_weapon_data)(this);
  }

  weapon_id_e get_weapon_id() {
    return utils::get_virtual_function<weapon_id_e(__thiscall*)(base_weapon_t*)>(this,
                                                                                 371)(this);
  }

  const char* get_weapon_name() noexcept {
    switch (get_weapon_id()) {
      case WEAPON_NONE:
        return "None";
      case WEAPON_P228:
        return "P228";
      case WEAPON_GLOCK:
        return "Glock";
      case WEAPON_SCOUT:
        return "Scout";
      case WEAPON_HEGRENADE:
        return "HE Grenade";
      case WEAPON_XM1014:
        return "XM1014";
      case WEAPON_C4:
        return "C4";
      case WEAPON_MAC10:
        return "MAC-10";
      case WEAPON_AUG:
        return "AUG";
      case WEAPON_SMOKEGRENADE:
        return "Smoke Grenade";
      case WEAPON_ELITE:
        return "Dual Elites";
      case WEAPON_FIVESEVEN:
        return "Five-SeveN";
      case WEAPON_UMP45:
        return "UMP-45";
      case WEAPON_SG550:
        return "SG-550";
      case WEAPON_GALIL:
        return "Galil";
      case WEAPON_FAMAS:
        return "FAMAS";
      case WEAPON_USP:
        return "USP";
      case WEAPON_AWP:
        return "AWP";
      case WEAPON_MP5NAVY:
        return "MP5 Navy";
      case WEAPON_M249:
        return "M249";
      case WEAPON_M3:
        return "M3";
      case WEAPON_M4A1:
        return "M4A1";
      case WEAPON_TMP:
        return "TMP";
      case WEAPON_G3SG1:
        return "G3SG1";
      case WEAPON_FLASHBANG:
        return "Flashbang";
      case WEAPON_DEAGLE:
        return "Desert Eagle";
      case WEAPON_SG552:
        return "SG-552";
      case WEAPON_AK47:
        return "AK-47";
      case WEAPON_KNIFE:
        return "Knife";
      case WEAPON_P90:
        return "P90";
      case WEAPON_SHIELDGUN:
        return "Shield Gun";
      case WEAPON_KEVLAR:
        return "Kevlar";
      case WEAPON_ASSAULTSUIT:
        return "Assault Suit";
      case WEAPON_NVG:
        return "Night Vision";
      default:
        return "Unknown";
    }
  }

  netvar_value_func(int, clip, client::g_offsets.client.base_weapon.clip);
};