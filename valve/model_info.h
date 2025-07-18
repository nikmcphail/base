#pragma once

#include "library/utils.h"

class studio_header_t;
class model_t;

class model_info_t {
public:
  studio_header_t* get_studio_model(const model_t* model) {
    return utils::get_virtual_function<studio_header_t*(
        __thiscall*)(model_info_t*, const model_t*)>(this, 28)(this, model);
  }
};