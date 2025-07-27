#include "drawing.h"

#include "library/math.h"
#include "client/client.h"
#include <fmt/core.h>

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

void drawing_t::add_line(const vector2_t& position_one, const vector2_t& position_two,
                         const ImU32 color, float thickness) {
  initial.push_back(line_t{position_one, position_two, color, thickness});
}

void drawing_t::add_text(const vector2_t& position, const ImU32 color, const char* text,
                         bool outlined, const ImU32 outline_color) {
  initial.push_back(text_t{position, color, outline_color, outlined, text});
}

void drawing_t::add_circle(const vector2_t& center, float radius, const ImU32 color,
                           int segments, float thickness, bool filled) {
  initial.push_back(circle_t{center, radius, color, filled, segments, thickness});
}

void drawing_t::add_rect(const vector2_t& position, const vector2_t& size, const ImU32 color,
                         float rounding, float thickness) {
  initial.push_back(rect_t{position, size, color, rounding, thickness});
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
  std::scoped_lock draw_lock{drawing_mutex};
  for (auto&& object : render) {
    if (auto* line = std::get_if<line_t>(&object)) {
      if ((line->color & IM_COL32_A_MASK) == 0) {
        break;
      }

      draw_line(line->position_one, line->position_two, IM_COL32_WHITE);
    } else if (auto* text = std::get_if<text_t>(&object)) {
      if (text->outlined) {
        draw_text_outlined(text->position, text->color, text->outline_color, text->text);
      } else {
        draw_text(text->position, text->color, text->text);
      }
    } else if (auto* circle = std::get_if<circle_t>(&object)) {
      if (circle->filled) {
        draw_circle_filled(circle->center, circle->radius, circle->color, circle->segments);
      } else {
        draw_circle(circle->center, circle->radius, circle->color, circle->segments,
                    circle->thickness);
      }
    } else if (auto* rect = std::get_if<rect_t>(&object)) {
      draw_rect(rect->position, rect->size, rect->color, rect->rounding, rect->thickness);
    }
  }
}