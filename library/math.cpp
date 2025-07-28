#include "math.h"

#include "valve/vector3.h"
#include "valve/view_matrix.h"
#include "valve/vector2.h"
#include "client/client.h"
#include "valve/matrix3x4.h"
#include "valve/qangle.h"

void sin_cos(float radians, float* sine, float* cosine) {
  *sine   = sinf(radians);
  *cosine = cosf(radians);
}

bool math::world_to_screen(const vector3_t& origin, vector2_t& screen_position,
                           view_matrix_t& matrix) {
  const float w = matrix[3][0] * origin.x + matrix[3][1] * origin.y + matrix[3][2] * origin.z +
                  matrix[3][3];

  vector2_t half_screen_size = client::g_render.screen_size / 2;

#undef min
  if (w <= std::numeric_limits<float>::min())
    return false;

  screen_position.x = static_cast<float>(half_screen_size.x);
  screen_position.y = static_cast<float>(half_screen_size.y);

  screen_position.x *= 1 + (matrix[0][0] * origin.x + matrix[0][1] * origin.y +
                            matrix[0][2] * origin.z + matrix[0][3]) /
                               w;
  screen_position.y *= 1 - (matrix[1][0] * origin.x + matrix[1][1] * origin.y +
                            matrix[1][2] * origin.z + matrix[1][3]) /
                               w;

  return true;
}

vector3_t math::vector_transform(matrix_3x4_t& matrix, vector3_t offset) {
  return vector3_t{offset.dot(vector3_t(matrix[0])) + matrix[0][3],
                   offset.dot(vector3_t(matrix[1])) + matrix[1][3],
                   offset.dot(vector3_t(matrix[2])) + matrix[2][3]};
}

void math::angle_vectors(const qangle_t& angles, vector3_t* forward) {
  float sp, sy, cp, cy;
  sin_cos(degrees_to_radian(angles[1]), &sy, &cy);
  sin_cos(degrees_to_radian(angles[0]), &sp, &cp);

  forward->x = cp * cy;
  forward->y = cp * sy;
  forward->z = -sp;
}
