#include "offsets.h"

#include "client/core/netvars/netvars.h"
#include "client/client.h"
#include "library/hash.h"

bool offsets_t::get_offsets() {
  client::g_console.print("\tdumping netvars and datamaps", console_color_light_aqua);
  netvars_t netvars;

  { // client entity
    client.base_entity.origin =
        netvars.get_netvar_offset(HASH("DT_BaseEntity"), HASH("m_vecOrigin"));
    client.base_entity.team_number =
        netvars.get_netvar_offset(HASH("DT_BaseEntity"), HASH("m_iTeamNum"));
    client.base_entity.vec_mins =
        netvars.get_netvar_offset(HASH("DT_BaseEntity"), HASH("m_vecMins"));
    client.base_entity.vec_maxs =
        netvars.get_netvar_offset(HASH("DT_BaseEntity"), HASH("m_vecMaxs"));
    client.base_entity.move_type =
        netvars.get_netvar_offset(HASH("C_BaseEntity"), HASH("m_MoveType"));
    client.base_entity.dormant =
        netvars.get_netvar_offset(HASH("C_BaseEntity"), HASH("m_bDormant"));
    client.base_entity.abs_origin =
        netvars.get_netvar_offset(HASH("C_BaseEntity"), HASH("m_vecAbsOrigin"));
  }

  { // client player
    client.base_player.health =
        netvars.get_netvar_offset(HASH("DT_BasePlayer"), HASH("m_iHealth"));
    client.base_player.tick_base =
        netvars.get_netvar_offset(HASH("DT_BasePlayer"), HASH("m_nTickBase"));
    client.base_player.life_state =
        netvars.get_netvar_offset(HASH("DT_BasePlayer"), HASH("m_lifeState"));
    client.base_player.flags =
        netvars.get_netvar_offset(HASH("DT_BasePlayer"), HASH("m_fFlags"));
    client.base_player.hitbox_set =
        netvars.get_netvar_offset(HASH("DT_BaseAnimating"), HASH("m_nHitboxSet"));
    client.base_player.flash_max_alpha =
        netvars.get_netvar_offset(HASH("DT_CSPlayer"), HASH("m_flFlashMaxAlpha"));
    client.base_player.view_offset =
        netvars.get_netvar_offset(HASH("DT_CSPlayer"), HASH("m_vecViewOffset[0]"));
    client.base_player.aim_punch_angle =
        netvars.get_netvar_offset(HASH("DT_BasePlayer"), HASH("m_vecPunchAngle"));
  }

  {
    client.base_weapon.clip =
        netvars.get_netvar_offset(HASH("DT_BaseCombatWeapon"), HASH("m_iClip1"));
  }

  client::g_console.print("\toffsets initialized", console_color_gray);
  return true;
}