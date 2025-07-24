#pragma once

#include "library/utils.h"

class view_setup_t;
class view_matrix_t;

class render_view_t {
public:
  void set_blend(float blend) {
    utils::get_virtual_function<void(__thiscall*)(render_view_t*, float)>(this, 4)(this, blend);
  }

  float get_blend() {
    return utils::get_virtual_function<float(__thiscall*)(render_view_t*)>(this, 5)(this);
  }

  void set_color_modulation(float const* blend) {
    utils::get_virtual_function<void(__thiscall*)(render_view_t*, float const*)>(this, 6)(
        this, blend);
  }

  void get_color_modulation(float* blend) {
    utils::get_virtual_function<void(__thiscall*)(render_view_t*, float*)>(this, 7)(this,
                                                                                    blend);
  }

  void get_matrices_for_view(view_setup_t& view, view_matrix_t* world_to_view,
                             view_matrix_t* view_to_projection,
                             view_matrix_t* world_to_projection,
                             view_matrix_t* world_to_pixels) {
    return utils::get_virtual_function<void(__thiscall*)(
        void*, view_setup_t&, view_matrix_t*, view_matrix_t*, view_matrix_t*, view_matrix_t*)>(
        this, 50)(this, view, world_to_view, view_to_projection, world_to_projection,
                  world_to_pixels);
  }
};
