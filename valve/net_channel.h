#pragma once

#include "valve/net_channel_info.h"

#pragma pack(push, 1)
class net_channel_t : public net_channel_info_t {
private:
  char pad_0[0x04];

public:
  int out_sequence_number;
  int in_sequence_number;
  int out_sequence_number_nr_ack;
  int out_reliable_state;
  int in_reliable_state;
  int choked_packets;

private:
  char pad_24[0x94];

public:
  int socket;
  int stream_socket;
  int max_reliable_payload_size;

private:
  char pad_c4[0x44];

public:
  float last_received;
  float connect_time;

private:
  char pad_110[0x8];

public:
  int rate;

private:
  char pad_11c[0x2240];

public:
  int  packet_drop;
  char name[32];

private:
  char pad_2380[0x3c];

public:
  float interpolation_amount;
  float remote_frame_time;
  float remote_frame_time_std_deviation;
  int   max_routable_payload_size;
  int   split_packet_sequence;
};
#pragma pack(pop)
