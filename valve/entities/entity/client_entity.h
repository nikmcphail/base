#pragma once

#include "client_unknown.h"

#include "collideable.h"
#include "client_networkable.h"

class qangle_t;

class client_entity_t : public client_unknown_t {
public:
  const vector3_t& obb_mins_pre_scaled() { return get_collidable()->obb_mins_pre_scaled(); }
  const vector3_t& obb_maxs_pre_scaled() { return get_collidable()->obb_maxs_pre_scaled(); }

  client_class_t* get_client_class() { return get_client_networkable()->get_client_class(); }
  bool            is_dormant() { return get_client_networkable()->is_dormant(); }
  int             ent_index() { return get_client_networkable()->ent_index(); }

  const vector3_t& get_abs_origin() {
    return utils::get_virtual_function<const vector3_t&(__fastcall*)(void*)>(this, 9)(this);
  }

  const qangle_t& get_abs_angles() {
    return utils::get_virtual_function<const qangle_t&(__fastcall*)(void*)>(this, 10)(this);
  }
};