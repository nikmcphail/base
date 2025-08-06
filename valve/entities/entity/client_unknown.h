#pragma once

#include "library/utils.h"

class collideable_t;
class client_networkable_t;
class client_renderable_t;
class client_entity_t;
class base_entity_t;

class handle_entity_t {
public:
  void set_ref_e_handle(unsigned int handle) {
    utils::get_virtual_function<void(__fastcall*)(void*, unsigned int)>(this, 1)(this, handle);
  }

  unsigned int get_ref_e_handle() {
    return utils::get_virtual_function<unsigned int(__fastcall*)(void*)>(this, 2)(this);
  }
};

class client_unknown_t : public handle_entity_t {
public:
  collideable_t* get_collidable() {
    return utils::get_virtual_function<collideable_t*(__fastcall*)(void*)>(this, 3)(this);
  }

  client_networkable_t* get_client_networkable() {
    return utils::get_virtual_function<client_networkable_t*(__fastcall*)(void*)>(this,
                                                                                  4)(this);
  }

  client_renderable_t* get_client_renderable() {
    return utils::get_virtual_function<client_renderable_t*(__fastcall*)(void*)>(this, 5)(this);
  }

  client_entity_t* get_client_entity() {
    return utils::get_virtual_function<client_entity_t*(__fastcall*)(void*)>(this, 6)(this);
  }

  base_entity_t* get_base_entity() {
    return utils::get_virtual_function<base_entity_t*(__fastcall*)(void*)>(this, 7)(this);
  }
};