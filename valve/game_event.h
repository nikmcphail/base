#pragma once

class game_event_t {
public:
  virtual ~game_event_t() {};
  virtual const char* get_name() const = 0;

  virtual bool is_reliable() const                   = 0;
  virtual bool is_local() const                      = 0;
  virtual bool is_empty(const char* key_name = NULL) = 0;

  virtual bool        get_bool(const char* key_name = NULL, bool default_value = false)  = 0;
  virtual int         get_int(const char* key_name = NULL, int default_value = 0)        = 0;
  virtual float       get_float(const char* key_name = NULL, float default_value = 0.0f) = 0;
  virtual const char* get_string(const char* key_name      = NULL,
                                 const char* default_value = "")                         = 0;

  virtual void set_bool(const char* key_name, bool value)          = 0;
  virtual void set_int(const char* key_name, int value)            = 0;
  virtual void set_float(const char* key_name, float value)        = 0;
  virtual void set_string(const char* key_name, const char* value) = 0;
};