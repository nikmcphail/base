#pragma once

#include <windows.h>
#include "valve/vector3.h"

struct matrix_3x4_t {
  matrix_3x4_t() = default;
  matrix_3x4_t(float m00, float m01, float m02, float m03, float m10, float m11, float m12,
               float m13, float m20, float m21, float m22, float m23) {
    values[0][0] = m00;
    values[0][1] = m01;
    values[0][2] = m02;
    values[0][3] = m03;
    values[1][0] = m10;
    values[1][1] = m11;
    values[1][2] = m12;
    values[1][3] = m13;
    values[2][0] = m20;
    values[2][1] = m21;
    values[2][2] = m22;
    values[2][3] = m23;
  }

  void init(const vector3_t& x_axis, const vector3_t& y_axis, const vector3_t& z_axis,
            const vector3_t& origin) {
    values[0][0] = x_axis.x;
    values[0][1] = y_axis.x;
    values[0][2] = z_axis.x;
    values[0][3] = origin.x;
    values[1][0] = x_axis.y;
    values[1][1] = y_axis.y;
    values[1][2] = z_axis.y;
    values[1][3] = origin.y;
    values[2][0] = x_axis.z;
    values[2][1] = y_axis.z;
    values[2][2] = z_axis.z;
    values[2][3] = origin.z;
  }

  matrix_3x4_t(const vector3_t& x_axis, const vector3_t& y_axis, const vector3_t& z_axis,
               const vector3_t& origin) {
    init(x_axis, y_axis, z_axis, origin);
  }

  float*       operator[](int i) { return values[i]; }
  const float* operator[](int i) const { return values[i]; }
  float*       base() { return &values[0][0]; }
  const float* base() const { return &values[0][0]; }

  bool is_zero() const {
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 4; ++j)
        if (values[i][j] != 0.0f)
          return false;
    return true;
  }

  float values[3][4];
};