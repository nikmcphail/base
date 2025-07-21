#pragma once

#define MAX_PLAYER_NAME_LENGTH 32
#define SIGNED_GUID_LEN        32
#define MAX_CUSTOM_FILES       4

typedef struct player_info_s {
  // scoreboard information
  char          name[MAX_PLAYER_NAME_LENGTH];
  // local server user ID, unique while server is running
  int           userID;
  // global unique player identifer
  char          guid[SIGNED_GUID_LEN + 1];
  // friends identification number
  uint32_t      friendsID;
  // friends name
  char          friendsName[MAX_PLAYER_NAME_LENGTH];
  // true, if player is a bot controlled by game.dll
  bool          fakeplayer;
  // true if player is the HLTV proxy
  bool          ishltv;
  // custom files CRC for this player
  unsigned int  customFiles[MAX_CUSTOM_FILES];
  // this counter increases each time the server downloaded a new file
  unsigned char filesDownloaded;
} player_info_t;