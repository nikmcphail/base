#include "imgui_custom_widgets.h"
#include <Windows.h>
#include <string>
#include <unordered_map>
#include <imgui.h> // Assuming you have this included

void ImGui::Hotkey(int* k, const ImVec2& size_arg) {
  static bool waitingForKey = false;
  static bool justOpened    = false;

  auto GetKeyName = [](int vk) -> std::string {
    // Manual override for common VK codes
    static const std::unordered_map<int, const char*> keyMap = {
        {VK_LBUTTON, "Mouse 1"},
        {VK_RBUTTON, "Mouse 2"},
        {VK_MBUTTON, "Mouse 3"},
        {VK_XBUTTON1, "Mouse 4"},
        {VK_XBUTTON2, "Mouse 5"},
        {VK_BACK, "Backspace"},
        {VK_TAB, "Tab"},
        {VK_CLEAR, "Clear"},
        {VK_RETURN, "Enter"},
        {VK_SHIFT, "Shift"},
        {VK_CONTROL, "Ctrl"},
        {VK_MENU, "Alt"},
        {VK_PAUSE, "Pause"},
        {VK_CAPITAL, "Caps Lock"},
        {VK_ESCAPE, "Escape"},
        {VK_SPACE, "Space"},
        {VK_PRIOR, "Page Up"},
        {VK_NEXT, "Page Down"},
        {VK_END, "End"},
        {VK_HOME, "Home"},
        {VK_LEFT, "Left Arrow"},
        {VK_UP, "Up Arrow"},
        {VK_RIGHT, "Right Arrow"},
        {VK_DOWN, "Down Arrow"},
        {VK_SELECT, "Select"},
        {VK_PRINT, "Print"},
        {VK_EXECUTE, "Execute"},
        {VK_SNAPSHOT, "Print Screen"},
        {VK_INSERT, "Insert"},
        {VK_DELETE, "Delete"},
        {VK_HELP, "Help"},
        {VK_LWIN, "Left Win"},
        {VK_RWIN, "Right Win"},
        {VK_APPS, "Menu"},
        {VK_SLEEP, "Sleep"},
        {VK_NUMLOCK, "Num Lock"},
        {VK_SCROLL, "Scroll Lock"},
        {VK_BROWSER_BACK, "Browser Back"},
        {VK_BROWSER_FORWARD, "Browser Forward"},
        {VK_BROWSER_REFRESH, "Browser Refresh"},
        {VK_BROWSER_STOP, "Browser Stop"},
        {VK_BROWSER_SEARCH, "Browser Search"},
        {VK_BROWSER_FAVORITES, "Browser Favorites"},
        {VK_BROWSER_HOME, "Browser Home"},
        {VK_VOLUME_MUTE, "Volume Mute"},
        {VK_VOLUME_DOWN, "Volume Down"},
        {VK_VOLUME_UP, "Volume Up"},
        {VK_MEDIA_NEXT_TRACK, "Next Track"},
        {VK_MEDIA_PREV_TRACK, "Previous Track"},
        {VK_MEDIA_STOP, "Media Stop"},
        {VK_MEDIA_PLAY_PAUSE, "Play/Pause"},
        {VK_LAUNCH_MAIL, "Launch Mail"},
        {VK_LAUNCH_MEDIA_SELECT, "Launch Media"},
        {VK_LAUNCH_APP1, "Launch App1"},
        {VK_LAUNCH_APP2, "Launch App2"},
        // Function keys
        {VK_F1, "F1"},
        {VK_F2, "F2"},
        {VK_F3, "F3"},
        {VK_F4, "F4"},
        {VK_F5, "F5"},
        {VK_F6, "F6"},
        {VK_F7, "F7"},
        {VK_F8, "F8"},
        {VK_F9, "F9"},
        {VK_F10, "F10"},
        {VK_F11, "F11"},
        {VK_F12, "F12"},
        {VK_F13, "F13"},
        {VK_F14, "F14"},
        {VK_F15, "F15"},
        {VK_F16, "F16"},
        {VK_F17, "F17"},
        {VK_F18, "F18"},
        {VK_F19, "F19"},
        {VK_F20, "F20"},
        {VK_F21, "F21"},
        {VK_F22, "F22"},
        {VK_F23, "F23"},
        {VK_F24, "F24"},
        {VK_NUMPAD0, "Numpad 0"},
        {VK_NUMPAD1, "Numpad 1"},
        {VK_NUMPAD2, "Numpad 2"},
        {VK_NUMPAD3, "Numpad 3"},
        {VK_NUMPAD4, "Numpad 4"},
        {VK_NUMPAD5, "Numpad 5"},
        {VK_NUMPAD6, "Numpad 6"},
        {VK_NUMPAD7, "Numpad 7"},
        {VK_NUMPAD8, "Numpad 8"},
        {VK_NUMPAD9, "Numpad 9"},
        {VK_MULTIPLY, "Numpad *"},
        {VK_ADD, "Numpad +"},
        {VK_SEPARATOR, "Numpad Separator"},
        {VK_SUBTRACT, "Numpad -"},
        {VK_DECIMAL, "Numpad ."},
        {VK_DIVIDE, "Numpad /"},
        // Modifier keys left/right versions
        {VK_LSHIFT, "Left Shift"},
        {VK_RSHIFT, "Right Shift"},
        {VK_LCONTROL, "Left Ctrl"},
        {VK_RCONTROL, "Right Ctrl"},
        {VK_LMENU, "Left Alt"},
        {VK_RMENU, "Right Alt"}};

    auto it = keyMap.find(vk);
    if (it != keyMap.end())
      return it->second;

    UINT scanCode = MapVirtualKeyA(vk, MAPVK_VK_TO_VSC);
    switch (vk) {
      case VK_LEFT:
      case VK_UP:
      case VK_RIGHT:
      case VK_DOWN:
      case VK_PRIOR:
      case VK_NEXT:
      case VK_END:
      case VK_HOME:
      case VK_INSERT:
      case VK_DELETE:
      case VK_DIVIDE:
      case VK_NUMLOCK:
        scanCode |= 0x100;
        break;
    }

    char keyName[128] = {};
    if (GetKeyNameTextA(scanCode << 16, keyName, sizeof(keyName)) && keyName[0] != '\0')
      return std::string(keyName);

    char fallback[32];
    sprintf_s(fallback, "[VK_%d]", vk);
    return std::string(fallback);
  };

  if (!waitingForKey) {
    if (ImGui::Button(GetKeyName(*k).c_str(), size_arg)) {
      waitingForKey = true;
      justOpened    = true;
    }
  } else {
    ImGui::Button("...", size_arg);
    Sleep(20);

    if (justOpened) {
      justOpened = false;
      return;
    }

    for (int vk = 1; vk <= 254; ++vk) {
      if (GetAsyncKeyState(vk) & 0x8000) {
        *k            = vk;
        waitingForKey = false;
        break;
      }
    }
  }
}
