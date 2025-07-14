#pragma once

#include "library/utils.h"

class engine_client_t {
public:
  int get_local_player_index() {
    return utils::get_virtual_function<int(__thiscall*)(engine_client_t*)>(this, 12)(this);
  }
};