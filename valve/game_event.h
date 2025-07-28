#pragma once

class game_event_t {
public:
  virtual ~game_event_t() {};
  virtual const char* get_name() const = 0;
};