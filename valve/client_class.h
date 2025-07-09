#pragma once

#include "recv.h"

class client_class_t {
private:
  void* create_fn;
  void* create_event_fn;

public:
  const char*     network_name;
  recv_table_t*   table;
  client_class_t* next;
  int             id;
};