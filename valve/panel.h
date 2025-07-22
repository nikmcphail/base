#pragma once

#include "library/utils.h"

class panel_t {
public:
  const char* get_name(unsigned long long panel) {
    return utils::get_virtual_function<const char*(__thiscall*)(panel_t*, unsigned long long)>(
        this, 36)(this, panel);
  }
};