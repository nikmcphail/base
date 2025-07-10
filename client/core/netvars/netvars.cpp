#include "netvars.h"

#include "client/client.h"
#include "valve/client_class.h"
#include "valve/base_client_dll.h"
#include "library/hash.h"

#include <iostream>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <cstdio>
#include <ostream>
#include <ranges>
#include <algorithm>
#include <vector>

std::ofstream file;

netvars_t::netvars_t() {
  file.open("netvars.txt");

  client_class_t* client_class = client::g_interfaces.base_client->get_all_classes();

  while (client_class) {
    recv_table_t* recv_table = client_class->table;

    if (!recv_table) {
      client_class = client_class->next;
      continue;
    }
    file << recv_table->table_name << "\n";

    const auto table_name = hash::hash_crc(recv_table->table_name);
    var_map_t  var_map;
    iterate_props(&var_map, recv_table, 0);
    netvar_map.insert({table_name, var_map});

    client_class = client_class->next;
  }
  file.close();
}

void netvars_t::iterate_props(var_map_t* map, recv_table_t* table, uint32_t offset, int depth) {
  if (!table)
    return;

  std::string indent(depth, '\t');

  for (size_t i = 0; i < table->prop_count; i++) {
    const auto& prop = table->props[i];

    if (prop.data_table) {
      file << indent << "[" << prop.data_table->table_name << "]\n";
      iterate_props(map, prop.data_table, offset + prop.offset, depth + 1);
    }

    file << indent << prop.var_name << " = 0x" << std::hex << (offset + prop.offset) << "\n";

    map->insert({hash::hash_crc(prop.var_name), offset + prop.offset});
  }
}

uintptr_t netvars_t::get_netvar_offset(uint32_t table_name, uint32_t var_name) {
  auto var_map = netvar_map.at(table_name);
  return var_map.at(var_name);
}

uintptr_t netvars_t::get_netvar_offset(const char* table_name, const char* var_name) {
  return get_netvar_offset(hash::hash_crc(table_name), hash::hash_crc(var_name));
}

netvars_t::~netvars_t() { netvar_map.clear(); }