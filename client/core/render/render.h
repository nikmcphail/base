#pragma once

#include <mutex>
#include <Windows.h>

#include "library/math.h"

#include "imgui.h"

class render_t {
public:
  std::recursive_mutex imgui_mutex{};
  WNDPROC              orig_wndproc{};

  ImDrawList*   draw_list;
  glm::ivec2    screen_size{};
  view_matrix_t view_matrix;

  void draw_text(const ImVec2& position, const ImU32 color, const char* text);
  void draw_text_outlined(const ImVec2& position, const ImU32 color, const ImU32 outline_color,
                          const char* text);

  void setup_style();
  bool initialize();
  void setup_input();
  void detach_input();
  void detach();
  void begin();
  void get_view_matrix();
  void draw();
  void finish();
};