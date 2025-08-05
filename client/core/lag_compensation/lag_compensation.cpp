#include "lag_compensation.h"

#include "client/client.h"

#include "valve/global_vars_base.h"
#include "valve/cvar.h"
#include "valve/entities/client_local_player.h"
#include "valve/animation_layer.h"

void lag_compensation_t::on_frame_stage_notify() {

  if (client::g_interfaces.global_vars->max_clients <= 1) {
    clear_history();
    return;
  }

  teleport_distance_sqr = 64.f * 64.f;
  int dead_time         = client::g_interfaces.global_vars->cur_time - 1.0f;

  for (int i = 1; i <= 64; i++) {
    if (i == client::g_interfaces.engine_client->get_local_player_index())
      continue;

    client_player_t* player =
        (client_player_t*)(client::g_interfaces.entity_list->get_client_entity(i));

    auto& track = player_track[i - 1];

    if (!player || !player->is_player() || !player->is_alive() || player->dormant()) {
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

    player->setup_bones(record.bones, 127, BONE_USED_BY_ANYTHING,
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

void lag_compensation_t::clear_history() {
  for (int i = 0; i < 64; i++) {
    player_track[i].clear();
  }
}