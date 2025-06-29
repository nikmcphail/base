#pragma once

enum console_colors_e {
  console_color_white = 15,
  console_color_red   = 12,
  console_color_green = 10,
  console_color_cyan  = 11,
  console_color_beige = 14
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
};