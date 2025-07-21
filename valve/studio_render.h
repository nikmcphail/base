#pragma once

#include "library/utils.h"

class studio_header_t;
class client_renderable_t;

struct draw_model_info_t {
  studio_header_t*     studio_header;
  void*                hardware_data;
  int                  decals;
  int                  skin;
  int                  body;
  int                  hitbox_set;
  client_renderable_t* renderable;
};

enum override_type_e {
  OVERRIDE_NORMAL = 0,
  OVERRIDE_BUILD_SHADOWS,
  OVERRIDE_DEPTH_WRITE,
  OVERRIDE_SSAO_DEPTH_WRITE,
};

class material_t;

class studio_render_t {
public:
  void set_color_modulation(const float* blend) {
    utils::get_virtual_function<void(__thiscall*)(studio_render_t*, const float*)>(this, 27)(
        this, blend);
  }

  void set_alpha_modulation(float alpha) {
    utils::get_virtual_function<void(__thiscall*)(studio_render_t*, float)>(this, 28)(this,
                                                                                      alpha);
  }

  void forced_material_override(material_t*     new_material,
                                override_type_e override_type = OVERRIDE_NORMAL) {
    utils::get_virtual_function<void(__thiscall*)(
        studio_render_t*, material_t*, override_type_e)>(this, 33)(this, new_material,
                                                                   override_type);
  }
};