#include "menu.h"

#include "client/client.h"

#include <Windows.h>

#include "imgui.h"

void menu::present() {
  if (GetAsyncKeyState(VK_INSERT) & 1)
    open = !open;

  if (!open)
    return;

  if (ImGui::Begin("x64 base", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
    if (ImGui::BeginTabBar("Test Tab##test_tab_bar")) {

      if (ImGui::BeginTabItem("Tab01##tab_one")) {
        if (ImGui::Button("Test Print##test_print_one")) {
          client::g_console.print("Test!", console_color_light_aqua);
        }
        ImGui::EndTabItem();
      }

      ImGui::EndTabBar();
    }
  }
  ImGui::End();
}