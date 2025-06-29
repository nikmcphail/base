#pragma once

#include <Windows.h>
#include <minwindef.h>
#include <objidlbase.h>
#include <winnt.h>
#include <winternl.h>

#include <cstdint>
#include <map>
#include <string_view>
#include <string>
#include <vector>

#include "address.h"
#include "hash.h"
#include "valve/interface_reg.h"

namespace pe {
  struct module_t {
    std::map<uint32_t, uintptr_t> interface_cache = {};
    uint8_t*                      base_           = nullptr;

    module_t(uintptr_t ptr) {
      base_ = reinterpret_cast<uint8_t*>(ptr);
      populate_interfaces();
    }

    module_t() {}

    ~module_t() { flush_interfaces(); }

    uint8_t* base() { return base_; }

    IMAGE_DOS_HEADER* dos_header() { return reinterpret_cast<IMAGE_DOS_HEADER*>(base()); }

    IMAGE_NT_HEADERS* nt_headers() {
      return reinterpret_cast<IMAGE_NT_HEADERS*>(base() + dos_header()->e_lfanew);
    }

    inline uint8_t* get_export(uint64_t hash) {
      auto export_dir =
          nt_headers()->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
      auto exports =
          reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>((base() + export_dir.VirtualAddress));
      if (!export_dir.VirtualAddress) {
        return nullptr;
      }

      auto functions = reinterpret_cast<uintptr_t*>((base() + exports->AddressOfFunctions));
      auto names     = reinterpret_cast<uintptr_t*>(base() + exports->AddressOfNames);
      auto ordinals  = reinterpret_cast<uint16_t*>(base() + exports->AddressOfNameOrdinals);
      for (size_t i = 0; i < exports->NumberOfNames; i++) {
        if (hash::hash_crc(reinterpret_cast<char*>(base() + names[i])) != hash) {
          continue;
        }

        return base() + functions[ordinals[i]];
      }

      return nullptr;
    }

    inline uint8_t* get_export(std::string_view name) {
      return get_export(hash::hash_crc(name.data(), name.size()));
    }

    inline bool populate_interfaces() {
      uintptr_t interface_registry =
          find_pattern_in_memory("4C 8B 0D ?? ?? ?? ?? 4C 8B D2").rel32<uintptr_t>(0x3);
      if (!interface_registry) {
        return false;
      }
      interface_reg_t* interface_list =
          *reinterpret_cast<interface_reg_t**>(interface_registry);

      if (!interface_list) {
        return false;
      }

      for (interface_reg_t* current_interface = interface_list; current_interface;
           current_interface                  = current_interface->next) {
        if (!current_interface || !current_interface->create_fn)
          continue;

        interface_cache.insert({hash::hash_crc(current_interface->name),
                                reinterpret_cast<uintptr_t>(current_interface->create_fn())});
      }

      return true;
    }

    template <typename T = uintptr_t> inline T get_interface(uint32_t hash) {
      if (interface_cache.count(hash))
        return reinterpret_cast<T>(interface_cache.at(hash));
      return 0;
    }

    inline void flush_interfaces() { interface_cache.clear(); }

    inline std::vector<uintptr_t> find_all_pattern_in_memory(const char* pattern) {
      static std::vector<uintptr_t> patterns = {};
      patterns.clear();

      static auto pattern_to_byte = [](const char* pattern) {
        auto       bytes = std::vector<int>{};
        const auto start = const_cast<char*>(pattern);
        const auto end   = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current) {
          if (*current == '?') {
            ++current;

            if (*current == '?')
              ++current;

            bytes.push_back(-1);
          } else {
            bytes.push_back(std::strtoul(current, &current, 16));
          }
        }
        return bytes;
      };

      const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(base());
      const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(
          reinterpret_cast<std::uint8_t*>(base()) + dos_header->e_lfanew);

      const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
      const auto pattern_bytes = pattern_to_byte(pattern);
      const auto scan_bytes    = reinterpret_cast<std::uint8_t*>(base());

      const auto s = pattern_bytes.size();
      const auto d = pattern_bytes.data();

      for (auto i = 0ul; i < size_of_image - s; ++i) {
        auto found = true;

        for (auto j = 0ul; j < s; ++j) {
          if (scan_bytes[i + j] != d[j] && d[j] != -1) {
            found = false;
            break;
          }
        }

        if (found)
          patterns.push_back((uintptr_t)(&scan_bytes[i]));
      }

      return patterns;
    }

    inline address_t find_pattern_in_memory(const char* pattern) {
      static auto pattern_to_byte = [](const char* pattern) {
        auto       bytes = std::vector<int>{};
        const auto start = const_cast<char*>(pattern);
        const auto end   = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current) {
          if (*current == '?') {
            ++current;

            if (*current == '?')
              ++current;

            bytes.push_back(-1);
          } else {
            bytes.push_back(std::strtoul(current, &current, 16));
          }
        }
        return bytes;
      };

      const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(base());
      const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(
          reinterpret_cast<std::uint8_t*>(base()) + dos_header->e_lfanew);

      const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
      const auto pattern_bytes = pattern_to_byte(pattern);
      const auto scan_bytes    = reinterpret_cast<std::uint8_t*>(base());

      const auto s = pattern_bytes.size();
      const auto d = pattern_bytes.data();

      for (auto i = 0ul; i < size_of_image - s; ++i) {
        auto found = true;

        for (auto j = 0ul; j < s; ++j) {
          if (scan_bytes[i + j] != d[j] && d[j] != -1) {
            found = false;
            break;
          }
        }

        if (found) {
          return address_t{&scan_bytes[i]};
        }
      }

      return {};
    }
  };

  struct ldr_entry_t {
    LIST_ENTRY     InLoadOrderLinks;
    LIST_ENTRY     InMemoryOrderLinks;
    LIST_ENTRY     InInitializationOrderLinks;
    uintptr_t      DllBase;
    uintptr_t      EntryPoint;
    uint32_t       SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
  };

  inline std::map<uint32_t, module_t> module_cache = {};

  inline void flush_module_cache() { module_cache.clear(); }

  inline bool get_module(std::string module_name, module_t& module) {
    uint32_t name_hash = hash::hash_crc(module_name.c_str());
    if (module_cache.count(name_hash) != 0) {
      module = module_cache.at(name_hash);
      return true;
    }
    module_cache.insert(
        {name_hash, module_t((uintptr_t)GetModuleHandleA(module_name.c_str()))});
    module = module_cache.at(name_hash);
    return true;
  }
} // namespace pe