#include "console.h"

#include <cstdio>
#include <Windows.h>

#include "valve/color.h"

void console_t::open_console() {
  AllocConsole();
  SetConsoleTitleA("x64 base");

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

void console_t::test(const char* text, bool passed) {
  set_console_color(console_colors_e::console_color_light_green);

  if (!passed)
    set_console_color(console_colors_e::console_color_light_red);

  printf_s("%s\n", text);
}

void console_t::testf(const char* text, bool passed, ...) {
  set_console_color(console_colors_e::console_color_light_green);

  if (!passed)
    set_console_color(console_colors_e::console_color_light_red);

  char    buffer[1024];
  va_list args;
  va_start(args, text);
  vsnprintf(buffer, sizeof(buffer), text, args);
  va_end(args);

  printf_s("%s\n", buffer);
}

void console_t::con_msg(const char* fmt, ...) {
  static ULONG64 con_msg_address =
      (ULONG64)GetProcAddress(GetModuleHandleA("tier0.dll"), "?ConMsg@@YAXPEBDZZ");

  static auto func = (void (*)(const char*))con_msg_address;

  char    buffer[1024];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  snprintf(buffer, sizeof(buffer), "%s\n", buffer);

  func(buffer);
}

void console_t::con_color_msg(const color_t& color, const char* fmt, ...) {
  static ULONG64 con_color_msg_address = (ULONG64)GetProcAddress(
      GetModuleHandleA("tier0.dll"), "?ConColorMsg@@YAXAEBVColor@@PEBDZZ");

  static auto func = (void (*)(const color_t& color, const char*))con_color_msg_address;

  char    buffer[1024];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  snprintf(buffer, sizeof(buffer), "%s\n", buffer);

  func(color, buffer);
}

void console_t::con_warning(const char* fmt, ...) {
  static ULONG64 con_warning_address =
      (ULONG64)GetProcAddress(GetModuleHandleA("tier0.dll"), "?ConWarning@@YAXPEBDZZ");

  static auto func = (void (*)(const char*))con_warning_address;

  char    buffer[1024];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  snprintf(buffer, sizeof(buffer), "%s\n", buffer);

  func(buffer);
}