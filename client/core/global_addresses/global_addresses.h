#pragma once

#include <vector>

struct global_addresses_t {
  struct {
    struct {
      uintptr_t run_command, restore_entity_to_predicted_frame;
    } functions;

    struct {
      std::vector<uintptr_t> datamaps = {};
    } structures;
  } client;
  bool collect_addresses();
};