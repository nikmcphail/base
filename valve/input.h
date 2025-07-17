#pragma once

#include "valve/cusercmd.h"

class verified_user_cmd_t {
public:
  usercmd_t cmd;
  uint64_t  crc;
};

class input_t {
private:
  char pad[0x108];

public:
  usercmd_t*           commands{};
  verified_user_cmd_t* verified_commands{};
};