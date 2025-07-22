#pragma once

#include "library/utils.h"

class studio_header_t;
class model_t;
class material_t;

class model_info_t {
public:
  const char* get_model_name(const model_t* model) {
    return utils::get_virtual_function<const char*(__thiscall*)(model_info_t*, const model_t*)>(
        this, 3)(this, model);
  }

  void get_model_materials(const model_t* model, int count, material_t** material) {
    utils::get_virtual_function<void(__thiscall*)(model_info_t*, const model_t*, int,
                                                  material_t**)>(this, 16)(this, model, count,
                                                                           material);
  }

  studio_header_t* get_studio_model(const model_t* mod) {
    typedef studio_header_t* (*get_studio_model_t)(void*, const model_t*);
    return utils::get_virtual_function<get_studio_model_t>(this, 28)(this, mod);
  }
};