#pragma once

#include "valve/vector3.h"

class client_base_entity_t;

class move_helper_t {
public:
  virtual ~move_helper_t(void) = 0;

  // touch lists
  virtual void reset_touch_list(void)                                          = 0;
  virtual bool add_to_touched(const void* tr, const vector3_t& impactvelocity) = 0;
  virtual void process_impacts(void)                                           = 0;

  // Numbered line printf
  virtual void con_printf(int idx, char const* fmt, ...) = 0;

  virtual bool player_falling_damage(void)       = 0;
  virtual void player_set_animation(void* eAnim) = 0;

  // These have separate server vs client impementations
  virtual void  start_sound(const vector3_t& origin, int channel, char const* sample,
                            float volume, int soundlevel, int fFlags, int pitch) = 0;
  virtual void  start_sound(const vector3_t& origin, const char* soundname)      = 0;
  virtual void  playback_event_full(int flags, int clientindex, unsigned short eventindex,
                                    float delay, vector3_t& origin, vector3_t& angles,
                                    float fparam1, float fparam2, int iparam1, int iparam2,
                                    int bparam1, int bparam2)                    = 0;
  virtual void* get_surface_props(void)                                          = 0;

  virtual bool is_world_entity(const void* handle) = 0;

  virtual void set_host(void* host) = 0;
};