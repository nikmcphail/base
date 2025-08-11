#pragma once

#include <Windows.h>

class vector3_t;
class matrix_3x4_t;
class view_matrix_t;
class vector2_t;
class qangle_t;
class usercmd_t;

namespace math {
  constexpr double PI = 3.14159265358979323846;
  constexpr float  radian_to_degrees(const double x) { return x * (180.f / PI); }

  constexpr float degrees_to_radian(const float x) { return x * (PI / 180.f); }

  vector3_t vector_transform(matrix_3x4_t& matrix, vector3_t offset);

  bool     world_to_screen(const vector3_t& origin, vector2_t& screen_position,
                           view_matrix_t& matrix);
  void     angle_vector(const qangle_t& angles, vector3_t* forward);
  void     angle_vectors(const qangle_t& from, vector3_t* forward, vector3_t* right = NULL,
                         vector3_t* up = NULL);
  void     normalize_angles(qangle_t& angles);
  void     clamp_angles(qangle_t& angles);
  float    ticks_to_time(int ticks);
  int      time_to_ticks(float time);
  qangle_t calc_angle(const vector3_t& from, const vector3_t& to);
  void     vector_angles(const vector3_t& forward, qangle_t& angles);
  float    get_fov(const qangle_t& from, const qangle_t& to);
  void movement_fix(qangle_t old_angles, usercmd_t* cmd, float old_forward, float old_sidemove);
  unsigned int md5_pseudo_random(int seed);
}; // namespace math