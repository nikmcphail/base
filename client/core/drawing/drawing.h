#pragma once

#include "imgui.h"

#include "valve/vector3.h"
#include <vector>
#include "valve/vector2.h"
#include <variant>
#include <mutex>

#define COLOR_BLACK   IM_COL32_BLACK
#define COLOR_WHITE   IM_COL32_WHITE
#define COLOR_RED     IM_COL32(255, 0, 0, 255)
#define COLOR_LIME    IM_COL32(0, 255, 0, 255)
#define COLOR_BLUE    IM_COL32(0, 0, 255, 255)
#define COLOR_YELLOW  IM_COL32(255, 255, 0, 255)
#define COLOR_CYAN    IM_COL32(0, 255, 255, 255)
#define COLOR_MAGENTA IM_COL32(255, 0, 255, 255)
#define COLOR_SILVER  IM_COL32(192, 192, 192, 255)
#define COLOR_GRAY    IM_COL32(128, 128, 128, 255)
#define COLOR_MAROON  IM_COL32(128, 0, 0, 255)
#define COLOR_OLIVE   IM_COL32(128, 128, 0, 255)
#define COLOR_GREEN   IM_COL32(0, 128, 0, 255)
#define COLOR_PURPLE  IM_COL32(128, 0, 128, 255)
#define COLOR_TEAL    IM_COL32(0, 128, 128, 255)
#define COLOR_NAVY    IM_COL32(0, 0, 128, 255)

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
  std::string text{};
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
  ImU32     outline_color{};
  bool      outlined{false};
  float     rounding{0.f};
  float     thickness{1.f};
};

struct quad_t {
  vector2_t p0{};
  vector2_t p1{};
  vector2_t p2{};
  vector2_t p3{};
  ImU32     color{};
  bool      filled{false};
  float     thickness{1.f};
};

class drawing_t {
public:
  std::mutex                                                          drawing_mutex{};
  std::vector<std::variant<line_t, text_t, circle_t, rect_t, quad_t>> initial;
  std::vector<std::variant<line_t, text_t, circle_t, rect_t, quad_t>> intermediary;
  std::vector<std::variant<line_t, text_t, circle_t, rect_t, quad_t>> render;

private:
  void draw_text(const vector2_t& position, const ImU32 color = COLOR_WHITE,
                 const char* text = "");
  void draw_text_outlined(const vector2_t& position, const ImU32 color = COLOR_WHITE,
                          const ImU32 outline_color = COLOR_BLACK, const char* text = "");

  void draw_circle(const vector2_t& center, float radius, const ImU32 color, int segments = 0,
                   float thickness = 1.0f);
  void draw_circle_filled(const vector2_t& center, float radius,
                          const ImU32 color = COLOR_WHITE, int segments = 0);

  void draw_line(const vector2_t& pos_one, const vector2_t& pos_two,
                 const ImU32 color = COLOR_WHITE, float thickness = 1.0f);

  void draw_rect(const vector2_t& position, const vector2_t& size,
                 const ImU32 color = COLOR_WHITE, float rounding = 0.f, float thickness = 1.f);

  void draw_rect_outlined(const vector2_t& position, const vector2_t& size,
                          const ImU32 color         = COLOR_WHITE,
                          const ImU32 outline_color = COLOR_BLACK, float rounding = 0.f,
                          float thickness = 1.f);

  void draw_quad(const vector2_t& p0, const vector2_t& p1, const vector2_t& p2,
                 const vector2_t& p3, const ImU32 color = COLOR_WHITE, float thickness = 1.f);
  void draw_quad_filled(const vector2_t& p0, const vector2_t& p1, const vector2_t& p2,
                        const vector2_t& p3, const ImU32 color = COLOR_WHITE);

public:
  void add_line(const vector2_t& position_one, const vector2_t& position_two,
                const ImU32 color = COLOR_WHITE, float thickness = 1.f);

  void add_text(const vector2_t& position, const ImU32 color = COLOR_WHITE,
                std::string text = "", bool outlined = false,
                const ImU32 outline_color = COLOR_BLACK);

  void add_circle(const vector2_t& center, float radius, const ImU32 color = COLOR_WHITE,
                  int segments = 0, float thickness = 1.0f, bool filled = false);

  void add_rect(const vector2_t& position, const vector2_t& size,
                const ImU32 color = COLOR_WHITE, float rounding = 0.f, float thickness = 1.f,
                bool outlined = false, const ImU32 outline_color = COLOR_BLACK);

  void add_quad(const vector2_t& p0, const vector2_t& p1, const vector2_t& p2,
                const vector2_t& p3, const ImU32 color = COLOR_WHITE, float thickness = 1.f,
                bool filled = false);

  void clear_initial();
  void copy_to_intermediary();
  void copy_from_intermediary();

  void draw();
};