#pragma once

#include <cstdint>
#include <map>
#include <string>

#include "library/address.h"

class recv_table_t;

class netvars_t {
public:
  netvars_t();
  ~netvars_t();

  using var_map_t   = std::map<uint32_t, uint32_t>;
  using table_map_t = std::map<uint32_t, var_map_t>;

  table_map_t netvar_map = {};

  void iterate_props(var_map_t* map, recv_table_t* table, uint32_t offset = 0, int depth = 1);
  uintptr_t        get_netvar_offset(uint32_t table_name, uint32_t var_name);
  inline uintptr_t get_netvar_offset(const char* table_name, const char* var_name);
  void             store_data_map(address_t addr);
  void             find_and_store_data_maps();
};