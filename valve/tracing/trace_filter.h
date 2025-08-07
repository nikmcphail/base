#pragma once

class base_entity_t;

enum class trace_type_t {
  TRACE_EVERYTHING = 0,
  TRACE_WORLD_ONLY,
  TRACE_ENTITIES_ONLY,
  TRACE_EVERYTHING_FILTER_PROPS
};

class i_trace_filter_t {
  virtual bool         should_hit_entity(base_entity_t* ent, int contents_mask) = 0;
  virtual trace_type_t get_type() const                                         = 0;
};

class trace_filter_t : public i_trace_filter_t {
  virtual bool should_hit_entity(base_entity_t* ent, int contents_mask) {
    return ent != skip_entity;
  }

  virtual trace_type_t get_type() const { return trace_type_t::TRACE_EVERYTHING; }

public:
  trace_filter_t(base_entity_t* skip) : skip_entity(skip) {}

  base_entity_t* skip_entity;
};