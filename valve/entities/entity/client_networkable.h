#pragma once

#include "library/utils.h"

class client_class_t;

class client_networkable_t {
public:
  client_class_t* get_client_class() {
    return utils::get_virtual_function<client_class_t*(__fastcall*)(void*)>(this, 2)(this);
  }

  bool is_dormant() {
    return utils::get_virtual_function<bool(__fastcall*)(void*)>(this, 8)(this);
  }

  int ent_index() {
    return utils::get_virtual_function<int(__fastcall*)(void*)>(this, 9)(this);
  }
};