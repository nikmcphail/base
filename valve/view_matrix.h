#pragma once

#include "valve/vector3.h"
#include "valve/matrix3x4.h"

#include <memory>

class view_matrix_t {
public:
  view_matrix_t() = default;
  view_matrix_t(float m00, float m01, float m02, float m03, float m10, float m11, float m12,
                float m13, float m20, float m21, float m22, float m23, float m30, float m31,
                float m32, float m33);

  view_matrix_t(const vector3_t& x_axis, const vector3_t& y_axis, const vector3_t& z_axis);
  view_matrix_t(const vector3_t& x_axis, const vector3_t& y_axis, const vector3_t& z_axis,
                const vector3_t& translation);

  view_matrix_t(const matrix_3x4_t& matrix3x4);

  void init(float m00, float m01, float m02, float m03, float m10, float m11, float m12,
            float m13, float m20, float m21, float m22, float m23, float m30, float m31,
            float m32, float m33);

  void init(const matrix_3x4_t& matrix3x4);

  inline float*       operator[](int i) { return m[i]; }
  inline const float* operator[](int i) const { return m[i]; }

  float m[4][4];
};

inline view_matrix_t::view_matrix_t(float m00, float m01, float m02, float m03, float m10,
                                    float m11, float m12, float m13, float m20, float m21,
                                    float m22, float m23, float m30, float m31, float m32,
                                    float m33) {
  init(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
}

inline view_matrix_t::view_matrix_t(const vector3_t& x_axis, const vector3_t& y_axis,
                                    const vector3_t& z_axis) {
  init(x_axis.x, y_axis.x, z_axis.x, 0.0f, x_axis.y, y_axis.y, z_axis.y, 0.0f, x_axis.z,
       y_axis.z, z_axis.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

inline view_matrix_t::view_matrix_t(const vector3_t& x_axis, const vector3_t& y_axis,
                                    const vector3_t& z_axis, const vector3_t& translation) {
  init(x_axis.x, y_axis.x, z_axis.x, translation.x, x_axis.y, y_axis.y, z_axis.y, translation.y,
       x_axis.z, y_axis.z, z_axis.z, translation.z, 0.0f, 0.0f, 0.0f, 1.0f);
}

inline view_matrix_t::view_matrix_t(const matrix_3x4_t& matrix3x4) { init(matrix3x4); }

inline void view_matrix_t::init(float m00, float m01, float m02, float m03, float m10,
                                float m11, float m12, float m13, float m20, float m21,
                                float m22, float m23, float m30, float m31, float m32,
                                float m33) {
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;

  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;

  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;

  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

inline void view_matrix_t::init(const matrix_3x4_t& matrix3x4) {
  memcpy(m, matrix3x4.base(), sizeof(matrix_3x4_t));

  m[3][0] = 0.0f;
  m[3][1] = 0.0f;
  m[3][2] = 0.0f;
  m[3][3] = 1.0f;
}
