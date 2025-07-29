#include "drawing.h"

#include "library/math.h"
#include "client/client.h"
#include <fmt/core.h>

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

// public functions
void drawing_t::add_line(const vector2_t& position_one, const vector2_t& position_two,
                         const ImU32 color, float thickness) {
  initial.push_back(line_t{position_one, position_two, color, thickness});
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
                         const ImU32 outline_color) {
  initial.push_back(
      rect_t{position, size, color, outline_color, outlined, rounding, thickness});
}

void drawing_t::add_quad(const vector2_t& p0, const vector2_t& p1, const vector2_t& p2,
                         const vector2_t& p3, const ImU32 color, float thickness, bool filled) {
  initial.push_back(quad_t{p0, p1, p2, p3, color, filled, thickness});
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

      draw_line(line->position_one, line->position_two, line->color, line->thickness);
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
      if (rect->outlined) {
        draw_rect_outlined(rect->position, rect->size, rect->color, rect->outline_color,
                           rect->rounding, rect->thickness);
      } else {
        draw_rect(rect->position, rect->size, rect->color, rect->rounding, rect->thickness);
      }
    } else if (auto* quad = std::get_if<quad_t>(&object)) {
      if (quad->filled) {
        draw_quad_filled(quad->p0, quad->p1, quad->p2, quad->p3, quad->color);
      } else {
        draw_quad(quad->p0, quad->p1, quad->p2, quad->p3, quad->color, quad->thickness);
      }
    }
  }
}