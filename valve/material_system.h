#pragma once

#include "library/utils.h"

class material_t;

class material_system_t {
public:
  unsigned short first_material() {
    return utils::get_virtual_function<unsigned short(__thiscall*)(material_system_t*)>(
        this, 65)(this);
  }

  unsigned short next_material(unsigned short handle) {
    return utils::get_virtual_function<unsigned short(__thiscall*)(
        material_system_t*, unsigned short)>(this, 66)(this, handle);
  }

  unsigned short invalid_material() {
    return utils::get_virtual_function<unsigned short(__thiscall*)(material_system_t*)>(
        this, 67)(this);
  }

  material_t* get_material(unsigned short handle) {
    return utils::get_virtual_function<material_t*(
        __thiscall*)(material_system_t*, unsigned short)>(this, 68)(this, handle);
  }
};