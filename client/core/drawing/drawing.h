#pragma once

#include "imgui.h"

class drawing_t {
public:
  void draw_text(const ImVec2& position, const ImU32 color, const char* text);
  void draw_text_outlined(const ImVec2& position, const ImU32 color, const ImU32 outline_color,
                          const char* text);

  void draw_circle(const ImVec2& center, float radius, const ImU32 color, int segments = 0,
                   float thickness = 1.0f);
  void draw_circle_filled(const ImVec2& center, float radius, const ImU32 color,
                          int segments = 0);

  void draw_line(const ImVec2& pos_one, const ImVec2& pos_two, const ImU32 color,
                 float thickness = 1.0f);

  void draw_rect(const ImVec2& p_min, const ImVec2& p_max, const ImU32 color,
                 float rounding = 0.f, ImDrawFlags flags = 0, float thickness = 1.f);

  void draw();
};