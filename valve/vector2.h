#pragma once

#include <cmath>

class vector2_t {
public:
  float x, y;

  vector2_t() = default;
  vector2_t(float X, float Y);
  vector2_t(const float* v);

  void initialize(float ix = 0.0f, float iy = 0.0f);

  float length() const;
  float length_sqr() const;

  bool  is_zero(float tolerance = 0.01f) const;
  float dot(const vector2_t& v) const;
  float normalize_in_place();
  float dist_to(const vector2_t& other) const;

  float      operator[](int i) const;
  float&     operator[](int i);
  bool       operator==(const vector2_t& v) const;
  bool       operator!=(const vector2_t& v) const;
  vector2_t& operator+=(const vector2_t& v);
  vector2_t& operator-=(const vector2_t& v);
  vector2_t& operator*=(const vector2_t& v);
  vector2_t& operator*=(float fl);
  vector2_t& operator/=(const vector2_t& v);
  vector2_t& operator/=(float fl);

  vector2_t& operator=(const vector2_t& v);

  vector2_t operator-(void) const;

  vector2_t operator+(const vector2_t& v) const;
  vector2_t operator-(const vector2_t& v) const;
  vector2_t operator*(const vector2_t& v) const;
  vector2_t operator*(float fl) const;
  vector2_t operator/(const vector2_t& v) const;
  vector2_t operator/(float fl) const;
};

inline void vector_2d_add(const vector2_t& a, const vector2_t& b, vector2_t& c) {
  c.x = a.x + b.x;
  c.y = a.y + b.y;
}

inline void vector_2d_subtract(const vector2_t& a, const vector2_t& b, vector2_t& c) {
  c.x = a.x - b.x;
  c.y = a.y - b.y;
}

inline void vector_2d_multiply(const vector2_t& a, const vector2_t& b, vector2_t& c) {
  c.x = a.x * b.x;
  c.y = a.y * b.y;
}

inline void vector_2d_multiply(const vector2_t& a, float b, vector2_t& c) {
  c.x = a.x * b;
  c.y = a.y * b;
}

inline void vector_2d_divide(const vector2_t& a, const vector2_t& b, vector2_t& c) {
  c.x = a.x / b.x;
  c.y = a.y / b.y;
}

inline void vector_2d_divide(const vector2_t& a, float b, vector2_t& c) {
  float oob = 1.0f / b;
  c.x       = a.x * oob;
  c.y       = a.y * oob;
}

inline float dot_product_2d(const vector2_t& a, const vector2_t& b) {
  return (a.x * b.x + a.y * b.y);
}

inline float vector_2d_normalize(vector2_t& v) {
  float l = v.length();
  if (l != 0.0f) {
    v /= l;
  } else {
    v.x = v.y = 0.0f;
  }
  return l;
}

inline vector2_t::vector2_t(float X, float Y) {
  x = X;
  y = Y;
}

inline vector2_t::vector2_t(const float* v) {
  x = v[0];
  y = v[1];
}

inline void vector2_t::initialize(float ix, float iy) {
  x = ix;
  y = iy;
}

inline float vector2_t::length() const { return (float)sqrtf(x * x + y * y); }

inline float vector2_t::length_sqr() const { return (x * x + y * y); }

inline bool vector2_t::is_zero(float tolerance) const {
  return (x > -tolerance && x < tolerance && y > -tolerance && y < tolerance);
}

inline float vector2_t::dot(const vector2_t& v) const { return dot_product_2d(*this, v); }

inline float vector2_t::normalize_in_place() { return vector_2d_normalize(*this); }

inline float vector2_t::operator[](int i) const { return ((float*)this)[i]; }

inline float& vector2_t::operator[](int i) { return ((float*)this)[i]; }

inline bool vector2_t::operator==(const vector2_t& v) const { return (v.x == x) && (v.y == y); }

inline bool vector2_t::operator!=(const vector2_t& v) const { return (v.x != x) && (v.y != y); }

inline vector2_t& vector2_t::operator+=(const vector2_t& v) {
  x += v.x;
  y += v.y;
  return *this;
}

inline vector2_t& vector2_t::operator-=(const vector2_t& v) {
  x -= v.x;
  y -= v.y;
  return *this;
}

inline vector2_t& vector2_t::operator*=(const vector2_t& v) {
  x *= v.x;
  y *= v.y;
  return *this;
}

inline vector2_t& vector2_t::operator*=(float fl) {
  x *= fl;
  y *= fl;
  return *this;
}

inline vector2_t& vector2_t::operator/=(const vector2_t& v) {
  x /= v.x;
  y /= v.y;
  return *this;
}

inline vector2_t& vector2_t::operator/=(float fl) {
  x /= fl;
  y /= fl;
  return *this;
}

inline vector2_t& vector2_t::operator=(const vector2_t& v) {
  x = v.x;
  y = v.y;
  return *this;
}

inline vector2_t vector2_t::operator-(void) const { return vector2_t(-x, -y); }

inline vector2_t vector2_t::operator+(const vector2_t& v) const {
  vector2_t res;
  vector_2d_add(*this, v, res);
  return res;
}

inline vector2_t vector2_t::operator-(const vector2_t& v) const {
  vector2_t res;
  vector_2d_subtract(*this, v, res);
  return res;
}

inline vector2_t vector2_t::operator*(const vector2_t& v) const {
  vector2_t res;
  vector_2d_multiply(*this, v, res);
  return res;
}

inline vector2_t vector2_t::operator*(float fl) const {
  vector2_t res;
  vector_2d_multiply(*this, fl, res);
  return res;
}

inline vector2_t vector2_t::operator/(const vector2_t& v) const {
  vector2_t res;
  vector_2d_divide(*this, v, res);
  return res;
}

inline vector2_t vector2_t::operator/(float fl) const {
  vector2_t res;
  vector_2d_divide(*this, fl, res);
  return res;
}

inline float vector2_t::dist_to(const vector2_t& other) const {
  vector2_t delta;
  vector_2d_subtract(*this, other, delta);
  return delta.length();
}