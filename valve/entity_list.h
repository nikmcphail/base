#pragma once

#include "library/utils.h"

class client_base_entity_t;

class entity_list_t {
public:
  client_base_entity_t* get_client_entity(int index) {
    return utils::get_virtual_function<client_base_entity_t*(__thiscall*)(entity_list_t*, int)>(
        this, 3)(this, index);
  }
};