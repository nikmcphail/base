#pragma once

#include "library/utils.h"

class surface_t {
public:
  HCURSOR unlock_cursor() {
    return utils::get_virtual_function<HCURSOR(__thiscall*)(surface_t*)>(this, 61)(this);
  }
};