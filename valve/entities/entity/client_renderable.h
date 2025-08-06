#pragma once

#include "library/utils.h"

class matrix_3x4_t;
class vector3_t;
class model_t;

class client_renderable_t {
public:
  bool setup_bones(matrix_3x4_t* bone_to_world_out, int max_bones, int bone_mask,
                   float current_time) {
    return utils::get_virtual_function<bool(__fastcall*)(
        void*, matrix_3x4_t*, int, int, float)>(this, 16)(this, bone_to_world_out, max_bones,
                                                          bone_mask, current_time);
  }

  const model_t* get_model() {
    return utils::get_virtual_function<const model_t*(__fastcall*)(void*)>(this, 9)(this);
  }
};