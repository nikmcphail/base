#pragma once

enum console_colors_e {
  console_color_black        = 0,
  console_color_blue         = 1,
  console_color_green        = 2,
  console_color_aqua         = 3,
  console_color_red          = 4,
  console_color_purple       = 5,
  console_color_yellow       = 6,
  console_color_white_gray   = 7,
  console_color_gray         = 8,
  console_color_light_blue   = 9,
  console_color_light_green  = 10,
  console_color_light_aqua   = 11,
  console_color_light_red    = 12,
  console_color_light_purple = 13,
  console_color_light_yellow = 14,
  console_color_white        = 15
};

class console_t {
public:
  void open_console();
  void close_console();
  void set_console_color(console_colors_e color);
  void print(const char* text, console_colors_e color = console_colors_e::console_color_white);
  void printf(const char* text, console_colors_e color = console_colors_e::console_color_white,
              ...);
  void printf(const char* text, ...);

  void test(const char* text, bool passed = true);
  void testf(const char* text, bool passed = true, ...);
};