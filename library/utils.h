#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace utils {
  template <typename T> T get_virtual_function(void* base, std::uint16_t index) noexcept {
    return (*static_cast<T**>(base))[index];
  }

  inline void* resolve_rel32(uintptr_t address, int offset) {
    uintptr_t address_with_offset = address + offset;
    int32_t   rel_offset          = *reinterpret_cast<int32_t*>(address_with_offset);
    if (rel_offset == 0)
      return nullptr;

    uintptr_t target = address_with_offset + 4 + rel_offset;
    return reinterpret_cast<void*>(target);
  }

  // UTF-16 -> UTF-8.
  extern std::string str_utf16_to_8(std::wstring_view str) noexcept;

  // UTF-8 -> UTF-16.
  extern std::wstring str_utf8_to_16(std::string_view str) noexcept;
} // namespace utils