#pragma once

#include "client/core/console/console.h"
#include "client/core/interfaces/interfaces.h"
#include "client/core/hooks/hooks.h"
#include "client/core/render/render.h"
#include "client/core/offsets/offsets.h"
#include "client/core/global_addresses/global_addresses.h"
#include "client/core/engine_prediction/engine_prediction.h"
#include "client/core/drawing/drawing.h"
#include "client/core/atlas/atlas.h"
#include "client/core/lag_compensation/lag_compensation.h"

#include <Windows.h>

class usercmd_t;
class cs_player_t;

namespace client {
  inline bool attached{};

  inline console_t           g_console;
  inline interfaces_t        g_interfaces;
  inline hooks_t             g_hooks;
  inline render_t            g_render;
  inline offsets_t           g_offsets;
  inline global_addresses_t  g_addresses;
  inline engine_prediction_t g_prediction;
  inline drawing_t           g_drawing;
  inline atlas_t             g_atlas;
  inline lag_compensation_t  g_lag_compensation;

  inline HWND         g_window;
  inline cs_player_t* g_local_player;

  bool initialize();
  bool should_unload();
  void unload();
  void get_window_handle();
  bool get_local_player_global();
  bool check_insecure();

  void on_present();
  void on_create_move(usercmd_t* cmd);
  void on_level_shutdown();
  void on_paint();
  void on_frame_stage_notify(int stage);
} // namespace client