#pragma once

#include <cstdint>
#include "valve/cusercmd.h"
#include "valve/vector3.h"
#include "valve/qangle.h"

struct camera_third_data_t {
  float     m_flPitch;
  float     m_flYaw;
  float     m_flDist;
  float     m_flLag;
  vector3_t m_vecHullMin;
  vector3_t m_vecHullMax;
};

enum game_action_set_e {
  GAME_ACTION_SET_NONE         = -1,
  GAME_ACTION_SET_MENUCONTROLS = 0,
  GAME_ACTION_SET_FPSCONTROLS,
  GAME_ACTION_SET_IN_GAME_HUD,
  GAME_ACTION_SET_SPECTATOR,
};

enum game_action_set_flags_e {
  GAME_ACTION_SET_FLAGS_NONE     = 0,
  GAME_ACTION_SET_FLAGS_TAUNTING = (1 << 0),
};

struct kbutton_t {
  // key nums holding it down
  int down[2];
  // low bit is down state
  int state;
};

class keyboard_key_t {
public:
  // Name for key
  char            name[32];
  // Pointer to the underlying structure
  kbutton_t*      pkey;
  // Next key in key list.
  keyboard_key_t* next;
};

class verified_user_cmd_t {
public:
  usercmd_t cmd;
  uint64_t  crc;
};

class input_t {

private:
  typedef struct {
    unsigned int AxisFlags;
    unsigned int AxisMap;
    unsigned int ControlMap;
  } joy_axis_t;

public:
  bool                    mouse_initialized{};
  bool                    mouse_active{};
  bool                    joystick_advanced_init{};
  bool                    had_joysticks{};
  float                   accumulated_mouse_x_movement{};
  float                   accumulated_mouse_y_movement{};
  float                   previous_mouse_x_position{};
  float                   previous_mouse_y_position{};
  float                   remaining_joystick_sample_time{};
  float                   keyboard_sample_time{};
  int                     capture_workaround_last_mouse_x{};
  int                     capture_workaround_last_mouse_y{};
  bool                    restore_spi{};
  int                     orig_mouse_params[3]{};
  int                     new_mouse_params[3]{};
  int                     check_mouse_param[3]{};
  bool                    mouse_params_valid{};
  joy_axis_t              axes[6]{};
  keyboard_key_t*         keys{};
  bool                    camera_intercepting_mouse{};
  bool                    camera_in_third_person{};
  bool                    camera_moving_with_mouse{};
  bool                    camera_distance_move{};
  int                     camera_old_x{};
  int                     camera_old_y{};
  bool                    camera_is_orthographic{};
  qangle_t                previous_viewangles{};
  float                   last_forward_move{};
  float                   previous_joystick_forward{};
  float                   previous_joystick_side{};
  float                   previous_joystick_pitch{};
  float                   previous_joystick_yaw{};
  int                     controller_type[9]{};
  game_action_set_e       preferred_game_action_set{};
  game_action_set_flags_e game_action_set_flags{};
  bool                    steam_controller_game_actions_initialized{};
  bool                    steam_controller_seen_input = false;
  usercmd_t*              commands{};
  verified_user_cmd_t*    verified_commands{};
  camera_third_data_t*    camera_third_data{};
};