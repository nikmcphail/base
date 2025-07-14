#pragma once

class global_vars_base_t {
public:
  float real_time;
  float frame_count;
  float abs_frame_count;
  float cur_time;
  float frame_time;
  int   max_clients;
  int   tick_count;
  float interval_per_tick;
  float interpolation_amount;
  int   sim_ticks_this_frame;
  int   network_protocol;
  void* save_data;
  bool  b_client;
  int   timestamp_networking_base;
  int   timestamp_randomize_window;
};