#include "base_player.h"

base_player_t* base_player_t::get_base_player(int index) {
  auto base_entity = base_entity_t::get_base_entity(index);
  return to_base_player(base_entity);
}

void base_player_t::set_current_command(usercmd_t* cmd) { *(usercmd_t**)(this + 0x15B8) = cmd; }