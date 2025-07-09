#include "offsets.h"

#include "client/core/netvars/netvars.h"
#include "client/client.h"

bool offsets_t::get_offsets() {
  netvars_t netvars;

  client::g_console.print("\tdumping netvars", console_color_light_aqua);

  client::g_console.print("\toffsets initialized", console_color_gray);
  return true;
}