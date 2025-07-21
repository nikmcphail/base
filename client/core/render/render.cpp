#include "render.h"

#include "client/client.h"
#include "client/core/menu/menu.h"
#include "valve/view_setup.h"
#include "valve/render_view.h"
#include "valve/base_client_dll.h"

#include <d3d9.h>

#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam,
                                                             LPARAM lParam);

LRESULT WINAPI wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
  if (!client::attached) {
    return CallWindowProcW(client::g_render.orig_wndproc, hwnd, msg, wp, lp);
  }

  auto call_def = true;

  switch (msg) {
    case WM_SYSCHAR: {
      call_def = false;
      break;
    }

    default: {
      break;
    }
  }

  {
    std::scoped_lock _{client::g_render.imgui_mutex};
    ImGui_ImplWin32_WndProcHandler(hwnd, msg, wp, lp);
  }

  if (menu::open) {
    return call_def ? DefWindowProcW(hwnd, msg, wp, lp) : 0;
  }

  return CallWindowProcW(client::g_render.orig_wndproc, hwnd, msg, wp, lp);
}

void render_t::setup_style() {
  auto& io    = ImGui::GetIO();
  auto& style = ImGui::GetStyle();

  io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
}

void render_t::setup_input() {
  orig_wndproc = reinterpret_cast<WNDPROC>(
      SetWindowLongPtrW(client::g_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndproc)));
  client::g_console.printf("\tinput initialized", console_color_gray);
}

void render_t::detach_input() {
  SetWindowLongPtrW(client::g_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(orig_wndproc));
}

bool render_t::initialize() {
  ImGui::CreateContext();
  auto& io = ImGui::GetIO();

  if (!ImGui_ImplWin32_Init(client::g_window)) {
    client::g_console.printf("!!! imgui_implwin32 couldn't initialize properly !!!",
                             console_color_red);
    return false;
  }

  if (!ImGui_ImplDX9_Init(client::g_interfaces.d3d9_device)) {
    client::g_console.printf("!!! imgui_impldx9 couldn't initialize properly !!!",
                             console_color_red);
    return false;
  }

  io.Fonts->AddFontDefault();

  setup_style();

  client::g_console.printf("\trenderer initialized", console_color_gray);
  return true;
}

void render_t::detach() {
  ImGui_ImplDX9_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

DWORD g_prev_srgb{};

void render_t::begin() {
  client::g_interfaces.d3d9_device->GetRenderState(D3DRS_SRGBWRITEENABLE, &g_prev_srgb);
  client::g_interfaces.d3d9_device->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);

  ImGui_ImplDX9_NewFrame();
  ImGui_ImplWin32_NewFrame();

  auto& display_size = ImGui::GetIO().DisplaySize;
  screen_size        = {display_size.x, display_size.y};

  {
    std::scoped_lock _{client::g_render.imgui_mutex};
    ImGui::NewFrame();
  }

  draw_list = ImGui::GetBackgroundDrawList();
}

void render_t::get_view_matrix() {
  view_setup_t setup;
  if (!client::g_interfaces.base_client->get_player_view(setup))
    return;

  static view_matrix_t v_matrix;
  view_matrix_t        matrix1, matrix2, matrix3;

  client::g_interfaces.render_view->get_matrices_for_view(setup, &matrix1, &matrix2, &v_matrix,
                                                          &matrix3);

  this->view_matrix = v_matrix;
}

void render_t::finish() {
  ImGui::Render();
  ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
  client::g_interfaces.d3d9_device->SetRenderState(D3DRS_SRGBWRITEENABLE, g_prev_srgb);
}