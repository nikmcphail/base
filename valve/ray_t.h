#pragma once

#include "library/math.h"

class ray_t {
public:
  vector3_t start;
  vector3_t delta;
  vector3_t start_offset;
  vector3_t extents;
  bool      is_ray;
  bool      is_swept;

  void init(vector3_t const& start, vector3_t const& end) {
    this->delta    = end - start;
    this->is_swept = (glm::length(glm::vec2(this->delta)) != 0);
    this->extents  = {0.0f, 0.0f, 0.0f};
    this->is_ray   = true;

    this->start_offset = {0.0f, 0.0f, 0.0f};
    this->start        = start;
  }

  void init(vector3_t const& start, vector3_t const& end, vector3_t const& mins,
            vector3_t const& maxs) {
    this->delta = end - start;

    this->is_swept = (glm::length(this->delta) != 0);

    this->extents = (maxs - mins);
    this->extents *= 0.5f;
    this->is_ray = (glm::length(glm::vec2(this->extents)) < 1e-6);

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