#pragma once

#include "library/utils.h"
#include "client/client.h"
#include "client/core/global_addresses/global_addresses.h"

class key_values_t {

public:
  key_values_t(const char* name) {
    static auto func = (void(__fastcall*)(
        void*, const char*))client::g_addresses.client.functions.key_values_init;
    func(this, name);
  }

  bool load_from_buffer(const char* resource_name, const char* buffer, void* file_system = NULL,
                        const char* path_id = NULL) {
    static auto func =
        (bool(__fastcall*)(void*, const char*, const char*, void*,
                           const char*))client::g_addresses.client.functions.load_from_buffer;
    return func(this, resource_name, buffer, file_system, path_id);
  }
};