#pragma once

#include "library/utils.h"

class client_entity_t;
class entity_list_t {
public:
  client_entity_t* get_client_entity(int index) {
    return utils::get_virtual_function<client_entity_t*(__thiscall*)(entity_list_t*, int)>(
        this, 3)(this, index);
  }

  int number_of_entities(bool include_non_networkable) {
    return utils::get_virtual_function<int(__thiscall*)(entity_list_t*, bool)>(this, 5)(
        this, include_non_networkable);
  }

  int get_highest_entity_index() {
    return utils::get_virtual_function<int(__thiscall*)(entity_list_t*)>(this, 6)(this);
  }

  int get_max_entities() {
    return utils::get_virtual_function<int(__thiscall*)(entity_list_t*)>(this, 8)(this);
  }
};