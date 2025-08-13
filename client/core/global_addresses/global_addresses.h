#pragma once

#include <vector>

struct global_addresses_t {
  struct {
    struct {
      uintptr_t run_command, restore_entity_to_predicted_frame, set_prediction_random_seed,
          get_weapon_data, key_values_init, load_from_buffer, eye_vectors, get_anim_overlay,
          draw_client_hitboxes, update_button_state, apply_abs_velocity_impulse,
          physics_run_think, get_next_think_tick, set_next_think, md5_pseudo_random,
          reset_instance_counters, set_collision_bounds;
    } functions;

    struct {
      std::vector<uintptr_t> datamaps = {};
    } structures;
  } client;

  struct {
    struct {
      uintptr_t send_datagram, start_dynamic_sound;
    } functions;
  } engine;

  bool collect_addresses();
};