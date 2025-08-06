#pragma once

#include "library/utils.h"

class net_channel_t {
public:
  bool processing_messages;
  bool cleared_during_processing;
  int  out_sequence_number;
  int  in_sequence_number;
  int  out_sequence_number_ack;
  int  out_reliable_state;
  int  in_reliable_state;
  int  choked_packets;
};