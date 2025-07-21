#pragma once

#include "imgui.h"

#include "library/math.h"

class drawing_t {
public:
  void draw_text(const ImVec2& position, const ImU32 color, const char* text);
  void draw_text_outlined(const ImVec2& position, const ImU32 color, const ImU32 outline_color,
                          const char* text);

  void draw_circle(const ImVec2& center, float radius, const ImU32 color, int segments = 0,
                   float thickness = 1.0f);
  void draw_circle_filled(const ImVec2& center, float radius, const ImU32 color,
                          int segments = 0);

  void draw_2d_line(const ImVec2& pos_one, const ImVec2& pos_two, const ImU32 color,
                    float thickness = 1.0f);

  void draw_3d_line_clipped(const vector3_t& pos_one, const vector3_t& pos_two,
                            const ImU32 color, view_matrix_t& view_matrix,
                            float thickness = 1.f);

  void draw_rect(const ImVec2& p_min, const ImVec2& p_max, const ImU32 color,
                 float rounding = 0.f, ImDrawFlags flags = 0, float thickness = 1.f);

  void draw();
};