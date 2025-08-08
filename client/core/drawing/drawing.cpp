#include "drawing.h"

#include "library/math.h"
#include "client/client.h"
#include <fmt/core.h>
#include <array>

// private functions
void drawing_t::draw_text(const vector2_t& position, const ImU32 color, const char* text) {
  client::g_render.draw_list->AddText({position.x, position.y}, color, text);
}

void drawing_t::draw_text_outlined(const vector2_t& position, const ImU32 color,
                                   const ImU32 outline_color, const char* text) {
  draw_text({position.x, position.y - 1}, outline_color, text);
  draw_text({position.x, position.y + 1}, outline_color, text);
  draw_text({position.x - 1, position.y}, outline_color, text);
  draw_text({position.x + 1, position.y}, outline_color, text);

  draw_text(position, color, text);
}

void drawing_t::draw_circle(const vector2_t& center, float radius, const ImU32 color,
                            int segments, float thickness) {
  client::g_render.draw_list->AddCircle({center.x, center.y}, radius, color, segments,
                                        thickness);
}

void drawing_t::draw_circle_filled(const vector2_t& center, float radius, const ImU32 color,
                                   int segments) {
  client::g_render.draw_list->AddCircleFilled({center.x, center.y}, radius, color, segments);
}

void drawing_t::draw_line(const vector2_t& pos_one, const vector2_t& pos_two, const ImU32 color,
                          float thickness) {
  client::g_render.draw_list->AddLine({pos_one.x, pos_one.y}, {pos_two.x, pos_two.y}, color,
                                      thickness);
}
void drawing_t::draw_line_outlined(const vector2_t& pos_one, const vector2_t& pos_two,
                                   const ImU32 color, const ImU32 outline_color,
                                   float thickness) {
  float outline_thickness = thickness + 2.0f;

  // Draw the outline first
  client::g_render.draw_list->AddLine({pos_one.x, pos_one.y}, {pos_two.x, pos_two.y},
                                      outline_color, outline_thickness);

  // Draw the main line over it
  client::g_render.draw_list->AddLine({pos_one.x, pos_one.y}, {pos_two.x, pos_two.y}, color,
                                      thickness);
}

void drawing_t::draw_rect(const vector2_t& position, const vector2_t& size, const ImU32 color,
                          float rounding, float thickness) {
  auto max = position + size;
  client::g_render.draw_list->AddRect({position.x, position.y}, {max.x, max.y}, color, rounding,
                                      ImDrawFlags_None, thickness);
}

void drawing_t::draw_rect_outlined(const vector2_t& position, const vector2_t& size,
                                   const ImU32 color, const ImU32 outline_color, float rounding,
                                   float thickness) {
  auto max = position + size;
  client::g_render.draw_list->AddRect({position.x - thickness, position.y - thickness},
                                      {max.x + thickness, max.y + thickness}, outline_color,
                                      rounding, ImDrawFlags_None, thickness);
  client::g_render.draw_list->AddRect({position.x + thickness, position.y + thickness},
                                      {max.x - thickness, max.y - thickness}, outline_color,
                                      rounding, ImDrawFlags_None, thickness);

  client::g_render.draw_list->AddRect({position.x, position.y}, {max.x, max.y}, color, rounding,
                                      ImDrawFlags_None, thickness);
}

void drawing_t::draw_rect_filled(const vector2_t& position, const vector2_t& size,
                                 const ImU32 color, float rounding) {
  auto max = position + size;
  client::g_render.draw_list->AddRectFilled({position.x, position.y}, {max.x, max.y}, color,
                                            rounding);
}

void drawing_t::draw_quad(const vector2_t& p0, const vector2_t& p1, const vector2_t& p2,
                          const vector2_t& p3, const ImU32 color, float thickness) {
  client::g_render.draw_list->AddQuad({p0.x, p0.y}, {p1.x, p1.y}, {p2.x, p2.y}, {p3.x, p3.y},
                                      color, thickness);
}

void drawing_t::draw_quad_filled(const vector2_t& p0, const vector2_t& p1, const vector2_t& p2,
                                 const vector2_t& p3, const ImU32 color) {
  client::g_render.draw_list->AddQuadFilled({p0.x, p0.y}, {p1.x, p1.y}, {p2.x, p2.y},
                                            {p3.x, p3.y}, color);
}

void drawing_t::draw_hull(const vector3_t& origin, const vector3_t& mins, const vector3_t& maxs,
                          ImU32 color, float thickness) {
  // Compute the 8 corners of the bounding box in 3D space
  vector3_t corners[8];

  corners[0] = origin + vector3_t(mins.x, mins.y, mins.z);
  corners[1] = origin + vector3_t(maxs.x, mins.y, mins.z);
  corners[2] = origin + vector3_t(maxs.x, maxs.y, mins.z);
  corners[3] = origin + vector3_t(mins.x, maxs.y, mins.z);

  corners[4] = origin + vector3_t(mins.x, mins.y, maxs.z);
  corners[5] = origin + vector3_t(maxs.x, mins.y, maxs.z);
  corners[6] = origin + vector3_t(maxs.x, maxs.y, maxs.z);
  corners[7] = origin + vector3_t(mins.x, maxs.y, maxs.z);

  // Convert to screen space
  vector2_t screen[8];
  for (int i = 0; i < 8; ++i) {
    vector2_t projected;
    if (!math::world_to_screen(corners[i], projected, client::g_render.view_matrix))
      return;

    if (projected == vector2_t())
      return;

    screen[i] = projected;
  }

  // Vertical edges
  for (int i = 0; i < 4; i++) {
    draw_line(screen[i], screen[i + 4], color, thickness);
  }

  // Top face edges
  for (int i = 4; i < 8; i++) {
    draw_line(screen[i], screen[(i == 7) ? 4 : i + 1], color, thickness);
  }

  // Bottom face edges
  for (int i = 0; i < 4; i++) {
    draw_line(screen[i], screen[(i + 1) % 4], color, thickness);
  }
}

void drawing_t::draw_hull_filled(const vector3_t& origin, const vector3_t& mins,
                                 const vector3_t& maxs, ImU32 line_color, ImU32 fill_color,
                                 float thickness, float fill_alpha) {
  vector3_t corners[8];

  // Compute the 8 corners in 3D
  corners[0] = origin + vector3_t(mins.x, mins.y, mins.z);
  corners[1] = origin + vector3_t(maxs.x, mins.y, mins.z);
  corners[2] = origin + vector3_t(maxs.x, maxs.y, mins.z);
  corners[3] = origin + vector3_t(mins.x, maxs.y, mins.z);

  corners[4] = origin + vector3_t(mins.x, mins.y, maxs.z);
  corners[5] = origin + vector3_t(maxs.x, mins.y, maxs.z);
  corners[6] = origin + vector3_t(maxs.x, maxs.y, maxs.z);
  corners[7] = origin + vector3_t(mins.x, maxs.y, maxs.z);

  // Project to screen space
  vector2_t screen[8];
  for (int i = 0; i < 8; ++i) {
    vector2_t projected;
    if (!math::world_to_screen(corners[i], projected, client::g_render.view_matrix))
      return;
    if (projected == vector2_t())
      return;
    screen[i] = projected;
  }

  // Adjust alpha for fill
  ImU32 translucent_fill =
      IM_COL32((fill_color >> IM_COL32_R_SHIFT) & 0xFF, (fill_color >> IM_COL32_G_SHIFT) & 0xFF,
               (fill_color >> IM_COL32_B_SHIFT) & 0xFF,
               static_cast<int>(fill_alpha * 255.0f) // fill_alpha is 0.0f to 1.0f
      );

  // Each face of the box (CCW order)
  static const int faces[6][4] = {
      {0, 1, 2, 3}, // bottom
      {4, 5, 6, 7}, // top
      {0, 1, 5, 4}, // front
      {2, 3, 7, 6}, // back
      {1, 2, 6, 5}, // right
      {0, 3, 7, 4}  // left
  };

  // Fill faces
  for (auto& face : faces) {
    draw_quad_filled(screen[face[0]], screen[face[1]], screen[face[2]], screen[face[3]],
                     translucent_fill);
  }

  // Outline edges
  for (int i = 0; i < 4; i++)
    draw_line(screen[i], screen[i + 4], line_color, thickness);

  for (int i = 4; i < 8; i++)
    draw_line(screen[i], screen[(i == 7) ? 4 : i + 1], line_color, thickness);

  for (int i = 0; i < 4; i++)
    draw_line(screen[i], screen[(i + 1) % 4], line_color, thickness);
}

// public functions
void drawing_t::add_line(const vector2_t& position_one, const vector2_t& position_two,
                         const ImU32 color, float thickness, bool outlined,
                         const ImU32 outline_color) {
  initial.push_back(
      line_t{position_one, position_two, color, outline_color, outlined, thickness});
}

void drawing_t::add_text(const vector2_t& position, const ImU32 color, std::string text,
                         bool outlined, const ImU32 outline_color) {
  initial.push_back(text_t{position, color, outline_color, outlined, text});
}

void drawing_t::add_circle(const vector2_t& center, float radius, const ImU32 color,
                           int segments, float thickness, bool filled) {
  initial.push_back(circle_t{center, radius, color, filled, segments, thickness});
}

void drawing_t::add_rect(const vector2_t& position, const vector2_t& size, const ImU32 color,
                         float rounding, float thickness, bool outlined,
                         const ImU32 outline_color, bool filled) {
  initial.push_back(
      rect_t{position, size, color, outline_color, outlined, filled, rounding, thickness});
}

void drawing_t::add_quad(const vector2_t& p0, const vector2_t& p1, const vector2_t& p2,
                         const vector2_t& p3, const ImU32 color, float thickness, bool filled) {
  initial.push_back(quad_t{p0, p1, p2, p3, color, filled, thickness});
}

void drawing_t::add_hull(const vector3_t& origin, const vector3_t& mins, const vector3_t& maxs,
                         const ImU32 color, float thickness, bool filled,
                         const ImU32 fill_color, float fill_alpha) {
  initial.push_back(
      hull_t{origin, mins, maxs, color, thickness, filled, fill_color, fill_alpha});
}

void drawing_t::clear_initial() { initial.clear(); }

void drawing_t::copy_to_intermediary() {
  std::scoped_lock to_intermediary{drawing_mutex};
  std::swap(initial, intermediary);
}

void drawing_t::copy_from_intermediary() {
  std::scoped_lock from_intermediary{drawing_mutex};
  render = intermediary;
}

void drawing_t::draw() {
  for (auto&& object : render) {
    if (auto* line = std::get_if<line_t>(&object)) {
      if ((line->color & IM_COL32_A_MASK) == 0) {
        break;
      }

      if (line->outlined) {
        draw_line_outlined(line->position_one, line->position_two, line->color,
                           line->outline_color, line->thickness);
      } else {
        draw_line(line->position_one, line->position_two, line->color, line->thickness);
      }
    } else if (auto* text = std::get_if<text_t>(&object)) {
      if (text->outlined) {
        draw_text_outlined(text->position, text->color, text->outline_color,
                           text->text.c_str());
      } else {
        draw_text(text->position, text->color, text->text.c_str());
      }
    } else if (auto* circle = std::get_if<circle_t>(&object)) {
      if (circle->filled) {
        draw_circle_filled(circle->center, circle->radius, circle->color, circle->segments);
      } else {
        draw_circle(circle->center, circle->radius, circle->color, circle->segments,
                    circle->thickness);
      }
    } else if (auto* rect = std::get_if<rect_t>(&object)) {
      if (rect->filled) {
        draw_rect_filled(rect->position, rect->size, rect->color, rect->rounding);
      } else {
        if (rect->outlined) {
          draw_rect_outlined(rect->position, rect->size, rect->color, rect->outline_color,
                             rect->rounding, rect->thickness);
        } else {
          draw_rect(rect->position, rect->size, rect->color, rect->rounding, rect->thickness);
        }
      }
    } else if (auto* quad = std::get_if<quad_t>(&object)) {
      if (quad->filled) {
        draw_quad_filled(quad->p0, quad->p1, quad->p2, quad->p3, quad->color);
      } else {
        draw_quad(quad->p0, quad->p1, quad->p2, quad->p3, quad->color, quad->thickness);
      }
    } else if (auto* hull = std::get_if<hull_t>(&object)) {
      if (hull->filled) {
        draw_hull_filled(hull->origin, hull->mins, hull->maxs, hull->color, hull->fill_color,
                         hull->thickness, hull->fill_alpha);
      } else {
        draw_hull(hull->origin, hull->mins, hull->maxs, hull->color, hull->thickness);
      }
    }
  }
}