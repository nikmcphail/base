#include "console.h"

#include <cstdio>
#include <Windows.h>

void console_t::open_console() {
  AllocConsole();

  FILE* f{};
  freopen_s(&f, "CONIN$", "r", stdin);
  freopen_s(&f, "CONOUT$", "w", stdout);
  freopen_s(&f, "CONOUT$", "w", stderr);

  set_console_color(console_color_white);
}

void console_t::close_console() {
  fclose(stdin);
  fclose(stdout);
  fclose(stderr);
  FreeConsole();
}

void console_t::set_console_color(console_colors_e color) {
  const auto console = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(console, color);
}

void console_t::print(const char* text, console_colors_e color) {
  set_console_color(color);
  printf_s("%s\n", text);
}

void console_t::printf(const char* text, console_colors_e color, ...) {
  set_console_color(color);

  char    buffer[1024];
  va_list args;
  va_start(args, text);
  vsnprintf(buffer, sizeof(buffer), text, args);
  va_end(args);

  printf_s("%s\n", buffer);
}
void console_t::printf(const char* text, ...) {
  set_console_color(console_colors_e::console_color_white);

  char    buffer[1024];
  va_list args;
  va_start(args, text);
  vsnprintf(buffer, sizeof(buffer), text, args);
  va_end(args);

  printf_s("%s\n", buffer);
}