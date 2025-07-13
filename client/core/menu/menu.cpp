#include "menu.h"

#include "client/client.h"

#include <Windows.h>

#include "imgui.h"

void menu::present() {
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
  ImGui::GetIO().MouseDrawCursor = open;

  if (GetAsyncKeyState(VK_INSERT) & 1)
    open = !open;

  if (!open)
    return;

  if (ImGui::Begin("x64 base", nullptr)) {
    if (ImGui::BeginTabBar("##test_tab_bar")) {

      if (ImGui::BeginTabItem("Style##style_tab")) {
        ImGui::ShowStyleEditor();
      }
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }
  ImGui::End();
}