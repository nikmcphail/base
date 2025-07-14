#include "offsets.h"

#include "client/core/netvars/netvars.h"
#include "client/client.h"
#include "library/hash.h"

bool offsets_t::get_offsets() {
  client::g_console.print("\tdumping netvars and datamaps", console_color_light_aqua);
  netvars_t netvars;

  { // client
    client.base_player.health =
        netvars.get_netvar_offset(HASH("DT_CSPlayer"), HASH("m_iHealth"));
    client.base_player.tick_base =
        netvars.get_netvar_offset(HASH("DT_CSPlayer"), HASH("m_nTickBase"));
  }

  client::g_console.print("\toffsets initialized", console_color_gray);
  return true;
}