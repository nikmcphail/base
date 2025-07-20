#pragma once

#include <cstdint>

#include "library/math.h"
#include "library/utils.h"
#include "client/client.h"

#include "valve/engine_client.h"
#include "valve/entity_list.h"
#include "client/core/global_addresses/global_addresses.h"

class client_player_t;
class client_local_player_t;
class model_t;

#define FL_ONGROUND (1 << 0) // At rest / on the ground
#define FL_DUCKING  (1 << 1) // Player flag -- Player is fully crouched
#define FL_ANIMDUCKING                                                                         \
  (1 << 2) // Player flag -- Player is in the process of crouching or uncrouching but could be
           // in transition
// examples:                                   Fully ducked:  FL_DUCKING &  FL_ANIMDUCKING
//           Previously fully ducked, unducking in progress:  FL_DUCKING & !FL_ANIMDUCKING
//                                           Fully unducked: !FL_DUCKING & !FL_ANIMDUCKING
//           Previously fully unducked, ducking in progress: !FL_DUCKING &  FL_ANIMDUCKING
#define FL_WATERJUMP (1 << 3) // player jumping out of water
#define FL_ONTRAIN                                                                             \
  (1 << 4) // Player is _controlling_ a train, so movement commands should be ignored on client
           // during prediction.
#define FL_INRAIN (1 << 5) // Indicates the entity is standing in rain
#define FL_FROZEN (1 << 6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS                                                                          \
  (1 << 7) // Player can't move, but keeps key inputs for controlling another entity
#define FL_CLIENT (1 << 8) // Is a player
#define FL_FAKECLIENT                                                                          \
  (1 << 9) // Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be
// applied to players, though
#define FL_INWATER (1 << 10) // In water

// NOTE if you move things up, make sure to change this value
#define PLAYER_FLAG_BITS 32

#define FL_FLY (1 << 11) // Changes the SV_Movestep() behavior to not need to be on ground
#define FL_SWIM                                                                                \
  (1 << 12) // Changes the SV_Movestep() behavior to not need to be on ground (but stay in
            // water)
#define FL_CONVEYOR      (1 << 13)
#define FL_NPC           (1 << 14)
#define FL_GODMODE       (1 << 15)
#define FL_NOTARGET      (1 << 16)
#define FL_AIMTARGET     (1 << 17) // set if the crosshair needs to aim onto the entity
#define FL_PARTIALGROUND (1 << 18) // not all corners are valid
#define FL_STATICPROP    (1 << 19) // Eetsa static prop!
#define FL_GRAPHED                                                                             \
  (1 << 20) // worldgraph has this ent listed as something that blocks a connection
#define FL_GRENADE      (1 << 21)
#define FL_STEPMOVEMENT (1 << 22) // Changes the SV_Movestep() behavior to not do any processing
#define FL_DONTTOUCH                                                                           \
  (1 << 23) // Doesn't generate touch functions, generates Untouch() for anything it was
            // touching when this flag was set
#define FL_BASEVELOCITY                                                                        \
  (1 << 24) // Base velocity has been applied this frame (used to convert base velocity into
            // momentum)
#define FL_WORLDBRUSH                                                                          \
  (1 << 25) // Not moveable/removeable brush entity (really part of the world, but represented
            // as an entity for transparency or something)
#define FL_OBJECT                                                                              \
  (1 << 26) // Terrible name. This is an object that NPCs should see. Missiles, for example.
#define FL_KILLME                (1 << 27) // This entity is marked for death -- will be freed by game DLL
#define FL_ONFIRE                (1 << 28) // You know...
#define FL_DISSOLVING            (1 << 29) // We're dissolving!
#define FL_TRANSRAGDOLL          (1 << 30) // In the process of turning into a client side ragdoll.
#define FL_UNBLOCKABLE_BY_PLAYER (1 << 31) // pusher that can't be blocked by the player

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

class client_base_entity_t {
  friend client_player_t;

  template <typename T> inline T get_ptr_at_offset(uint32_t offset) noexcept {
    return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(this) + offset);
  }

  template <typename T> inline T& get_value_at_offset(uint32_t offset) noexcept {
    return *get_ptr_at_offset<T*>(offset);
  }

#define netvar_value_func(type, name, offset)                                                  \
  type& name() noexcept { return get_value_at_offset<type>(offset); }
#define get_ptr_value_func(type, name, offset)                                                 \
  type name() noexcept { return get_ptr_at_offset<type>(offset); }

public:
  bool is_player() {
    return utils::get_virtual_function<bool(__thiscall*)(client_base_entity_t*)>(this,
                                                                                 132)(this);
  }

  static client_local_player_t* get_local_player() {
    return (client_local_player_t*)client::g_interfaces.entity_list->get_client_entity(
        client::g_interfaces.engine_client->get_local_player_index());
  }

  void set_prediction_random_seed(const usercmd_t* cmd) {
    static auto func = (__int64(__fastcall*)(
        const usercmd_t*))client::g_addresses.client.functions.set_prediction_random_seed;
    func(cmd);
  }

  void* get_client_renderable() {
    return utils::get_virtual_function<void*(__thiscall*)(client_base_entity_t*)>(this,
                                                                                  5)(this);
  }

  model_t* get_model() {
    void* client_renderable = this->get_client_renderable();
    if (!client_renderable)
      return nullptr;

    return utils::get_virtual_function<model_t*(__thiscall*)(void*)>(client_renderable,
                                                                     9)(client_renderable);
  }

  bool setup_bones(matrix_3x4_t* bone_to_world_out, int max_bones, int bone_mask,
                   float current_time) {
    void* client_renderable = this->get_client_renderable();
    if (!client_renderable)
      return false;

    return utils::get_virtual_function<bool(__thiscall*)(void*, matrix_3x4_t*, int, int,
                                                         float)>(client_renderable, 16)(
        client_renderable, bone_to_world_out, max_bones, bone_mask, current_time);
  }

  netvar_value_func(vector3_t, origin, client::g_offsets.client.base_entity.origin);
  netvar_value_func(int, team_number, client::g_offsets.client.base_entity.team_number);
  netvar_value_func(vector3_t, vec_mins, client::g_offsets.client.base_entity.vec_mins);
  netvar_value_func(vector3_t, vec_maxs, client::g_offsets.client.base_entity.vec_maxs);
  netvar_value_func(int, hitbox_set, client::g_offsets.client.base_player.hitbox_set);
  netvar_value_func(unsigned char, move_type, client::g_offsets.client.base_entity.move_type);
};