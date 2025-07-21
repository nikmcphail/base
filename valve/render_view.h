#pragma once

#include "library/math.h"
#include "library/utils.h"

class view_setup_t;

class render_view_t {
public:
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
