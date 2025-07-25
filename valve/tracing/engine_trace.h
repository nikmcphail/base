#pragma once

#include <cstdint>

#include "library/utils.h"

#include "valve/vector3.h"
#include "mask_defines.h"
#include "trace_filter.h"

struct trace_t;

struct ray_t {
  vector3_a_t m_start;
  vector3_a_t m_delta;
  vector3_a_t m_start_offset;
  vector3_a_t m_extents;
  bool        m_is_ray;
  bool        m_is_swept;

  void initialize(const vector3_t& start, const vector3_t& end) {
    vector_subtract(end, start, m_delta);
    m_is_swept = (m_delta.length_sqr() != 0.f);
    vector_clear(m_extents);
    m_is_ray = true;
    vector_clear(m_start_offset);
    vector_copy(start, m_start);
  }

  void initialize(const vector3_t& start, const vector3_t& end, const vector3_t& mins,
                  const vector3_t& maxs) {
    vector_subtract(end, start, m_delta);
    m_is_swept = (m_delta.length_sqr() != 0);
    vector_subtract(maxs, mins, m_extents);
    m_extents *= 0.5f;
    m_is_ray = (m_extents.length_sqr() < 1e-6);
    vector_add(mins, maxs, m_start_offset);
    m_start_offset *= 0.5f;
    vector_add(start, m_start_offset, m_start);
    m_start_offset *= -1.0f;
  }

  ray_t() {}

  ray_t(vector3_t vec_start, vector3_t vec_end) { initialize(vec_start, vec_end); }
  ray_t(vector3_t vec_start, vector3_t vec_end, vector3_t min, vector3_t max) {
    initialize(vec_start, vec_end, min, max);
  }
};

class engine_trace_t {
public:
  void trace_ray(const ray_t& ray, uint64_t mask, i_trace_filter_t* filter, trace_t* trace) {
    typedef void(__fastcall * trace_ray_fn)(void*, const ray_t&, uint64_t, i_trace_filter_t*,
                                            trace_t*);
    return utils::get_virtual_function<trace_ray_fn>(this, 4)(this, ray, mask, filter, trace);
  }
};