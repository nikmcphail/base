#pragma once

#include "client/core/console/console.h"
#include "client/core/interfaces/interfaces.h"
#include "client/core/hooks/hooks.h"
#include "client/core/render/render.h"
#include "client/core/offsets/offsets.h"
#include "client/core/global_addresses/global_addresses.h"
#include "client/core/engine_prediction/engine_prediction.h"

#include <Windows.h>

class usercmd_t;

namespace client {
  inline bool attached{};

  inline console_t           g_console;
  inline interfaces_t        g_interfaces;
  inline hooks_t             g_hooks;
  inline render_t            g_render;
  inline offsets_t           g_offsets;
  inline global_addresses_t  g_addresses;
  inline engine_prediction_t g_prediction;

  inline HWND g_window;

  bool initialize();
  bool should_unload();
  void unload();
  void get_window_handle();
  bool check_insecure();

  void on_present();
  bool on_create_move(usercmd_t* cmd);
} // namespace client