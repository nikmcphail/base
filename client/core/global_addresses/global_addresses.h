#pragma once

#include <vector>

struct global_addresses_t {
  struct {
    struct {
      std::vector<uintptr_t> datamaps     = {};
      uintptr_t              local_player = {};
    } structures;
  } client;
  bool collect_addresses();
};