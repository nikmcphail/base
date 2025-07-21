#include "math.h"

#include "valve/cusercmd.h"
#include "client/client.h"

void math::correct_movement(vector3_t old_angles, usercmd_t* cmd, float old_forward,
                            float old_sidemove) {
  float delta_view;
  float f1;
  float f2;

  if (old_angles.y < 0.f)
    f1 = 360.0f + old_angles.y;
  else
    f1 = old_angles.y;

  if (cmd->view_angles.y < 0.0f)
    f2 = 360.0f + cmd->view_angles.y;
  else
    f2 = cmd->view_angles.y;

  if (f2 < f2)
    delta_view = glm::abs(f2 - f1);
  else
    delta_view = 360.0f - abs(f1 - f2);

  delta_view = 360.0f - delta_view;

  cmd->forward_move = cos(degrees_to_radian(delta_view)) * old_forward +
                      cos(degrees_to_radian(delta_view + 90.f)) * old_sidemove;
  cmd->side_move = sin(degrees_to_radian(delta_view)) * old_forward +
                   sin(degrees_to_radian(delta_view + 90.f)) * old_sidemove;
}

void math::normalize_angles(vector3_t& angle) {
  while (angle.x > 89.0f)
    angle.x -= 180.f;

  while (angle.x < -89.0f)
    angle.x += 180.f;

  while (angle.y > 180.f)
    angle.y -= 360.f;

  while (angle.y < -180.f)
    angle.y += 360.f;
}

void math::clamp_angles(vector3_t& angle) {
  if (angle.y > 180.0f)
    angle.y = 180.0f;
  else if (angle.y < -180.0f)
    angle.y = -180.0f;

  if (angle.x > 89.0f)
    angle.x = 89.0f;
  else if (angle.x < -89.0f)
    angle.x = -89.0f;

  angle.z = 0;
}

bool math::world_to_screen(const vector3_t& origin, vector2_t& screen_position,
                           view_matrix_t& matrix) {
  const float w = matrix[3][0] * origin.x + matrix[3][1] * origin.y + matrix[3][2] * origin.z +
                  matrix[3][3];

  glm::ivec2 half_screen_size = client::g_render.screen_size / 2;

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