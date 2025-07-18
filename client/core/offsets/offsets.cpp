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
  }

  client::g_console.print("\toffsets initialized", console_color_gray);
  return true;
}