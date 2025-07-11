#pragma once

#include <cstddef>
#include <cstdint>

enum {
  TD_OFFSET_NORMAL = 0,
  TD_OFFSET_PACKED = 1,

  // Must be last
  TD_OFFSET_COUNT,
};

struct datamap_t;

typedef enum _fieldtypes {
  FIELD_VOID = 0,   // No type or value
  FIELD_FLOAT,      // Any floating point value
  FIELD_STRING,     // A string ID (return from ALLOC_STRING)
  FIELD_VECTOR,     // Any vector, QAngle, or AngularImpulse
  FIELD_QUATERNION, // A quaternion
  FIELD_INTEGER,    // Any integer or enum
  FIELD_BOOLEAN,    // boolean, implemented as an int, I may use this as a hint for compression
  FIELD_SHORT,      // 2 byte integer
  FIELD_CHARACTER,  // a byte
  FIELD_COLOR32,    // 8-bit per channel r,g,b,a (32bit color)
  FIELD_EMBEDDED,   // an embedded object with a datadesc, recursively traverse and embedded
                    // class/structure based on an additional typedescription
  FIELD_CUSTOM,     // special type that contains function pointers to it's read/write/parse
                    // functions

  FIELD_CLASSPTR, // CBaseEntity *
  FIELD_EHANDLE,  // Entity handle
  FIELD_EDICT,    // edict_t *

  FIELD_POSITION_VECTOR, // A world coordinate (these are fixed up across level transitions
                         // automagically)
  FIELD_TIME,            // a floating point time (these are fixed up automatically too!)
  FIELD_TICK,            // an integer tick count( fixed up similarly to time)
  FIELD_MODELNAME,       // Engine string that is a model name (needs precache)
  FIELD_SOUNDNAME,       // Engine string that is a sound name (needs precache)

  FIELD_INPUT,    // a list of inputed data fields (all derived from CMultiInputVar)
  FIELD_FUNCTION, // A class function pointer (Think, Use, etc)

  FIELD_VMATRIX, // a vmatrix (output coords are NOT worldspace)

  // NOTE: Use float arrays for local transformations that don't need to be fixed up.
  FIELD_VMATRIX_WORLDSPACE, // A VMatrix that maps some local space to world space (translation
                            // is fixed up on level transitions)
  FIELD_MATRIX3X4_WORLDSPACE, // matrix3x4_t that maps some local space to world space
                              // (translation is fixed up on level transitions)

  FIELD_INTERVAL, // a start and range floating point interval ( e.g., 3.2->3.6 == 3.2 and 0.4 )
  FIELD_MODELINDEX,    // a model index
  FIELD_MATERIALINDEX, // a material index (using the material precache string table)

  FIELD_VECTOR2D, // 2 floats

  FIELD_TYPECOUNT, // MUST BE LAST
} fieldtype_t;

typedef void (*inputfunc_t)();

struct typedescription_t {

public:
  typedescription_t(fieldtype_t type, const char* name, uint32_t offset, unsigned short size,
                    short flags, const char* ext_name, int bytes, float tolerance)
      : fieldType(type), fieldName(name), fieldSize(size), flags(flags), externalName(ext_name),
        pSaveRestoreOps(nullptr), inputFunc(nullptr), fieldSizeInBytes(bytes),
        override_field(nullptr), override_count(0), fieldTolerance(tolerance) {
    fieldOffset[0] = (offset);
  }
  fieldtype_t    fieldType;
  const char*    fieldName;
  uint32_t       fieldOffset[TD_OFFSET_COUNT]; // 0 == normal, 1 == packed offset
  unsigned short fieldSize;
  short          flags;
  // the name of the variable in the map/fgd data, or the name of the action
  const char*    externalName;
  // pointer to the function set for save/restoring of custom data types
  void*          pSaveRestoreOps;
  // for associating function with string names
  inputfunc_t    inputFunc;
  // For embedding additional datatables inside this one
  datamap_t*     td;

  // Stores the actual member variable size in bytes
  int fieldSizeInBytes;

  // FTYPEDESC_OVERRIDE point to first baseclass instance if chains_validated has occurred
  struct typedescription_t* override_field;

  // Used to track exclusion of baseclass fields
  int override_count;

  // Tolerance for field errors for float fields
  float fieldTolerance;
};

typedef struct color32_s {
  bool operator!=(const struct color32_s& other) const;

  char r, g, b, a;
} color32;

class variant_t {
public:
  union {
    bool        bVal;
    const char* iszVal;
    int         iVal;
    float       flVal;
    float       vecVal[3];
    color32     rgbaVal;
  };
  void* eVal; // this can't be in the union because it has a constructor.

  fieldtype_t fieldType;
};

#pragma pack(push, 1)
struct datamap_t {
  typedescription_t* dataDesc;      // 0x0
  size_t             dataNumFields; // 0x8
  char const*        dataClassName; // 0xc
  datamap_t*         baseMap;       // 0x14
  //
  bool               chains_validated;        // 0x1c
  bool               packed_offsets_computed; // 0x1d
  char               idk[2];                  // 0x1e
  int                packed_size;             // 0x20
}; // Size: 0x24
#pragma pack(pop)
