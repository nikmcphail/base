#pragma once

#include "valve/entities/entity/base_entity.h"

class prediction_system_t {
public:
  virtual ~prediction_system_t() {}

  prediction_system_t* next_system{nullptr};
  bool                 suppress_event{};
  base_entity_t*       suppress_host{nullptr};
  int                  status_pushed;
};