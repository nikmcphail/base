#include "cs_player.h"

#include "valve/engine_client.h"

cs_player_t* cs_player_t::get_cs_player(int index) {
  auto base_entity = base_entity_t::get_base_entity(index);
  return to_cs_player(base_entity);
}

cs_player_t* cs_player_t::get_local_player() {
  auto index = client::g_interfaces.engine_client->get_local_player_index();
  return get_cs_player(index);
}

bool cs_player_t::is_local_player() {
  return (ent_index() == client::g_interfaces.engine_client->get_local_player_index());
}

bool cs_player_t::is_valid() { return (is_player() && is_alive() && !is_dormant()); }