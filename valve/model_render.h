#pragma once

enum override_type_e {
  OVERRIDE_NORMAL = 0,
  OVERRIDE_BUILD_SHADOWS,
  OVERRIDE_DEPTH_WRITE,
  OVERRIDE_SSAO_DEPTH_WRITE,
};

class material_t;
class model_render_t {
private:
  virtual int vfunc00() = 0;

public:
  virtual void forced_material_override(material_t*     new_material,
                                        override_type_e override_type = OVERRIDE_NORMAL) = 0;
};