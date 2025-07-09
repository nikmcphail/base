#pragma once

class IDirect3DDevice9;

class cvar_t;

class interfaces_t {
public:
  IDirect3DDevice9* d3d9_device{nullptr};
  cvar_t*           cvar{nullptr};

  bool collect_interfaces();
};