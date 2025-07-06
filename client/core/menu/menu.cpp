#include "menu.h"

#include "client/client.h"

#include <Windows.h>

#include "imgui.h"

void menu::present() {
  if (GetAsyncKeyState(VK_INSERT) & 1)
    open = !open;

  if (!open)
    return;

  ImGui::Begin("x64 base", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  if (ImGui::Button("Test"))
    client::g_console.print("success!");
  ImGui::End();
}