#pragma once

#include <vector>

struct global_addresses_t {
  struct {
    struct {
      uintptr_t run_command;
    } functions;

    struct {
      std::vector<uintptr_t> datamaps = {};
      uintptr_t move_data;
    } structures;
  } client;
  bool collect_addresses();
};