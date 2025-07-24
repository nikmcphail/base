#pragma once

#include <cmath>

class vector2_t;

class vector3_t {
public:
  float x, y, z;

  vector3_t();
  vector3_t(float ix, float iy, float iz);
  explicit vector3_t(float XYZ);
  vector3_t(const float* v);

  void init(float ix, float iy, float iz);

  vector2_t&       as_vector_2d();
  const vector2_t& as_vector_2d() const;

  float               length() const;
  __forceinline float length_sqr();

  bool  is_zero(float tolerance = 0.01f) const;
  float dot(const vector3_t& other);

  float                    operator[](int i) const;
  float&                   operator[](int i);
  bool                     operator==(const vector3_t& v) const;
  bool                     operator!=(const vector3_t& v) const;
  __forceinline vector3_t& operator+=(const vector3_t& v);
  __forceinline vector3_t& operator-=(const vector3_t& v);
  __forceinline vector3_t& operator*=(const vector3_t& v);
  __forceinline vector3_t& operator*=(float s);
  __forceinline vector3_t& operator/=(const vector3_t& v);
  __forceinline vector3_t& operator/=(float s);
  __forceinline vector3_t& operator+=(float fl); ///< broadcast add
  __forceinline vector3_t& operator-=(float fl); ///< broadcast sub

  vector3_t operator-(void) const;

  vector3_t operator+(const vector3_t& v) const;
  vector3_t operator-(const vector3_t& v) const;
  vector3_t operator*(const vector3_t& v) const;
  vector3_t operator/(const vector3_t& v) const;
  vector3_t operator*(float fl) const;
  vector3_t operator/(float fl) const;
};

inline vector3_t::vector3_t() { x = y = z = 0.0f; }
inline vector3_t::vector3_t(float ix, float iy, float iz) {
  x = ix;
  y = iy;
  z = iz;
}

inline vector3_t::vector3_t(float XYZ) { x = y = z = XYZ; }

inline vector3_t::vector3_t(const float* v) {
  x = v[0];
  y = v[1];
  z = v[2];
}

inline void vector3_t::init(float ix, float iy, float iz) {
  x = ix;
  y = iy;
  z = iz;
}

inline vector2_t&       vector3_t::as_vector_2d() { return *(vector2_t*)this; }
inline const vector2_t& vector3_t::as_vector_2d() const { return *(const vector2_t*)this; }

inline float vector3_t::length() const { return (float)std::sqrtf(x * x + y * y + z * z); }
inline float vector3_t::length_sqr() { return (x * x + y * y + z * z); }

inline bool vector3_t::is_zero(float tolerance) const {
  return (x > -tolerance && x < tolerance && y > -tolerance && y < tolerance &&
          z > -tolerance && z < tolerance);
}

inline float vector3_t::dot(const vector3_t& other) {
  return (x * other.x + y * other.y + z * other.z);
}

inline float  vector3_t::operator[](int i) const { return ((float*)this)[i]; }
inline float& vector3_t::operator[](int i) { return ((float*)this)[i]; }

inline bool vector3_t::operator==(const vector3_t& v) const {
  return (v.x == x) && (v.y == y) && (v.z == z);
}

inline bool vector3_t::operator!=(const vector3_t& v) const {
  return (v.x != x) && (v.y != y) && (v.z != z);
}

inline vector3_t& vector3_t::operator+=(const vector3_t& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

inline vector3_t& vector3_t::operator-=(const vector3_t& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

inline vector3_t& vector3_t::operator*=(const vector3_t& v) {
  x *= v.x;
  y *= v.y;
  z *= v.z;
  return *this;
}

inline vector3_t& vector3_t::operator*=(float fl) {
  x *= fl;
  y *= fl;
  z *= fl;
  return *this;
}

inline vector3_t& vector3_t::operator/=(const vector3_t& v) {
  x /= v.x;
  y /= v.y;
  z /= v.z;
  return *this;
}

inline vector3_t& vector3_t::operator/=(float s) {
  float oos = 1.0f / s;
  x *= oos;
  y *= oos;
  z *= oos;
  return *this;
}

inline vector3_t& vector3_t::operator+=(float fl) {
  x += fl;
  y += fl;
  z += fl;
  return *this;
}

inline vector3_t& vector3_t::operator-=(float fl) {
  x -= fl;
  y -= fl;
  z -= fl;
  return *this;
}

inline vector3_t vector3_t::operator-(void) const { return vector3_t(-x, -y, -z); }

inline vector3_t vector3_t::operator+(const vector3_t& v) const {
  vector3_t res;
  res.x = x + v.x;
  res.y = y + v.y;
  res.z = y + v.z;
  return res;
}

inline vector3_t vector3_t::operator-(const vector3_t& v) const {
  vector3_t res;
  res.x = x - v.x;
  res.y = y - v.y;
  res.z = z - v.z;
  return res;
}

inline vector3_t vector3_t::operator*(const vector3_t& v) const {
  vector3_t res;
  res.x = x * v.x;
  res.y = y * v.y;
  res.z = z * v.z;
  return res;
}

inline vector3_t vector3_t::operator/(const vector3_t& v) const {
  vector3_t res;
  res.x = x / v.x;
  res.y = y / v.y;
  res.z = z / v.z;
  return res;
}

inline vector3_t vector3_t::operator*(float fl) const {
  vector3_t res;
  res.x = x * fl;
  res.y = y * fl;
  res.z = z * fl;
  return res;
}

inline vector3_t vector3_t::operator/(float fl) const {
  vector3_t res;
  res.x = x / fl;
  res.y = y / fl;
  res.z = z / fl;
  return res;
}

class vector3_a_t : public vector3_t {
public:
  float w;

  vector3_a_t(void) {}
  vector3_a_t(float X, float Y, float Z) { init(X, Y, Z); }

  vector3_a_t& operator=(const vector3_t& other) {
    init(other.x, other.y, other.z);
    return *this;
  }
};
