#pragma once

#include "library/utils.h"

#include "valve/ray_t.h"
#include "valve/trace_filter.h"
#include "valve/trace.h"

class engine_trace_t {
private:
  virtual void unused_01() = 0;
  virtual void unused_02() = 0;
  virtual void unused_03() = 0;
  virtual void unused_04() = 0;

public:
  virtual void trace_ray(const ray_t& ray, unsigned int mask, trace_filter_t* filter,
                         trace_t* trace);
};