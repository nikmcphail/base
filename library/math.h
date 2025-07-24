#pragma once

#include "valve/vector3.h"
#include "valve/matrix3x4.h"
#include "valve/view_matrix.h"

namespace math {
	inline vector3_t vector_transform(matrix_3x4_t& matrix, vector3_t offset) {
    return vector3_t{offset.dot(vector3_t(matrix[0])) + matrix[0][3],
                     offset.dot(vector3_t(matrix[1])) + matrix[1][3],
                     offset.dot(vector3_t(matrix[2])) + matrix[2][3]};
  }

    bool world_to_screen(const vector3_t& origin, vector2_t& screen_position,
                       view_matrix_t& matrix);
};