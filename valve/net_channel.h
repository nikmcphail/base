#pragma once

#include "library/utils.h"

#include "valve/net_channel_info.h"

#pragma pack(push, 1)
class net_channel_t {
private:
  char pad_0[0xc];

public:
  int out_sequence_number;        // 0xc
  int in_sequence_number;         // 0x10
  int out_sequence_number_nr_ack; // 0x14
  int out_reliable_state;         // 0x18
  int in_reliable_state;          // 0x1c
  int choked_packets;             // 0x20
private:
  char pad_24[0x94];

public:
  int socket;                    // 0xb8
  int stream_socket;             // 0xbc
  int max_reliable_payload_size; // 0xc0
private:
  char pad_c4[0x44];

public:
  float last_received; // 0x108
  float connect_time;  // 0x10c
private:
  char pad_110[0x8];

public:
  int rate; // 0x118
private:
  char pad_11c[0x2240];

public:
  int  packet_drop; // 0x235c
  char name[32];    // 0x2360
private:
  char pad_2380[0x3c];

public:
  float interpolation_amount;            // 0x23bc
  float remote_frame_time;               // 0x23c0
  float remote_frame_time_std_deviation; // 0x23c4
  int   max_routable_payload_size;       // 0x23c8
  int   split_packet_sequence;           // 0x23cc
}; // Size: 0x23d0
#pragma pack(pop)