#pragma once

struct utl_string_t {
  char* pstring;
};

struct clock_drift_mng_t {
  float clock_offsets[16];
  int   cur_clock_offset;
  int   server_tick;
  int   client_tick;
};

class net_channel_t;

struct __declspec(align(8)) client_state_t {
  char              gap0[24];
  int               socket;
  net_channel_t*    net_channel;
  unsigned int      challenge_nr;
  double            connect_time;
  int               retry_number;
  char              retry_address[260];
  utl_string_t      retry_source_tag;
  int               retry_challenge;
  int               signon_state;
  double            next_cmdtime;
  int               server_count;
  unsigned __int64  game_server_steamid;
  int               current_sequence;
  clock_drift_mng_t clock_driftmgr;
  int               delta_tick;
  bool              paused;
  float             paused_expire_time;
  int               view_entity;
  int               player_slot;
  char              levelfilename[128];
  char              gap24C[132];
  char              level_base_name[128];
  char              gap350[116];
  int               max_clients;
  char              gap3C8[34856];
  void*             table_container;
  bool              restrict_server_commands;
  bool              restrict_client_commands;
  char              gap8BFC[106];
  bool              in_simulation;
  int               old_tick_count;
  float             tick_remainder;
  float             frame_time;
  int               last_outgoing_command;
  int               choked_commands;
  int               last_command_ack;
  int               command_ack;
  int               sound_sequence;
  bool              is_hltv;
  bool              is_replay;
  char              gap8C8A[278];
  int               demo_num;
  utl_string_t      demos[32];
  char              gap8EE8[344184];
  bool              markedcrcsunverified;
};