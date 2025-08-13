#include "key_values.h"

#include "client/client.h"
#include "client/core/global_addresses/global_addresses.h"

key_values_t::key_values_t(const char* name) {
  static auto func = (void(__fastcall*)(
      void*, const char*))client::g_addresses.client.functions.key_values_init;
  func(this, name);
}

bool key_values_t::load_from_buffer(const char* resource_name, const char* buffer,
                                    void* file_system, const char* path_id) {
  static auto func =
      (bool(__fastcall*)(void*, const char*, const char*, void*,
                         const char*))client::g_addresses.client.functions.load_from_buffer;
  return func(this, resource_name, buffer, file_system, path_id);
}