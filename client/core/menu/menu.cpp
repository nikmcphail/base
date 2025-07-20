#include "menu.h"

#include "client/client.h"

#include <Windows.h>

#include "imgui.h"
#include "custom_widgets/imgui_custom_widgets.h"

void menu::present() {
  auto& io           = ImGui::GetIO();
  io.MouseDrawCursor = open;

  if (GetAsyncKeyState(VK_INSERT) & 1)
    open = !open;

  if (!open)
    return;

  if (ImGui::Begin("x64 base", nullptr)) {
    if (ImGui::BeginTabBar("##default_tab_bar")) {

      if (ImGui::BeginTabItem("Default##default_tab")) {

        ImGui::EndTabItem();
      }
    }

    ImGui::EndTabBar();
  }
  ImGui::End();
}