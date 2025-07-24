#pragma once

#include "library/utils.h"

#include "valve/ray_t.h"
#include "valve/trace_filter.h"
#include "valve/trace.h"

class engine_trace_t {
public:
  void trace_ray(const ray_t& ray, unsigned int mask, i_trace_filter_t* filter,
                 trace_t* trace) {
    utils::get_virtual_function<void(__thiscall*)(engine_trace_t*, const ray_t&, unsigned int,
                                                  i_trace_filter_t*, trace_t*)>(this, 4)(
        this, ray, mask, filter, trace);
  }
};