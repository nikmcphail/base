#pragma once

class vector2_t {
public:
  float x, y;

  vector2_t operator/(float fl) const;
  float     length() const;
};

inline vector2_t vector2_t::operator/(float fl) const {
  vector2_t res;
  float     oofl = 1.0f / fl;
  res.x          = x * oofl;
  res.y          = y * oofl;
  return res;
}

inline float vector2_t::length() const { return (float)sqrtf(x * x + y * y); }