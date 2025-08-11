#include "lag_compensation.h"

#include "client/client.h"

#include "valve/global_vars_base.h"
#include "valve/cvar.h"
#include "valve/entities/player/cs_player.h"
#include "valve/animation_layer.h"
#include "valve/bone.h"
#include "valve/engine_client.h"
#include "valve/entity_list.h"

void lag_compensation_t::on_frame_stage_notify() {
  if (!client::g_local_player || !client::g_local_player->is_alive())
    return;

  if (client::g_interfaces.global_vars->max_clients <= 1) {
    clear_history();
    return;
  }

  teleport_distance_sqr = 64.f * 64.f;
  int dead_time         = client::g_interfaces.global_vars->cur_time - 1.0f;

  for (int i = 1; i <= 64; i++) {
    if (i == client::g_interfaces.engine_client->get_local_player_index())
      continue;

    cs_player_t* player = cs_player_t::get_cs_player(i);

    auto& track = player_track[player];

    if (!player || !player->is_valid() ||
        player->team_number() == client::g_local_player->team_number()) {
      if (!track.empty())
        track.clear();
      continue;
    }

    if (track.size() >= 1000)
      continue;

    // Remove outdated lag records
    while (!track.empty() && track.front().simulation_time < dead_time) {
      track.pop_front();
    }

    // Skip if the last record is already current
    if (!track.empty() && track.back().simulation_time >= player->simulation_time())
      continue;

    lag_record_t& record = track.emplace_back();

    record.flags = 0;
    if (player->is_alive())
      record.flags |= LC_ALIVE;

    record.simulation_time = player->simulation_time();
    record.angles          = player->eye_angles();
    record.origin          = player->abs_origin();
    record.mins_pre_scaled = player->vec_mins();
    record.maxs_pre_scaled = player->vec_maxs();
    record.head_pos        = player->get_hitbox_pos(HITBOX_HEAD);
    record.tick            = client::g_interfaces.global_vars->tick_count;

    player->setup_bones(record.bones, 128, BONE_USED_BY_HITBOX,
                        client::g_interfaces.global_vars->cur_time);

    for (int j = 0; j < MAX_LAYER_RECORDS; ++j) {
      if (animation_layer_t* current_layer = player->get_anim_overlay(j)) {
        record.layer_records[j].cycle    = current_layer->cycle;
        record.layer_records[j].order    = current_layer->order;
        record.layer_records[j].sequence = current_layer->sequence;
        record.layer_records[j].weight   = current_layer->weight;
      }
    }

    record.master_sequence = player->sequence();
    record.master_cycle    = player->cycle();

    for (int k = 0; k < MAXSTUDIOPOSEPARAM; k++) {
      record.pose_parameters[k] = player->get_pose_parameter(k);
    }
  }
}

void lag_compensation_t::clear_history() { player_track.clear(); }

float lag_compensation_t::get_lerp_time() {
  static auto cl_interp       = client::g_interfaces.cvar->find_var("cl_interp");
  static auto cl_interp_ratio = client::g_interfaces.cvar->find_var("cl_interp_ratio");
  static auto sv_client_min_interp_ratio =
      client::g_interfaces.cvar->find_var("sv_client_min_interp_ratio");
  static auto sv_client_max_interp_ratio =
      client::g_interfaces.cvar->find_var("sv_client_max_interp_ratio");
  static auto cl_updaterate    = client::g_interfaces.cvar->find_var("cl_updaterate");
  static auto sv_minupdaterate = client::g_interfaces.cvar->find_var("sv_minupdaterate");
  static auto sv_maxupdaterate = client::g_interfaces.cvar->find_var("sv_maxupdaterate");

  auto interp           = cl_interp->value.float_value;
  auto interp_ratio     = cl_interp_ratio->value.float_value;
  auto min_interp_ratio = sv_client_min_interp_ratio->value.float_value;
  auto max_interp_ratio = sv_client_max_interp_ratio->value.float_value;
  auto update_rate      = cl_updaterate->value.int_value;
  auto min_update_rate  = sv_minupdaterate->value.int_value;
  auto max_update_rate  = sv_maxupdaterate->value.int_value;

  auto clamp_interp_ratio = std::clamp(interp_ratio, min_interp_ratio, max_interp_ratio);
  auto clamp_update_rate  = std::clamp(update_rate, min_update_rate, max_update_rate);

  auto lerp = clamp_interp_ratio / static_cast<float>(clamp_update_rate);

  if (lerp <= interp)
    lerp = interp;

  return lerp;
}