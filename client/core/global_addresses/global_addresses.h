#pragma once

#include <vector>

struct global_addresses_t {
  struct {
    struct {
      std::vector<uintptr_t> datamaps = {};
    } structures;
  } client;
  bool collect_addresses();
};