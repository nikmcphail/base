#pragma once

#include "library/utils.h"

class client_base_entity_t;

class entity_listener_t {
public:
  virtual void on_entity_created(client_base_entity_t* entity) {};
  virtual void on_entity_deleted(client_base_entity_t* entity) {};
};

class entity_list_t {
public:
  client_base_entity_t* get_client_entity(int index) {
    return utils::get_virtual_function<client_base_entity_t*(__thiscall*)(entity_list_t*, int)>(
        this, 3)(this, index);
  }

  void add_listener(entity_listener_t* listener) { entity_listeners.push_back(listener); }
  void remove_listener(entity_listener_t* listener) {
    auto it = std::find(entity_listeners.begin(), entity_listeners.end(), listener);
    if (it != entity_listeners.end()) {
      entity_listeners.erase(it);
    }
  }

private:
  std::vector<entity_listener_t*> entity_listeners;
};