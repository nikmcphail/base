#pragma once

#include <mutex>
#include <Windows.h>

class render_t {
public:
  std::recursive_mutex imgui_mutex{};
  WNDPROC              orig_wndproc{};

  void setup_style();
  bool initialize();
  void setup_input();
  void detach_input();
  void detach();
  void begin();
  void finish();
};