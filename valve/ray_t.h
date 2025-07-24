#pragma once

#include "valve/vector3.h"
#include "valve/vector2.h"

class ray_t {
public:
  vector3_a_t start;
  vector3_a_t delta;
  vector3_a_t start_offset;
  vector3_a_t extents;
  bool        is_ray;
  bool        is_swept;

  void init(vector3_t const& start, vector3_t const& end) {
    vector_subtract(start, end, delta);
    this->is_swept = this->delta.length_sqr() != 0;
    this->extents  = vector3_t{0.0f, 0.0f, 0.0f};
    this->is_ray   = true;

    this->start_offset = vector3_t{0.0f, 0.0f, 0.0f};
    this->start        = start;
  }

  void init(vector3_t const& start, vector3_t const& end, vector3_t const& mins,
            vector3_t const& maxs) {
    vector_subtract(start, end, delta);

    this->is_swept = this->delta.length() != 0;

    vector_subtract(maxs, mins, extents);
    this->extents *= 0.5f;
    this->is_ray = this->extents.length_sqr() < 1e-6;

    vector3_t offset = (mins + maxs) * 0.5f;

    this->start        = (start + offset);
    this->start_offset = offset;
    this->start_offset *= -1.0f;
  }

  ray_t() {}

  ray_t(vector3_t vec_start, vector3_t vec_end) { init(vec_start, vec_end); }
  ray_t(vector3_t vec_start, vector3_t vec_end, vector3_t mins, vector3_t maxs) {
    init(vec_start, vec_end, mins, maxs);
  }
};