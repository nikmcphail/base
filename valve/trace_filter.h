#pragma once

class client_base_entity_t;

enum class trace_type_t {
  TRACE_EVERYTHING = 0,
  TRACE_WORLD_ONLY,
  TRACE_ENTITIES_ONLY,
  TRACE_EVERYTHING_FILTER_PROPS
};

class i_trace_filter_t {
  virtual bool         should_hit_entity(client_base_entity_t* entity, int contents_mask) = 0;
  virtual trace_type_t get_type() const                                                   = 0;
};

class trace_filter_t : public i_trace_filter_t {
  virtual bool should_hit_entity(client_base_entity_t* entity, int contents_mask) {
    return entity != skip_entity;
  }

  virtual trace_type_t get_type() const { return trace_type_t::TRACE_EVERYTHING; }

public:
  trace_filter_t(client_base_entity_t* entity) : skip_entity(entity) {}

  client_base_entity_t* skip_entity;
};