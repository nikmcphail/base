#include "engine_prediction.h"

#include "valve/cusercmd.h"
#include "valve/move_data.h"
#include "valve/entities/player/cs_player.h"
#include "client/client.h"
#include "valve/move_helper.h"
#include "valve/prediction.h"
#include "valve/global_vars_base.h"
#include "library/md5.h"
#include "valve/game_movement.h"
#include "valve/prediction.h"
#include "valve/client_state.h"

#include "valve/entities/weapon/cs_weapon.h"
#include "valve/entity_list.h"
#include "valve/flags.h"

void engine_prediction_t::start_prediction(usercmd_t* cmd) {
  if (!client::g_interfaces.move_helper || !cmd)
    return;

  if (!client::g_local_player)
    return;

  memset(&move_data, 0, sizeof(move_data_t));

  { // CPrediction::StartCommand(C_BasePlayer* player, CUserCmd* cmd)
    client::g_local_player->set_current_command(cmd);
// Replace with in game pseudo_random
#undef max
    cmd->random_seed =
        (md5::pseudo_random(cmd->command_number) & std::numeric_limits<int>::max());
    client::g_local_player->set_prediction_random_seed(cmd);
    *client::g_interfaces.prediction_player = client::g_local_player;
  }

  old_flags    = client::g_local_player->flags();
  old_velocity = client::g_local_player->velocity();

  old_frametime = client::g_interfaces.global_vars->frame_time;
  old_curtime   = client::g_interfaces.global_vars->cur_time;
  old_tickcount = client::g_interfaces.global_vars->tick_count;

  const auto old_tickbase         = client::g_local_player->tick_base();
  const auto old_in_prediction    = client::g_interfaces.prediction->in_prediction;
  const auto old_first_prediction = client::g_interfaces.prediction->first_time_predicted;

  client::g_interfaces.global_vars->cur_time =
      client::g_local_player->tick_base() * client::g_interfaces.global_vars->interval_per_tick;

  client::g_interfaces.global_vars->frame_time =
      client::g_interfaces.prediction->engine_paused
          ? 0
          : client::g_interfaces.global_vars->interval_per_tick;

  client::g_interfaces.global_vars->tick_count = client::g_local_player->tick_base();

  client::g_interfaces.prediction->first_time_predicted = false;
  client::g_interfaces.prediction->in_prediction        = true;

  client::g_interfaces.game_movement->start_track_prediction_errors(client::g_local_player);

  if (cmd->weapon_select) {
    cs_weapon_t* weapon =
        (cs_weapon_t*)client::g_interfaces.entity_list->get_client_entity(cmd->weapon_select);
    if (weapon) {
      client::g_local_player->select_item(weapon->get_weapon_name(), cmd->weapon_subtype);
    }
  }

  if (cmd->impulse) {
    client::g_local_player->impulse() = cmd->impulse;
  }

  client::g_local_player->update_button_state(cmd->buttons);

  { // CPrediction::CheckMovingGround(C_BasePlayer* player, double frametime)
    if (!(client::g_local_player->flags() & FL_BASEVELOCITY)) {
      client::g_local_player->apply_abs_velocity_impulse(
          client::g_local_player->base_velocity() *
          (1.0 + (client::g_interfaces.global_vars->frame_time * 0.5)));
      client::g_local_player->base_velocity() = vector3_t{0, 0, 0};
    }

    client::g_local_player->flags() &= ~FL_BASEVELOCITY;
  }

  client::g_local_player->set_local_view_angles(cmd->view_angles);

  run_pre_think();

  run_think();

  client::g_interfaces.move_helper->set_host(client::g_local_player);

  client::g_interfaces.prediction->setup_move(client::g_local_player, cmd,
                                              client::g_interfaces.move_helper, &move_data);
  client::g_interfaces.game_movement->process_movement(client::g_local_player, &move_data);
  client::g_interfaces.prediction->finish_move(client::g_local_player, cmd, &move_data);

  client::g_interfaces.move_helper->process_impacts();

  client::g_local_player->post_think();

  client::g_local_player->tick_base() = old_tickbase;

  client::g_interfaces.prediction->first_time_predicted = old_first_prediction;
  client::g_interfaces.prediction->in_prediction        = old_in_prediction;
}

void engine_prediction_t::finish_prediction() {
  if (!client::g_interfaces.move_helper)
    return;

  if (!client::g_local_player)
    return;

  client::g_interfaces.game_movement->finish_track_prediction_errors(client::g_local_player);
  client::g_interfaces.move_helper->set_host(nullptr);

  client::g_interfaces.global_vars->cur_time   = old_curtime;
  client::g_interfaces.global_vars->frame_time = old_frametime;
  client::g_interfaces.global_vars->tick_count = old_tickcount;

  client::g_local_player->set_prediction_random_seed(nullptr);
  *client::g_interfaces.prediction_player = nullptr;
}

void engine_prediction_t::run_pre_think() {
  if (!client::g_local_player)
    return;

  if (!client::g_local_player->physics_run_think())
    return;

  client::g_local_player->pre_think();
}

void engine_prediction_t::run_think() {
  if (!client::g_local_player)
    return;

  int think_tick = client::g_local_player->get_next_think_tick();
  if (think_tick <= 0 || think_tick > client::g_local_player->tick_base())
    return;

  client::g_local_player->set_next_think(-1);

  client::g_local_player->think();
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
