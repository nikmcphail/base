#pragma once

#include "library/utils.h"

enum material_var_flags_e {
  MATERIAL_VAR_DEBUG                = (1 << 0),
  MATERIAL_VAR_NO_DEBUG_OVERRIDE    = (1 << 1),
  MATERIAL_VAR_NO_DRAW              = (1 << 2),
  MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

  MATERIAL_VAR_VERTEXCOLOR              = (1 << 4),
  MATERIAL_VAR_VERTEXALPHA              = (1 << 5),
  MATERIAL_VAR_SELFILLUM                = (1 << 6),
  MATERIAL_VAR_ADDITIVE                 = (1 << 7),
  MATERIAL_VAR_ALPHATEST                = (1 << 8),
  MATERIAL_VAR_MULTIPASS                = (1 << 9),
  MATERIAL_VAR_ZNEARER                  = (1 << 10),
  MATERIAL_VAR_MODEL                    = (1 << 11),
  MATERIAL_VAR_FLAT                     = (1 << 12),
  MATERIAL_VAR_NOCULL                   = (1 << 13),
  MATERIAL_VAR_NOFOG                    = (1 << 14),
  MATERIAL_VAR_IGNOREZ                  = (1 << 15),
  MATERIAL_VAR_DECAL                    = (1 << 16),
  MATERIAL_VAR_ENVMAPSPHERE             = (1 << 17),
  MATERIAL_VAR_NOALPHAMOD               = (1 << 18),
  MATERIAL_VAR_ENVMAPCAMERASPACE        = (1 << 19),
  MATERIAL_VAR_BASEALPHAENVMAPMASK      = (1 << 20),
  MATERIAL_VAR_TRANSLUCENT              = (1 << 21),
  MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
  MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING  = (1 << 23),
  MATERIAL_VAR_OPAQUETEXTURE            = (1 << 24),
  MATERIAL_VAR_ENVMAPMODE               = (1 << 25),
  MATERIAL_VAR_SUPPRESS_DECALS          = (1 << 26),
  MATERIAL_VAR_HALFLAMBERT              = (1 << 27),
  MATERIAL_VAR_WIREFRAME                = (1 << 28),
  MATERIAL_VAR_ALLOWALPHATOCOVERAGE     = (1 << 29),
  MATERIAL_VAR_IGNORE_ALPHA_MODULATION  = (1 << 30),

  // NOTE: Only add flags here that either should be read from
  // .vmts or can be set directly from client code. Other, internal
  // flags should to into the flag enum in imaterialinternal.h
};

class material_t {
public:
  const char* get_name() {
    return utils::get_virtual_function<const char*(__thiscall*)(material_t*)>(this, 0)(this);
  }

  const char* get_texture_group_name() {
    return utils::get_virtual_function<const char*(__thiscall*)(material_t*)>(this, 1)(this);
  }

  void set_material_var_flag(material_var_flags_e flag, bool on) {
    utils::get_virtual_function<void(__thiscall*)(material_t*, material_var_flags_e, bool)>(
        this, 29)(this, flag, on);
  }
};