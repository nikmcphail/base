#pragma once

class IDirect3DDevice9;

class cvar_t;
class base_client_dll_t;
class surface_t;
class entity_list_t;

class interfaces_t {
public:
  IDirect3DDevice9*  d3d9_device{nullptr};
  cvar_t*            cvar{nullptr};
  base_client_dll_t* base_client{nullptr};
  void*              client_mode{nullptr};
  surface_t*         surface{nullptr};
  entity_list_t*     entity_list{nullptr};

  bool collect_interfaces();
};