#pragma once

#include <cmath>

class qangle_t {
public:
  float x, y, z;

  qangle_t() = default;
  qangle_t(float X, float Y, float Z);

  void initialize(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);

  float length() const;
  float length_sqr() const;

  float     operator[](int i) const;
  float&    operator[](int i);
  bool      operator==(const qangle_t& v) const;
  bool      operator!=(const qangle_t& v) const;
  qangle_t& operator+=(const qangle_t& v);
  qangle_t& operator-=(const qangle_t& v);
  qangle_t& operator*=(float fl);
  qangle_t& operator/=(float fl);

  qangle_t& operator=(const qangle_t& v);

  qangle_t operator-(void) const;

  qangle_t operator+(const qangle_t& v) const;
  qangle_t operator-(const qangle_t& v) const;
  qangle_t operator*(float fl) const;
  qangle_t operator/(float fl) const;
};

inline qangle_t::qangle_t(float X, float Y, float Z) {
  x = X;
  y = Y;
  z = Z;
}

inline void qangle_t::initialize(float ix, float iy, float iz) {
  x = ix;
  y = iy;
  z = iz;
}

inline float qangle_t::length() const { return (float)sqrtf(length_sqr()); }

inline float qangle_t::length_sqr() const { return x * x + y * y + z * z; }

inline float qangle_t::operator[](int i) const { return ((float*)this)[i]; }

inline float& qangle_t::operator[](int i) { return ((float*)this)[i]; }

inline bool qangle_t::operator==(const qangle_t& v) const {
  return (v.x == x) && (v.y == y) && (v.z == z);
}

inline bool qangle_t::operator!=(const qangle_t& v) const {
  return (v.x != x) && (v.y != y) && (v.z != z);
}

inline qangle_t& qangle_t::operator+=(const qangle_t& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

inline qangle_t& qangle_t::operator-=(const qangle_t& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

inline qangle_t& qangle_t::operator*=(float fl) {
  x *= fl;
  y *= fl;
  z *= fl;
  return *this;
}

inline qangle_t& qangle_t::operator/=(float fl) {
  float oofl = 1.0f / fl;
  x *= oofl;
  y *= oofl;
  z *= oofl;
  return *this;
}

inline qangle_t& qangle_t::operator=(const qangle_t& v) {
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

inline qangle_t qangle_t::operator-(void) const {
  qangle_t ret(-x, -y, -z);
  return ret;
}

inline qangle_t qangle_t::operator+(const qangle_t& v) const {
  qangle_t res;
  res.x = x + v.x;
  res.y = y + v.y;
  res.z = z + v.z;
  return res;
}

inline qangle_t qangle_t::operator-(const qangle_t& v) const {
  qangle_t res;
  res.x = x - v.x;
  res.y = y - v.y;
  res.z = z - v.z;
  return res;
}

inline qangle_t qangle_t::operator*(float fl) const {
  qangle_t res;
  res.x = x * fl;
  res.y = y * fl;
  res.z = z * fl;
  return res;
}

inline qangle_t qangle_t::operator/(float fl) const {
  qangle_t res;
  res.x = x / fl;
  res.y = y / fl;
  res.z = z / fl;
  return res;
}
