#include "menu.h"

#include <Windows.h>

#include "imgui.h"

void menu::present() {
  if (GetAsyncKeyState(VK_INSERT) & 1)
    open = !open;

  if (!open)
    return;

  ImGui::Begin("Test");
  ImGui::End();
}