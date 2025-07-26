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

void drawing_t::draw_text_stack(const vector2_t& position, const im_gui_text_stack_t stack) {
  vector2_t line_pos   = position;
  float     font_scale = ImGui::GetFont()->LegacySize;

  for (const auto& line : stack.text) {
    draw_text_outlined(line_pos, line.color, line.outline_color, line.text);
    line_pos.y += font_scale;
  }
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

void drawing_t::draw_2d_line(const vector2_t& pos_one, const vector2_t& pos_two,
                             const ImU32 color, float thickness) {
  client::g_render.draw_list->AddLine({pos_one.x, pos_one.y}, {pos_two.x, pos_two.y}, color,
                                      thickness);
}

void drawing_t::draw_rect(const vector2_t& position, const vector2_t& size, const ImU32 color,
                          float rounding, ImDrawFlags flags, float thickness) {
  auto max = position + size;
  client::g_render.draw_list->AddRect({position.x, position.y}, {max.x, max.y}, color, rounding,
                                      flags, thickness);
}

void drawing_t::draw() {}