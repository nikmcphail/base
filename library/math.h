#pragma once

#include <array>
#include <glm/geometric.hpp>
#include <glm/common.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x4.hpp>
#include <glm/gtc/type_aligned.hpp>
#include <algorithm>
#include <numbers>
#include <optional>
#include <vector>

using vector2_t      = glm::vec2;
using vector3_t      = glm::vec3;
using vector3_a_t    = glm::aligned_vec3;
using vector4_t      = glm::vec4;
using matrix_3x4_a_t = glm::aligned_mat3x4;
using matrix_3x4_t   = glm::mat3x4;
using view_matrix_t  = glm::mat<4, 4, float, glm::defaultp>;

namespace math {
  constexpr double PI   = 3.14159265358979323846;
  constexpr double PI_2 = 1.57079632679489661923;
  constexpr float  radian_to_degrees(const double x) { return x * (180.f / PI); }
  constexpr float  degrees_to_radian(const float x) { return x * (PI / 180.f); }

  inline vector3_t vector_transform(matrix_3x4_t& matrix, vector3_t offset) {
    return vector3_t{glm::dot(offset, vector3_t(matrix[0])) + matrix[0][3],
                     glm::dot(offset, vector3_t(matrix[1])) + matrix[1][3],
                     glm::dot(offset, vector3_t(matrix[2])) + matrix[2][3]};
  }
} // namespace math