#pragma once

#define BONE_CALCULATE_MASK       0x1F
#define BONE_PHYSICALLY_SIMULATED 0x01 // bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL   0x02 // procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL    0x04 // bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE  0x08 // bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER                                                             \
  0x10 // bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK           0x0007FF00
#define BONE_USED_BY_ANYTHING    0x0007FF00
#define BONE_USED_BY_HITBOX      0x00000100 // bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT  0x00000200 // bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK 0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0                                                               \
  0x00000400 // bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1 0x00000800
#define BONE_USED_BY_VERTEX_LOD2 0x00001000
#define BONE_USED_BY_VERTEX_LOD3 0x00002000
#define BONE_USED_BY_VERTEX_LOD4 0x00004000
#define BONE_USED_BY_VERTEX_LOD5 0x00008000
#define BONE_USED_BY_VERTEX_LOD6 0x00010000
#define BONE_USED_BY_VERTEX_LOD7 0x00020000
#define BONE_USED_BY_BONE_MERGE                                                                \
  0x00040000 // bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) (BONE_USED_BY_VERTEX_LOD0 << (lod))
#define BONE_USED_BY_ANYTHING_AT_LOD(lod)                                                      \
  ((BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK) | BONE_USED_BY_VERTEX_AT_LOD(lod))

#define MAX_NUM_LODS 8

#define BONE_TYPE_MASK 0x00F00000
#define BONE_FIXED_ALIGNMENT                                                                   \
  0x00100000 // bone can't spin 360 degrees, all interpolation is normalized around a fixed
             // orientation

#define BONE_HAS_SAVEFRAME_POS 0x00200000 // Vector48
#define BONE_HAS_SAVEFRAME_ROT 0x00400000 // Quaternion64

#define MAXSTUDIOBONES 128

enum bone_ids_e {
  BONE_PELVIS = 0,
  BONE_LEFT_KNEE,
  BONE_LEFT_ANKLE,
  BONE_LEFT_FOOT,
  BONE_LEFT_TOE,
  BONE_RIGHT_KNEE,
  BONE_RIGHT_ANKLE,
  BONE_RIGHT_FOOT,
  BONE_RIGHT_TOE,
  BONE_STOMACH,
  BONE_CHEST,
  BONE_NECK,
  BONE_HEAD,
  BONE_LEFT_ARM,
  BONE_LEFT_WRIST,
  BONE_LEFT_HAND,
  BONE_RIGHT_ARM,
  BONE_RIGHT_WRIST,
  BONE_RIGHT_HAND
};