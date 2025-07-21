#pragma once

#include "library/utils.h"

class view_setup_t;
class client_class_t;

class base_client_dll_t {
public:
  client_class_t* get_all_classes() {
    return utils::get_virtual_function<client_class_t*(__thiscall*)(base_client_dll_t*)>(
        this, 8)(this);
  }

  bool get_player_view(view_setup_t& playerView) {
    typedef bool(__thiscall * func)(void*, view_setup_t&);
    return utils::get_virtual_function<func>(this, 59)(this, playerView);
  }
};