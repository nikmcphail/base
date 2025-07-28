#pragma once

#include "valve/vector3.h"
#include "valve/qangle.h"

class matrix_3x4_t;
class model_t;
class studio_header_t;

struct draw_model_state_t {
  studio_header_t*    studio_header;
  void*               hw_data;
  void*               renderable;
  const matrix_3x4_t* model_to_world;
  int                 decals;
  int                 draw_flags;
  int                 lod;
};

struct model_render_info_t {
  vector3_t           origin;
  qangle_t            angles;
  void*               renderable;
  const model_t*      model;
  const matrix_3x4_t* model_to_world;
  const matrix_3x4_t* lighting_offset;
  const vector3_t*    lighting_origin;
  int                 flags;
  int                 entity_index;
  int                 skin;
  int                 body;
  int                 hitboxset;
  unsigned short      instance;
};