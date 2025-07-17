#include "engine_prediction.h"

#include "valve/cusercmd.h"
#include "valve/move_data.h"
#include "valve/client_player.h"
#include "client/client.h"
#include "valve/move_helper.h"
#include "valve/game_movement.h"
#include "valve/prediction.h"
#include "valve/global_vars_base.h"

void engine_prediction_t::start_prediction(usercmd_t* cmd) {
  client_player_t*    local_player = client_player_t::get_local_player();
  global_vars_base_t* globals      = client::g_interfaces.global_vars;

  memset(&move_data, 0, sizeof(move_data_t));

  old_curtime         = globals->cur_time;
  old_frametime       = globals->frame_time;
  globals->cur_time   = local_player->tick_base() * globals->interval_per_tick;
  globals->frame_time = globals->interval_per_tick;

  *(usercmd_t**)(local_player + 5560) = cmd;

  if (client::g_interfaces.move_helper) {
    client::g_interfaces.move_helper->set_host(local_player);
    client::g_interfaces.game_movement->start_track_prediction_errors(local_player);
    client::g_interfaces.prediction->setup_move(local_player, cmd,
                                                client::g_interfaces.move_helper, &move_data);
    client::g_interfaces.game_movement->process_movement(local_player, &move_data);
    client::g_interfaces.prediction->finish_move(local_player, cmd, &move_data);
  }
}

void engine_prediction_t::finish_prediction() {
  client_player_t*    local_player = client_player_t::get_local_player();
  global_vars_base_t* globals      = client::g_interfaces.global_vars;

  if (client::g_interfaces.move_helper) {
    client::g_interfaces.game_movement->finish_track_prediction_errors(local_player);
    client::g_interfaces.move_helper->set_host(nullptr);
  }
  globals->cur_time   = old_curtime;
  globals->frame_time = old_frametime;
}