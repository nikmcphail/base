#pragma once

#include <Windows.h>

#include "library/utils.h"

class hud_chat_t {
public:
  // hex color codes can be done as such hud_chat->chat_printf("\7<hex code><your text>")
  void chat_printf(const char* fmt, ...) {

    char    buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    utils::get_virtual_function<void(__fastcall*)(void*, int, int, const char*)>(this, 19)(
        this, 0, 0, buffer);
  }
};