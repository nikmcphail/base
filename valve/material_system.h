#pragma once

#include "library/utils.h"

class material_t;
class key_values_t;

class material_system_t {
public:
  material_t* create_material(const char* name, key_values_t* key_values) {
    return utils::get_virtual_function<material_t*(
        __thiscall*)(material_system_t*, const char*, key_values_t*)>(this, 70)(this, name,
                                                                                key_values);
  }

  material_t* find_material(const char* name, const char* group_name, bool complain = true,
                            const char* complain_prefix = NULL) {
    return utils::get_virtual_function<material_t*(
        __thiscall*)(material_system_t*, const char*, const char*, bool, const char*)>(
        this, 71)(this, name, group_name, complain, complain_prefix);
  }

  unsigned short first_material() {
    return utils::get_virtual_function<unsigned short(__thiscall*)(material_system_t*)>(
        this, 73)(this);
  }

  unsigned short next_material(unsigned short handle) {
    return utils::get_virtual_function<unsigned short(__thiscall*)(
        material_system_t*, unsigned short)>(this, 74)(this, handle);
  }

  unsigned short invalid_material() {
    return utils::get_virtual_function<unsigned short(__thiscall*)(material_system_t*)>(
        this, 75)(this);
  }

  material_t* get_material(unsigned short handle) {
    return utils::get_virtual_function<material_t*(
        __thiscall*)(material_system_t*, unsigned short)>(this, 76)(this, handle);
  }
};