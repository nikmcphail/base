#pragma once

#include "safetyhook.hpp"

class hooks_t {
public:
  SafetyHookVmt d3d9_device_hook;
  SafetyHookVm  d3d9_present_hook;
  SafetyHookVm  d3d9_reset_hook;

  SafetyHookVmt client_mode_hook;
  SafetyHookVm  create_move_hook;
  SafetyHookVm  override_view_hook;

  SafetyHookVmt surface_hook;
  SafetyHookVm  lock_cursor_hook;

  SafetyHookVmt prediction_hook;
  SafetyHookVm  run_command_hook;

  SafetyHookVmt base_client_hook;
  SafetyHookVm  level_shutdown_hook;

  SafetyHookInline cl_move_hook;

  bool initialize();
  void unload();
};