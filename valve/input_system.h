#pragma once

#include "library/utils.h"

#define MAX_SPLITSCREEN_CLIENT_BITS 2
#define MAX_SPLITSCREEN_CLIENTS     (1 << MAX_SPLITSCREEN_CLIENT_BITS) // 4

#define JOYSTICK_BUTTON_INTERNAL(_joystick, _button)                                           \
  (JOYSTICK_FIRST_BUTTON + ((_joystick) * JOYSTICK_MAX_BUTTON_COUNT) + (_button))
#define JOYSTICK_POV_BUTTON_INTERNAL(_joystick, _button)                                       \
  (JOYSTICK_FIRST_POV_BUTTON + ((_joystick) * JOYSTICK_POV_BUTTON_COUNT) + (_button))
#define JOYSTICK_AXIS_BUTTON_INTERNAL(_joystick, _button)                                      \
  (JOYSTICK_FIRST_AXIS_BUTTON + ((_joystick) * JOYSTICK_AXIS_BUTTON_COUNT) + (_button))

#define JOYSTICK_BUTTON(_joystick, _button)                                                    \
  ((ButtonCode_t)JOYSTICK_BUTTON_INTERNAL(_joystick, _button))
#define JOYSTICK_POV_BUTTON(_joystick, _button)                                                \
  ((ButtonCode_t)JOYSTICK_POV_BUTTON_INTERNAL(_joystick, _button))
#define JOYSTICK_AXIS_BUTTON(_joystick, _button)                                               \
  ((ButtonCode_t)JOYSTICK_AXIS_BUTTON_INTERNAL(_joystick, _button))

enum {
  MAX_JOYSTICKS      = MAX_SPLITSCREEN_CLIENTS,
  MOUSE_BUTTON_COUNT = 5,
};

enum joystick_axis_e {
  JOY_AXIS_X = 0,
  JOY_AXIS_Y,
  JOY_AXIS_Z,
  JOY_AXIS_R,
  JOY_AXIS_U,
  JOY_AXIS_V,
  MAX_JOYSTICK_AXES,
};

enum {
  JOYSTICK_MAX_BUTTON_COUNT  = 32,
  JOYSTICK_POV_BUTTON_COUNT  = 4,
  JOYSTICK_AXIS_BUTTON_COUNT = MAX_JOYSTICK_AXES * 2,
};

enum button_code_e {
  BUTTON_CODE_INVALID = -1,
  BUTTON_CODE_NONE    = 0,

  KEY_FIRST = 0,

  KEY_NONE = KEY_FIRST,
  KEY_0,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_A,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,
  KEY_PAD_0,
  KEY_PAD_1,
  KEY_PAD_2,
  KEY_PAD_3,
  KEY_PAD_4,
  KEY_PAD_5,
  KEY_PAD_6,
  KEY_PAD_7,
  KEY_PAD_8,
  KEY_PAD_9,
  KEY_PAD_DIVIDE,
  KEY_PAD_MULTIPLY,
  KEY_PAD_MINUS,
  KEY_PAD_PLUS,
  KEY_PAD_ENTER,
  KEY_PAD_DECIMAL,
  KEY_LBRACKET,
  KEY_RBRACKET,
  KEY_SEMICOLON,
  KEY_APOSTROPHE,
  KEY_BACKQUOTE,
  KEY_COMMA,
  KEY_PERIOD,
  KEY_SLASH,
  KEY_BACKSLASH,
  KEY_MINUS,
  KEY_EQUAL,
  KEY_ENTER,
  KEY_SPACE,
  KEY_BACKSPACE,
  KEY_TAB,
  KEY_CAPSLOCK,
  KEY_NUMLOCK,
  KEY_ESCAPE,
  KEY_SCROLLLOCK,
  KEY_INSERT,
  KEY_DELETE,
  KEY_HOME,
  KEY_END,
  KEY_PAGEUP,
  KEY_PAGEDOWN,
  KEY_BREAK,
  KEY_LSHIFT,
  KEY_RSHIFT,
  KEY_LALT,
  KEY_RALT,
  KEY_LCONTROL,
  KEY_RCONTROL,
  KEY_LWIN,
  KEY_RWIN,
  KEY_APP,
  KEY_UP,
  KEY_LEFT,
  KEY_DOWN,
  KEY_RIGHT,
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,
  KEY_CAPSLOCKTOGGLE,
  KEY_NUMLOCKTOGGLE,
  KEY_SCROLLLOCKTOGGLE,

  KEY_LAST  = KEY_SCROLLLOCKTOGGLE,
  KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

  // Mouse
  MOUSE_FIRST = KEY_LAST + 1,

  MOUSE_LEFT = MOUSE_FIRST,
  MOUSE_RIGHT,
  MOUSE_MIDDLE,
  MOUSE_4,
  MOUSE_5,
  MOUSE_WHEEL_UP, // A fake button which is 'pressed' and 'released' when the wheel is moved up
  MOUSE_WHEEL_DOWN, // A fake button which is 'pressed' and 'released' when the wheel is moved
                    // down

  MOUSE_LAST  = MOUSE_WHEEL_DOWN,
  MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,

  // Joystick
  JOYSTICK_FIRST = MOUSE_LAST + 1,

  JOYSTICK_FIRST_BUTTON = JOYSTICK_FIRST,
  JOYSTICK_LAST_BUTTON =
      JOYSTICK_BUTTON_INTERNAL(MAX_JOYSTICKS - 1, JOYSTICK_MAX_BUTTON_COUNT - 1),
  JOYSTICK_FIRST_POV_BUTTON,
  JOYSTICK_LAST_POV_BUTTON =
      JOYSTICK_POV_BUTTON_INTERNAL(MAX_JOYSTICKS - 1, JOYSTICK_POV_BUTTON_COUNT - 1),
  JOYSTICK_FIRST_AXIS_BUTTON,
  JOYSTICK_LAST_AXIS_BUTTON =
      JOYSTICK_AXIS_BUTTON_INTERNAL(MAX_JOYSTICKS - 1, JOYSTICK_AXIS_BUTTON_COUNT - 1),

  JOYSTICK_LAST = JOYSTICK_LAST_AXIS_BUTTON,

  BUTTON_CODE_LAST,
  BUTTON_CODE_COUNT = BUTTON_CODE_LAST - KEY_FIRST + 1,

  // Helpers for XBox 360
  KEY_XBUTTON_UP = JOYSTICK_FIRST_POV_BUTTON, // POV buttons
  KEY_XBUTTON_RIGHT,
  KEY_XBUTTON_DOWN,
  KEY_XBUTTON_LEFT,

  KEY_XBUTTON_A = JOYSTICK_FIRST_BUTTON, // Buttons
  KEY_XBUTTON_B,
  KEY_XBUTTON_X,
  KEY_XBUTTON_Y,
  KEY_XBUTTON_LEFT_SHOULDER,
  KEY_XBUTTON_RIGHT_SHOULDER,
  KEY_XBUTTON_BACK,
  KEY_XBUTTON_START,
  KEY_XBUTTON_STICK1,
  KEY_XBUTTON_STICK2,
  KEY_XBUTTON_INACTIVE_START,

  KEY_XSTICK1_RIGHT = JOYSTICK_FIRST_AXIS_BUTTON, // XAXIS POSITIVE
  KEY_XSTICK1_LEFT,                               // XAXIS NEGATIVE
  KEY_XSTICK1_DOWN,                               // YAXIS POSITIVE
  KEY_XSTICK1_UP,                                 // YAXIS NEGATIVE
  KEY_XBUTTON_LTRIGGER,                           // ZAXIS POSITIVE
  KEY_XBUTTON_RTRIGGER,                           // ZAXIS NEGATIVE
  KEY_XSTICK2_RIGHT,                              // UAXIS POSITIVE
  KEY_XSTICK2_LEFT,                               // UAXIS NEGATIVE
  KEY_XSTICK2_DOWN,                               // VAXIS POSITIVE
  KEY_XSTICK2_UP,                                 // VAXIS NEGATIVE
};

enum MouseCodeState_t {
  BUTTON_RELEASED = 0,
  BUTTON_PRESSED,
  BUTTON_DOUBLECLICKED,
};

class input_system_t {
public:
  void enable_input(bool enable) {
    utils::get_virtual_function<void(__thiscall*)(input_system_t*, bool)>(this, 7)(this,
                                                                                   enable);
  }

  bool is_button_down(button_code_e code) {
    return utils::get_virtual_function<bool(__thiscall*)(input_system_t*, button_code_e)>(
        this, 11)(this, code);
  }
};