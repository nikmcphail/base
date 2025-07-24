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
    this->delta    = end - start;
    this->is_swept = (this->delta.as_vector_2d().length()) != 0;
    this->extents  = {0.0f, 0.0f, 0.0f};
    this->is_ray   = true;

    this->start_offset = {0.0f, 0.0f, 0.0f};
    this->start        = start;
  }

  void init(vector3_t const& start, vector3_t const& end, vector3_t const& mins,
            vector3_t const& maxs) {
    this->delta = end - start;

    this->is_swept = this->delta.length() != 0;

    this->extents = (maxs - mins);
    this->extents *= 0.5f;
    this->is_ray = this->extents.as_vector_2d().length() < 1e-6;

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