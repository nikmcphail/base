#pragma once

#include "library/math.h"

struct studio_bbox_t {
  int       bone;
  int       group;
  vector3_t bb_min;
  vector3_t bb_max;
  int       hitbox_name_index;
  int       unused[8];

  const char* hitbox_name() {
    if (hitbox_name_index == 0)
      return "";

    return ((const char*)this) + hitbox_name_index;
  }

  studio_bbox_t() = default;
};

struct studio_hitbox_set_t {
  int                   name_index;
  inline char* const    name(void) const { return ((char*)this) + name_index; }
  int                   num_hitboxes;
  int                   hitbox_index;
  inline studio_bbox_t* hitbox(int i) const {
    return (studio_bbox_t*)(((std::byte*)this) + hitbox_index) + i;
  }
};

class studio_header_t {
public:
  int       id;
  int       version;
  int       checksum;
  char      name[64];
  int       length;
  vector3_t eye_position;
  vector3_t illumination_position;
  vector3_t hull_min;
  vector3_t hull_max;
  vector3_t view_bbmin;
  vector3_t view_bbmax;
  int       flags;
  int       num_bones;
  int       bone_index;
  int       num_bone_controllers;
  int       bone_controller_index;
  int       num_hitbox_sets;
  int       hitbox_set_index;

  studio_hitbox_set_t* get_hitbox_set(int i) const {
    return (studio_hitbox_set_t*)(((std::byte*)this) + hitbox_set_index) + i;
  }

  inline studio_bbox_t* get_hitbox(int i, int set) const {
    studio_hitbox_set_t const* s = get_hitbox_set(set);
    if (!s)
      return NULL;

    return s->hitbox(i);
  }
};