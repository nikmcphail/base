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
  SafetyHookVm  frame_stage_notify_hook;

  SafetyHookVmt model_render_hook;
  SafetyHookVm  draw_model_execute_hook;

  SafetyHookVmt engine_vgui_hook;
  SafetyHookVm  paint_hook;

  SafetyHookVmt panel_hook;
  SafetyHookVm  paint_traverse_hook;

  void hook_vmt(SafetyHookVmt& vmt, void* original, const std::string& name);
  template <typename T>
  void hook_vm(SafetyHookVmt& vmt, SafetyHookVm& vm, T detour, int index,
               const std::string& name);
  template <typename T>
  void hook_inline(SafetyHookInline& inline_hook, T detour, void* original,
                   const std::string& name);

  bool initialize();
  void unload();
};