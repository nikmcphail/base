#include "render.h"

#include "client/client.h"
#include "client/core/menu/menu.h"

#include <d3d9.h>

#include "imgui.h"
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

void render_t::setup_input() {
  orig_wndproc = reinterpret_cast<WNDPROC>(
      SetWindowLongPtrW(client::g_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndproc)));
  client::g_console.printf("\tinput initialized", console_color_cyan);
}

void render_t::detach_input() {
  SetWindowLongPtrW(client::g_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(orig_wndproc));
}

bool render_t::initialize() {
  ImGui::CreateContext();

  if (!ImGui_ImplWin32_Init(client::g_window)) {
    client::g_console.printf("\t!!! imgui_implwin32 couldn't initialize properly !!!",
                             console_color_red);
    return false;
  }

  if (!ImGui_ImplDX9_Init(client::g_interfaces.d3d9_device)) {
    client::g_console.printf("\t!!! imgui_impldx9 couldn't initialize properly !!!",
                             console_color_red);
    return false;
  }

  client::g_console.printf("\trenderer initialized", console_color_cyan);
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
  {
    std::scoped_lock _{client::g_render.imgui_mutex};
    ImGui::NewFrame();
  }
}

void render_t::finish() {
  ImGui::Render();
  ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
  client::g_interfaces.d3d9_device->SetRenderState(D3DRS_SRGBWRITEENABLE, g_prev_srgb);
}