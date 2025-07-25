#pragma once

#include "valve/vector3.h"

#pragma pack(push, 1)
class move_data_t {
public:
    uintptr_t vtable_pad; // 0x0
    bool first_run_of_functions; // 0x8
    bool game_code_moved_player; // 0x9
    char pad[2]; // 0xa
    int entity_handle; // 0xc
    int impulse_command; // 0x10
    vector3_t view_angles; // 0x14
    vector3_t abs_view_angles; // 0x20
    int buttons; // 0x2c
    int old_buttons; // 0x30
    float forward_move; // 0x34
    float old_forward_move; // 0x38
    float side_move; // 0x3c
    float up_move; // 0x40
    float max_speed; // 0x44
    float client_max_speed; // 0x48
    vector3_t velocity; // 0x4c
    vector3_t angles; // 0x58
    vector3_t old_angles; // 0x64
    float step_height; // 0x70
    vector3_t wish_vel; // 0x74
    vector3_t jump_vel; // 0x80
    vector3_t constraint_center; // 0x8c
    float constraint_radius; // 0x98
    float constraint_width; // 0x9c
    float constraint_speed_factor; // 0xa0
    vector3_t abs_origin; // 0xa4
}; // Size: 0xb0
#pragma pack(pop)