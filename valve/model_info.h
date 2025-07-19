#pragma once

#include "library/utils.h"

class studio_header_t;
class model_t;

class model_info_t {
public:
  studio_header_t* get_studio_model(const model_t* mod) {
    typedef studio_header_t* (*get_studio_model_t)(void*, const model_t*);
    return utils::get_virtual_function<get_studio_model_t>(this, 28)(this, mod);
  }
};