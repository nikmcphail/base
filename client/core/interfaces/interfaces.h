#pragma once

class IDirect3DDevice9;

class interfaces_t {
public:
  IDirect3DDevice9* d3d9_device{nullptr};

  bool collect_interfaces();
};