#include "engine_prediction.h"

#include "valve/cusercmd.h"
#include "valve/move_data.h"
#include "valve/entities/client_local_player.h"
#include "client/client.h"
#include "valve/move_helper.h"
#include "valve/prediction.h"
#include "valve/global_vars_base.h"
#include "library/md5.h"
#include "valve/game_movement.h"
#include "valve/prediction.h"
#include "valve/client_state.h"

inline usercmd_t*& set_command(client_player_t* player) {
  return *reinterpret_cast<usercmd_t**>(reinterpret_cast<uintptr_t>(player) + 0x15B8);
}

void engine_prediction_t::store_old_global_variables() {
  if (!client::g_local_player)
    return;

  old_frametime = client::g_interfaces.global_vars->frame_time;
  old_curtime   = client::g_interfaces.global_vars->cur_time;
  old_tickbase  = client::g_local_player->tick_base();
  old_tickcount = client::g_interfaces.global_vars->tick_count;
}

void engine_prediction_t::start_prediction(usercmd_t* cmd, bool first) {
  if (!client::g_interfaces.move_helper)
    return;

  if (!client::g_local_player)
    return;

  client::g_interfaces.move_helper->set_host(client::g_local_player);
  if (first)
    memset(&move_data, 0, sizeof(move_data_t));

  set_command(client::g_local_player) = cmd;
  cmd->random_seed =
      (md5::pseudo_random(cmd->command_number) & std::numeric_limits<int>::max());
  client::g_local_player->set_prediction_random_seed(cmd);
  *client::g_interfaces.prediction_player = client::g_local_player;

  old_frametime = client::g_interfaces.global_vars->frame_time;

  const bool old_first_time_predicted = client::g_interfaces.prediction->first_time_predicted;
  const bool old_in_prediction        = client::g_interfaces.prediction->in_prediction;

  client::g_interfaces.global_vars->cur_time =
      client::g_local_player->tick_base() * client::g_interfaces.global_vars->interval_per_tick;
  client::g_interfaces.global_vars->frame_time =
      client::g_interfaces.global_vars->interval_per_tick;
  client::g_interfaces.global_vars->tick_count = client::g_local_player->tick_base();

  client::g_interfaces.prediction->in_prediction        = true;
  client::g_interfaces.prediction->first_time_predicted = false;

  client::g_interfaces.prediction->set_local_view_angles(cmd->view_angles);

  client::g_interfaces.game_movement->start_track_prediction_errors(client::g_local_player);

  if (first)
    client::g_interfaces.prediction->setup_move(client::g_local_player, cmd,
                                                client::g_interfaces.move_helper, &move_data);
  client::g_interfaces.game_movement->process_movement(client::g_local_player, &move_data);
  client::g_interfaces.prediction->finish_move(client::g_local_player, cmd, &move_data);
  client::g_interfaces.game_movement->finish_track_prediction_errors(client::g_local_player);

  client::g_interfaces.prediction->in_prediction        = old_in_prediction;
  client::g_interfaces.prediction->first_time_predicted = old_first_time_predicted;
}

void engine_prediction_t::finish_prediction() {
  if (!client::g_interfaces.move_helper)
    return;

  if (!client::g_local_player)
    return;

  client::g_interfaces.global_vars->cur_time   = old_curtime;
  client::g_interfaces.global_vars->frame_time = old_frametime;
  client::g_interfaces.global_vars->tick_count = old_tickcount;

  client::g_local_player->set_prediction_random_seed(nullptr);
  *client::g_interfaces.prediction_player = nullptr;
  client::g_interfaces.move_helper->set_host(nullptr);
  client::g_local_player->tick_base() = old_tickbase;
}

void engine_prediction_t::update() {
  const auto start = client::g_interfaces.client_state->last_command_ack;
  const auto stop  = client::g_interfaces.client_state->last_outgoing_command +
                    client::g_interfaces.client_state->choked_commands;

  client::g_interfaces.prediction->update(client::g_interfaces.client_state->delta_tick,
                                          client::g_interfaces.client_state->delta_tick > 0,
                                          start, stop);
}

void engine_prediction_t::restore() {
  client::g_interfaces.prediction->restore_entity_to_predicted_frame(
      client::g_interfaces.prediction->commands_predicted - 1);
}