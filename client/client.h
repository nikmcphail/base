#pragma once

#include "client/core/console/console.h"
#include "client/core/interfaces/interfaces.h"
#include "client/core/hooks/hooks.h"
#include "client/core/render/render.h"
#include "client/core/offsets/offsets.h"

#include <Windows.h>

namespace client {
  inline bool attached{};

  inline console_t    g_console;
  inline interfaces_t g_interfaces;
  inline hooks_t      g_hooks;
  inline render_t     g_render;
  inline offsets_t    g_offsets;

  inline HWND g_window;

  bool initialize();
  bool should_unload();
  void unload();
  void get_window_handle();
  bool check_insecure();

  void on_present();
} // namespace client