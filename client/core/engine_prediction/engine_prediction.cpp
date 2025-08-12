#include "engine_prediction.h"

#include "client/client.h"

#include "valve/entities/player/cs_player.h"
#include "valve/client_state.h"
#include "valve/prediction.h"
#include "valve/prediction_system.h"
#include "valve/cusercmd.h"
#include "valve/global_vars_base.h"
#include "valve/engine_client.h"
#include "valve/game_movement.h"
#include "valve/entities/weapon/cs_weapon.h"
#include "valve/entity_list.h"
#include "valve/flags.h"
#include "valve/move_helper.h"

void engine_prediction_t::run_pre_think(cs_player_t* player) {
  if (!player)
    return;

  if (!player->physics_run_think(0))
    return;

  client::g_local_player->pre_think();
}

void engine_prediction_t::run_think(cs_player_t* player) {
  if (!player)
    return;

  int think_tick = player->get_next_think_tick();
  if (think_tick <= 0 || think_tick > player->tick_base())
    return;

  player->set_next_think(-1);

  player->think();
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

void engine_prediction_t::suppress_events(base_entity_t* entity) {
  auto system = client::g_interfaces.prediction_system;
  if (system) {
    system->suppress_event = entity != nullptr;
    system->suppress_host  = entity;

    if (system->status_pushed > 0) {
      system->status_pushed = 0;
    }
    system = system->next_system;
  }
}

void engine_prediction_t::start_command(cs_player_t* player, usercmd_t* cmd) {
  static auto reset_instance_counters_fn =
      (void (*)())client::g_addresses.client.functions.reset_instance_counters;
  static auto set_prediction_random_seed_fn = (void(__fastcall*)(
      const usercmd_t* cmd))client::g_addresses.client.functions.set_prediction_random_seed;

  reset_instance_counters_fn();
  player->set_current_command(cmd);
  set_prediction_random_seed_fn(cmd);
  *client::g_interfaces.prediction_player = player;
}

void engine_prediction_t::check_moving_ground(cs_player_t* player, double frametime) {
  if (!(player->flags() & FL_BASEVELOCITY)) {
    player->apply_abs_velocity_impulse(player->base_velocity() * (1.0 + (frametime * 0.5)));
    player->base_velocity() = vector3_t(0, 0, 0);
  }

  player->flags() &= ~FL_BASEVELOCITY;
}

void engine_prediction_t::run_command(cs_player_t* player, usercmd_t* cmd) {
  if (!client::g_interfaces.move_helper)
    return;

  if (!player)
    return;

  suppress_events(player);

  static move_data_t data;

  start_command(player, cmd);
  client::g_interfaces.move_helper->set_host(player);

  old_curtime   = client::g_interfaces.global_vars->cur_time;
  old_frametime = client::g_interfaces.global_vars->frame_time;

  old_flags = client::g_local_player->flags();

  client::g_interfaces.global_vars->cur_time =
      player->tick_base() * client::g_interfaces.global_vars->interval_per_tick;
  client::g_interfaces.global_vars->frame_time =
      client::g_interfaces.engine_client->is_paused()
          ? 0
          : client::g_interfaces.global_vars->interval_per_tick;

  client::g_interfaces.prediction->first_time_predicted = false;
  client::g_interfaces.prediction->in_prediction        = true;

  client::g_interfaces.game_movement->start_track_prediction_errors(player);

  if (cmd->weapon_select != 0) {
    cs_weapon_t* weapon =
        (cs_weapon_t*)client::g_interfaces.entity_list->get_client_entity(cmd->weapon_select);
    if (weapon) {
      player->select_item(weapon->get_weapon_name(), cmd->weapon_subtype);
    }
  }

  if (cmd->impulse) {
    player->impulse() = cmd->impulse;
  }

  player->update_button_state(cmd->buttons);

  check_moving_ground(player, client::g_interfaces.global_vars->frame_time);

  { player->set_local_view_angles(cmd->view_angles); }

  run_pre_think(player);
  run_think(player);

  memset(&data, 0, sizeof(data));
  {
    client::g_interfaces.prediction->setup_move(player, cmd, client::g_interfaces.move_helper,
                                                &data);
  }

  client::g_interfaces.game_movement->process_movement(player, &data);

  client::g_interfaces.prediction->finish_move(player, cmd, &data);

  if (player->is_alive()) {
    if (player->flags() & FL_DUCKING) {
      player->set_collision_bounds(VECTOR_HULL_DUCK_MIN, VECTOR_HULL_DUCK_MAX);
    } else {
      player->set_collision_bounds(VECTOR_HULL_MIN, VECTOR_HULL_MAX);
    }
  }

  client::g_interfaces.move_helper->process_impacts();

  client::g_interfaces.game_movement->finish_track_prediction_errors(player);
}

void engine_prediction_t::finish_command(cs_player_t* player) {
  if (!client::g_interfaces.move_helper)
    return;

  static auto set_prediction_random_seed_fn = (void(__fastcall*)(
      const usercmd_t* cmd))client::g_addresses.client.functions.set_prediction_random_seed;

  player->set_current_command(NULL);
  set_prediction_random_seed_fn(NULL);
  *client::g_interfaces.prediction_player        = NULL;
  client::g_interfaces.prediction->in_prediction = false;
  client::g_interfaces.move_helper->set_host(NULL);
  client::g_interfaces.global_vars->cur_time   = old_curtime;
  client::g_interfaces.global_vars->frame_time = old_frametime;
  suppress_events(NULL);
}