#pragma once

#include "imgui.h"

#include "valve/vector3.h"
#include "valve/view_matrix.h"
#include <vector>
#include "valve/vector2.h"

struct im_gui_text_t {
  const char* text;
  ImU32       color;
  ImU32       outline_color;
};

struct im_gui_text_stack_t {
  std::vector<im_gui_text_t> text;
};

class drawing_t {
public:
  void draw_text(const vector2_t& position, const ImU32 color, const char* text);
  void draw_text_outlined(const vector2_t& position, const ImU32 color,
                          const ImU32 outline_color, const char* text);
  void draw_text_stack(const vector2_t& position, const im_gui_text_stack_t stack);

  void draw_circle(const vector2_t& center, float radius, const ImU32 color, int segments = 0,
                   float thickness = 1.0f);
  void draw_circle_filled(const vector2_t& center, float radius, const ImU32 color,
                          int segments = 0);

  void draw_2d_line(const vector2_t& pos_one, const vector2_t& pos_two, const ImU32 color,
                    float thickness = 1.0f);

  void draw_rect(const vector2_t& position, const vector2_t& size, const ImU32 color,
                 float rounding = 0.f, ImDrawFlags flags = 0, float thickness = 1.f);

  void draw();
};