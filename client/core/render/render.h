#pragma once

#include <mutex>
#include <Windows.h>

#include "imgui.h"
#include "valve/vector2.h"
#include "valve/view_matrix.h"

class render_t {
public:
  std::recursive_mutex imgui_mutex{};
  WNDPROC              orig_wndproc{};

  ImDrawList*   draw_list;
  vector2_t    screen_size{};
  view_matrix_t view_matrix;

  void setup_style();
  bool initialize();
  void setup_input();
  void detach_input();
  void detach();
  void begin();
  void get_view_matrix();
  void finish();
};