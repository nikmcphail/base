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

  netvar_value_func(int, clip, client::g_offsets.client.base_weapon.clip);
};