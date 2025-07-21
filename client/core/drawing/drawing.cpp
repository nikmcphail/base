#include "drawing.h"

#include "client/client.h"

void drawing_t::draw_text(const ImVec2& position, const ImU32 color, const char* text) {
  client::g_render.draw_list->AddText(position, color, text);
}

void drawing_t::draw_text_outlined(const ImVec2& position, const ImU32 color,
                                   const ImU32 outline_color, const char* text) {
  draw_text(ImVec2{position.x, position.y - 1}, outline_color, text);
  draw_text(ImVec2{position.x, position.y + 1}, outline_color, text);
  draw_text(ImVec2{position.x - 1, position.y}, outline_color, text);
  draw_text(ImVec2{position.x + 1, position.y}, outline_color, text);

  draw_text(position, color, text);
}

void drawing_t::draw_circle(const ImVec2& center, float radius, const ImU32 color, int segments,
                            float thickness) {
  client::g_render.draw_list->AddCircle(center, radius, color, segments, thickness);
}

void drawing_t::draw_circle_filled(const ImVec2& center, float radius, const ImU32 color,
                                   int segments) {
  client::g_render.draw_list->AddCircleFilled(center, radius, color, segments);
}

void drawing_t::draw_line(const ImVec2& pos_one, const ImVec2& pos_two, const ImU32 color,
                          float thickness) {
  client::g_render.draw_list->AddLine(pos_one, pos_two, color, thickness);
}

void drawing_t::draw_rect(const ImVec2& p_min, const ImVec2& p_max, const ImU32 color,
                          float rounding, ImDrawFlags flags, float thickness) {
  client::g_render.draw_list->AddRect(p_min, p_max, color, rounding, flags, thickness);
}

void drawing_t::draw() {}