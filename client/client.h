#pragma once

#include "client/core/console/console.h"
#include "client/core/interfaces/interfaces.h"
#include "client/core/hooks/hooks.h"

namespace client {
  inline bool attached{};

  inline console_t    g_console;
  inline interfaces_t g_interfaces;
  inline hooks_t      g_hooks;

  bool initialize();
  bool should_unload();
  void unload();
} // namespace client