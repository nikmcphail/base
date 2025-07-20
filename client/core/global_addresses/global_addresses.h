#pragma once

#include <vector>

struct global_addresses_t {
  struct {
    struct {
      uintptr_t run_command, restore_entity_to_predicted_frame, set_prediction_random_seed;
    } functions;

    struct {
      std::vector<uintptr_t> datamaps = {};
    } structures;
  } client;

  struct {
    struct {
      uintptr_t cl_move;
    } functions;
  } engine;

  bool collect_addresses();
};