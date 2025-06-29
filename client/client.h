#pragma once

#include "client/core/console/console.h"
#include "client/core/interfaces/interfaces.h"

namespace client {
  inline bool attached{};

  inline console_t    g_console;
  inline interfaces_t g_interfaces;

  bool initialize();
  bool should_unload();
  void unload();
} // namespace client