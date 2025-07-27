#pragma once

#include "imgui.h"

#include "valve/vector3.h"
#include <vector>
#include "valve/vector2.h"
#include <variant>
#include <mutex>

struct line_t {
  vector2_t position_one{};
  vector2_t position_two{};
  ImU32     color{};
  float     thickness{1.0f};
};

struct text_t {
  vector2_t   position{};
  ImU32       color{};
  ImU32       outline_color{};
  bool        outlined{false};
  const char* text{};
};

struct circle_t {
  vector2_t center{};
  float     radius{};
  ImU32     color{};
  bool      filled{false};
  int       segments{0};
  float     thickness{1.0f};
};

struct rect_t {
  vector2_t position{};
  vector2_t size{};
  ImU32     color{};
  float     rounding{0.f};
  float     thickness{1.f};
};

class drawing_t {
public:
  std::mutex                                                  drawing_mutex{};
  std::vector<std::variant<line_t, text_t, circle_t, rect_t>> initial;
  std::vector<std::variant<line_t, text_t, circle_t, rect_t>> intermediary;
  std::vector<std::variant<line_t, text_t, circle_t, rect_t>> render;

private:
  void draw_text(const vector2_t& position, const ImU32 color, const char* text);
  void draw_text_outlined(const vector2_t& position, const ImU32 color,
                          const ImU32 outline_color, const char* text);

  void draw_circle(const vector2_t& center, float radius, const ImU32 color, int segments = 0,
                   float thickness = 1.0f);
  void draw_circle_filled(const vector2_t& center, float radius, const ImU32 color,
                          int segments = 0);

  void draw_line(const vector2_t& pos_one, const vector2_t& pos_two, const ImU32 color,
                 float thickness = 1.0f);

  void draw_rect(const vector2_t& position, const vector2_t& size, const ImU32 color,
                 float rounding = 0.f, float thickness = 1.f);

public:
  void add_line(const vector2_t& position_one, const vector2_t& position_two, const ImU32 color,
                float thickness = 1.f);

  void add_text(const vector2_t& position, const ImU32 color, const char* text,
                bool outlined = false, const ImU32 outline_color = IM_COL32_BLACK);

  void add_circle(const vector2_t& center, float radius, const ImU32 color, int segments = 0,
                  float thickness = 1.0f, bool filled = false);

  void add_rect(const vector2_t& position, const vector2_t& size, const ImU32 color,
                float rounding = 0.f, float thickness = 1.f);

  void clear_initial();
  void copy_to_intermediary();
  void copy_from_intermediary();

  void draw();
};