#pragma once

class animation_layer_t {
public:
  int   sequence;
  float prev_cycle;
  float weight;
  int   order;
  float playback_rate;
  float cycle;
  float layer_anim_time;
  float layer_fade_out_time;
  float blend_in;
  float blend_out;
  bool  client_blend;
};