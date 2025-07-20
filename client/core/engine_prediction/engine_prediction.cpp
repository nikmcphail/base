#include "engine_prediction.h"

#include "valve/cusercmd.h"
#include "valve/move_data.h"
#include "valve/client_local_player.h"
#include "client/client.h"
#include "valve/move_helper.h"
#include "valve/prediction.h"
#include "valve/global_vars_base.h"
#include "library/md5.h"
#include "valve/game_movement.h"
#include "valve/prediction.h"

inline usercmd_t*& set_command(client_player_t* player) {
  return *reinterpret_cast<usercmd_t**>(reinterpret_cast<uintptr_t>(player) + 0x15B8);
}

void engine_prediction_t::start_prediction(usercmd_t* cmd) {
  if (!client::g_interfaces.move_helper)
    return;

  client_local_player_t* local_player = client_base_entity_t::get_local_player();
  if (!local_player || !(local_player->is_alive()))
    return;

  memset(&move_data, 0, sizeof(move_data_t));

  set_command(local_player) = cmd;

#undef max
  cmd->random_seed =
      (md5::pseudo_random(cmd->command_number) & std::numeric_limits<int>::max());
  local_player->set_prediction_random_seed(cmd);
  *client::g_interfaces.prediction_player = local_player;

  old_curtime   = client::g_interfaces.global_vars->cur_time;
  old_frametime = client::g_interfaces.global_vars->frame_time;
  old_tickcount = client::g_interfaces.global_vars->tick_count;

  old_flags                          = local_player->flags();
  const int  old_tick_base           = local_player->tick_base();
  const bool old_is_first_prediction = client::g_interfaces.prediction->first_time_predicted;
  const bool old_in_prediction       = client::g_interfaces.prediction->in_prediction;

  client::g_interfaces.global_vars->cur_time =
      local_player->tick_base() * client::g_interfaces.global_vars->interval_per_tick;
  client::g_interfaces.global_vars->frame_time =
      (client::g_interfaces.prediction->engine_paused
           ? 0.0f
           : client::g_interfaces.global_vars->interval_per_tick);
  client::g_interfaces.global_vars->tick_count = local_player->tick_base();

  client::g_interfaces.prediction->first_time_predicted = false;
  client::g_interfaces.prediction->in_prediction        = true;

  client::g_interfaces.game_movement->start_track_prediction_errors(local_player);

  client::g_interfaces.prediction->set_local_view_angles(cmd->view_angles);

  client::g_interfaces.move_helper->set_host(local_player);

  client::g_interfaces.prediction->setup_move(local_player, cmd,
                                              client::g_interfaces.move_helper, &move_data);
  client::g_interfaces.game_movement->process_movement(local_player, &move_data);
  client::g_interfaces.prediction->finish_move(local_player, cmd, &move_data);

  local_player->tick_base() = old_tick_base;

  client::g_interfaces.prediction->in_prediction        = old_in_prediction;
  client::g_interfaces.prediction->first_time_predicted = old_is_first_prediction;
}

void engine_prediction_t::finish_prediction() {
  if (!client::g_interfaces.move_helper)
    return;

  client_local_player_t* local_player = client_player_t::get_local_player();
  if (!local_player || !local_player->is_alive())
    return;

  client::g_interfaces.game_movement->finish_track_prediction_errors(local_player);
  client::g_interfaces.move_helper->set_host(nullptr);

  client::g_interfaces.global_vars->cur_time   = old_curtime;
  client::g_interfaces.global_vars->frame_time = old_frametime;
  client::g_interfaces.global_vars->tick_count = old_tickcount;

  set_command(local_player) = nullptr;
  local_player->set_prediction_random_seed(nullptr);
  *client::g_interfaces.prediction_player = local_player;
}