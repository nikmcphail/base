#pragma once

#include "valve/vector3.h"
#include "valve/qangle.h"
#include "valve/matrix3x4.h"

#define MAX_LAYER_RECORDS  15
#define MAXSTUDIOPOSEPARAM 24

struct layer_record_t {
  int   sequence;
  float cycle;
  float weight;
  int   order;

  layer_record_t() {
    sequence = 0;
    cycle    = 0;
    weight   = 0;
    order    = 0;
  }

  layer_record_t(const layer_record_t& src) {
    sequence = src.sequence;
    cycle    = src.cycle;
    weight   = src.weight;
    order    = src.order;
  }
};

struct lag_record_t {
public:
  lag_record_t() {
    flags = 0;
    origin.initialize();
    angles.initialize();
    mins_pre_scaled.initialize();
    maxs_pre_scaled.initialize();
    simulation_time = -1;
    master_sequence = 0;
    master_cycle    = 0;
    head_pos.initialize();
    tick = 0;

    for (int i = 0; i < 128; i++) {
      bones[i] = matrix_3x4_t();
    }

    for (int i = 0; i < MAXSTUDIOPOSEPARAM; i++) {
      pose_parameters[i] = 0;
    }
  }

  lag_record_t(const lag_record_t& src) {
    flags           = src.flags;
    origin          = src.origin;
    angles          = src.angles;
    mins_pre_scaled = src.mins_pre_scaled;
    maxs_pre_scaled = src.maxs_pre_scaled;
    simulation_time = src.simulation_time;
    head_pos        = src.head_pos;
    tick            = src.tick;

    for (int i = 0; i < 128; i++) {
      bones[i] = src.bones[i];
    }

    for (int layer_index = 0; layer_index < MAX_LAYER_RECORDS; ++layer_index) {
      layer_records[layer_index] = src.layer_records[layer_index];
    }

    master_sequence = src.master_sequence;
    master_cycle    = src.master_cycle;

    for (int i = 0; i < MAXSTUDIOPOSEPARAM; i++) {
      pose_parameters[i] = src.pose_parameters[i];
    }
  }

  bool valid();

  int            flags;
  vector3_t      origin;
  qangle_t       angles;
  vector3_t      mins_pre_scaled;
  vector3_t      maxs_pre_scaled;
  float          simulation_time;
  layer_record_t layer_records[MAX_LAYER_RECORDS];
  int            master_sequence;
  float          master_cycle;
  float          pose_parameters[MAXSTUDIOPOSEPARAM];
  vector3_t      head_pos;
  matrix_3x4_t   bones[128];
  int            tick;
};