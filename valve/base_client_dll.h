#pragma once

#include "library/utils.h"

class client_class_t;

class base_client_dll_t {
public:
  client_class_t* get_all_classes() {
    return utils::get_virtual_function<client_class_t*(__thiscall*)(base_client_dll_t*)>(
        this, 8)(this);
  }
};