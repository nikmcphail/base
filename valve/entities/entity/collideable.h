#pragma once

#include "library/utils.h"

class vector3_t;

class collideable_t {
public:
  const vector3_t& obb_mins_pre_scaled() {
    return utils::get_virtual_function<const vector3_t&(__fastcall*)(void*)>(this, 1)(this);
  }

  const vector3_t& obb_maxs_pre_scaled() {
    return utils::get_virtual_function<const vector3_t&(__fastcall*)(void*)>(this, 2)(this);
  }
};