#pragma once

class IDirect3DDevice9;

class cvar_t;
class base_client_dll_t;
class surface_t;
class entity_list_t;
class engine_client_t;
class move_helper_t;
class prediction_t;
class game_movement_t;
class global_vars_base_t;
class input_t;
class input_system_t;
class client_player_t;
class model_info_t;

class interfaces_t {
public:
  IDirect3DDevice9*   d3d9_device{nullptr};
  cvar_t*             cvar{nullptr};
  base_client_dll_t*  base_client{nullptr};
  void*               client_mode{nullptr};
  surface_t*          surface{nullptr};
  entity_list_t*      entity_list{nullptr};
  engine_client_t*    engine_client{nullptr};
  move_helper_t*      move_helper{nullptr};
  prediction_t*       prediction{nullptr};
  game_movement_t*    game_movement{nullptr};
  global_vars_base_t* global_vars{nullptr};
  input_t*            input{nullptr};
  input_system_t*     input_system{nullptr};
  client_player_t**   prediction_player{nullptr};
  model_info_t*       model_info{nullptr};

  bool collect_interfaces();
};