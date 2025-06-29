#include <Windows.h>
#include <thread>

#include "client/client.h"

unsigned long WINAPI Init(void* arg) {
  if (client::initialize()) {
    while (!client::should_unload())
      std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  client::unload();
  std::this_thread::sleep_for(std::chrono::seconds(1));

  FreeLibraryAndExitThread(static_cast<HMODULE>(arg), EXIT_SUCCESS);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  if (fdwReason == DLL_PROCESS_ATTACH) {
    auto handle = CreateThread(nullptr, 0, Init, hinstDLL, 0, nullptr);
    if (handle) {
      CloseHandle(handle);
    }
  }

  return TRUE;
}