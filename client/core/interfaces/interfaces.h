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
class engine_trace_t;
struct client_state_t;
class material_system_t;
class model_render_t;
class render_view_t;
class panel_t;

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
  engine_trace_t*     engine_trace{nullptr};
  client_state_t*     client_state{nullptr};
  material_system_t*  material_system{nullptr};
  model_render_t*     model_render{nullptr};
  render_view_t*      render_view{nullptr};
  void*               engine_vgui{nullptr};
  panel_t*            panel{nullptr};

  bool collect_interfaces();
};