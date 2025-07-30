#pragma once

#include <vector>

struct global_addresses_t {
  struct {
    struct {
      uintptr_t run_command, restore_entity_to_predicted_frame, set_prediction_random_seed,
          get_weapon_data, key_values_init, load_from_buffer, eye_vectors;
    } functions;

    struct {
      std::vector<uintptr_t> datamaps = {};
    } structures;
  } client;

  struct {
    struct {
      uintptr_t cl_move, host_should_run;
    } functions;
  } engine;

  bool collect_addresses();
};