#include "client.h"

#include <Windows.h>

bool client::initialize() {
  g_console.open_console();

  client::g_console.print("initializing interfaces", console_color_white);
  if (!g_interfaces.collect_interfaces())
    return false;

  attached = true;
  return true;
}

bool client::should_unload() { return (GetAsyncKeyState(VK_DELETE) & 1); }

void client::unload() { g_console.close_console(); }