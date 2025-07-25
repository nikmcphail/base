#pragma once

class vector3_t;
class matrix_3x4_t;
class view_matrix_t;
class vector2_t;
namespace math {
  constexpr double PI = 3.14159265358979323846;
  constexpr float  radian_to_degrees(const double x) { return x * (180.f / PI); }

  constexpr float degrees_to_radian(const float x) { return x * (PI / 180.f); }

  vector3_t vector_transform(matrix_3x4_t& matrix, vector3_t offset);

  bool world_to_screen(const vector3_t& origin, vector2_t& screen_position,
                       view_matrix_t& matrix);

}; // namespace math