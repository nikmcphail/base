#pragma once

#include <cstdint>

class address_t {
#define default_template template <typename t = address_t>

  uintptr_t addr{};

public:
  address_t(uintptr_t addr) { this->addr = addr; }
  address_t(void* addr) { this->addr = (uintptr_t)addr; }
  address_t() {}

  operator uintptr_t() { return addr; }

  __forceinline uintptr_t base() { return addr; }

  default_template __forceinline t add(uintptr_t num) {
    return reinterpret_cast<t>(addr + num);
  }

  default_template __forceinline t sub(uintptr_t num) {
    return reinterpret_cast<t>(addr - num);
  }

  default_template __forceinline t get(size_t n = 1) {
    if (!addr)
      return t{};

    uintptr_t out = addr;

    for (auto i = 0; i < n; i++) {
      if (!out)
        return t{};
      out = *reinterpret_cast<uintptr_t*>(out);
    }
    return reinterpret_cast<t>(out);
  }

  default_template __forceinline t rel32(const uintptr_t offset = 0) {

    uintptr_t out;
    int32_t   r;

    out = addr + offset;

    // get rel32 offset.
    r = *(int32_t*)out;
    if (!r)
      return t{};

    // relative to address of next instruction.
    out = (out + 4) + r;

    return (t)out;
  }
};