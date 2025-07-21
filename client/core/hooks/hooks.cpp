#include "hooks.h"
#include <d3d9.h>

#include "client/client.h"
#include "valve/cusercmd.h"
#include "valve/view_setup.h"
#include "valve/surface.h"
#include "client/core/menu/menu.h"
#include "valve/prediction.h"
#include "valve/client_frame_stage.h"
#include "valve/model_render_info.h"

class hooked_d3d9_device_t : IDirect3DDevice9 {
public:
  HRESULT hooked_present(IDirect3DDevice9* device, RECT* source_rect, RECT* dest_rect,
                         HWND dest_window_override, RGNDATA* dirty_region) {
    client::on_present();
    return client::g_hooks.d3d9_present_hook.thiscall<HRESULT>(
        this, device, source_rect, dest_rect, dest_window_override, dirty_region);
  }

  HRESULT hooked_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_parameters) {
    HRESULT result;

    {
      std::scoped_lock _{client::g_render.imgui_mutex};
      client::g_render.detach();
      result =
          client::g_hooks.d3d9_reset_hook.thiscall<HRESULT>(this, device, present_parameters);
      client::get_window_handle();
      client::g_render.initialize();
    }

    return result;
  }
};

class hooked_client_mode {
public:
  bool hooked_create_move(float input_sample_time, usercmd_t* cmd) {
    return client::on_create_move(cmd);
  }

  void hooked_override_view(view_setup_t* setup) {
    client::g_hooks.override_view_hook.thiscall(this, setup);
  }
};

class hooked_surface {
public:
  HCURSOR hooked_lock_cursor() {
    if (menu::open)
      return client::g_interfaces.surface->unlock_cursor();

    return client::g_hooks.lock_cursor_hook.thiscall<HCURSOR>(this);
  }
};

class hooked_prediction {
public:
  void hooked_run_command(client_player_t* player, usercmd_t* cmd, move_helper_t* move_helper) {
    if (move_helper)
      client::g_interfaces.move_helper = move_helper;

    client::g_hooks.run_command_hook.thiscall(this, player, cmd, move_helper);
  }
};

class hooked_base_client {
public:
  void hooked_level_shutdown() {
    client::g_hooks.level_shutdown_hook.thiscall(this);
    client::on_level_shutdown();
  }

  void hooked_frame_stage_notify(client_frame_stage_e current_stage) {
    client::g_hooks.frame_stage_notify_hook.thiscall(this, current_stage);
  }
};

class hooked_model_render {
public:
  void hooked_draw_model_execute(const draw_model_state_t&  state,
                                 const model_render_info_t& info,
                                 matrix_3x4_t*              custom_bone_to_world) {
    client::g_hooks.draw_model_execute_hook.thiscall(this, state, info, custom_bone_to_world);
  }
};

class hooked_engine_vgui {
public:
  void hooked_paint(int32_t mode) {
    client::g_render.get_view_matrix();
    client::g_hooks.paint_hook.thiscall(this, mode);
  }
};

void hooked_cl_move(void* _this, float accumulated_extra_samples, bool final_tick) {
  client::on_cl_move();
  client::g_hooks.cl_move_hook.thiscall(_this, accumulated_extra_samples, final_tick);
}

bool hooks_t::initialize() {
  this->d3d9_device_hook = safetyhook::create_vmt(client::g_interfaces.d3d9_device);
  client::g_console.printf("\td3d9_device:", console_color_light_yellow);
  this->d3d9_present_hook =
      safetyhook::create_vm(this->d3d9_device_hook, 17, &hooked_d3d9_device_t::hooked_present);
  client::g_console.printf("\t\tpresent hooked", console_color_light_aqua);
  this->d3d9_reset_hook =
      safetyhook::create_vm(this->d3d9_device_hook, 16, &hooked_d3d9_device_t::hooked_reset);
  client::g_console.printf("\t\treset hooked", console_color_light_aqua);

  this->client_mode_hook = safetyhook::create_vmt(client::g_interfaces.client_mode);
  client::g_console.printf("\tclient_mode:", console_color_light_yellow);
  this->create_move_hook = safetyhook::create_vm(this->client_mode_hook, 21,
                                                 &hooked_client_mode::hooked_create_move);
  client::g_console.printf("\t\tcreatemove hooked", console_color_light_aqua);
  this->override_view_hook = safetyhook::create_vm(this->client_mode_hook, 16,
                                                   &hooked_client_mode::hooked_override_view);
  client::g_console.printf("\t\toverrideview hooked", console_color_light_aqua);

  this->surface_hook = safetyhook::create_vmt(client::g_interfaces.surface);
  client::g_console.printf("\tsurface:", console_color_light_yellow);
  this->lock_cursor_hook =
      safetyhook::create_vm(this->surface_hook, 62, &hooked_surface::hooked_lock_cursor);
  client::g_console.printf("\t\tlockcursor hooked", console_color_light_aqua);

  this->prediction_hook = safetyhook::create_vmt(client::g_interfaces.prediction);
  client::g_console.printf("\tprediction:", console_color_light_yellow);
  this->run_command_hook =
      safetyhook::create_vm(this->prediction_hook, 17, &hooked_prediction::hooked_run_command);
  client::g_console.printf("\t\truncommand hooked", console_color_light_aqua);

  this->base_client_hook = safetyhook::create_vmt(client::g_interfaces.base_client);
  client::g_console.printf("\tbase client:", console_color_light_yellow);
  this->level_shutdown_hook = safetyhook::create_vm(this->base_client_hook, 7,
                                                    &hooked_base_client::hooked_level_shutdown);
  client::g_console.printf("\t\tlevel shutdown hooked", console_color_light_aqua);
  this->frame_stage_notify_hook = safetyhook::create_vm(
      this->base_client_hook, 35, &hooked_base_client::hooked_frame_stage_notify);
  client::g_console.printf("\t\tframe stage notify hooked", console_color_light_aqua);

  this->model_render_hook = safetyhook::create_vmt(client::g_interfaces.model_render);
  client::g_console.printf("\tmodel render:", console_color_light_yellow);
  this->draw_model_execute_hook = safetyhook::create_vm(
      this->model_render_hook, 19, &hooked_model_render::hooked_draw_model_execute);
  client::g_console.printf("\t\tdraw model execute hooked", console_color_light_aqua);

  this->engine_vgui_hook = safetyhook::create_vmt(client::g_interfaces.engine_vgui);
  client::g_console.printf("\tengine vgui:", console_color_light_yellow);
  this->paint_hook =
      safetyhook::create_vm(this->engine_vgui_hook, 14, &hooked_engine_vgui::hooked_paint);
  client::g_console.printf("\t\tpaint hooked", console_color_light_aqua);

  client::g_console.printf("\tinline hooks:", console_color_light_yellow);
  this->cl_move_hook =
      safetyhook::create_inline((void*)client::g_addresses.engine.functions.cl_move,
                                reinterpret_cast<void*>(hooked_cl_move));
  client::g_console.printf("\t\tcl_move hooked", console_color_light_aqua);

  client::g_console.print("\thooks initialized", console_color_gray);
  return true;
}

void hooks_t::unload() {
  d3d9_device_hook  = {};
  client_mode_hook  = {};
  surface_hook      = {};
  prediction_hook   = {};
  base_client_hook  = {};
  model_render_hook = {};
}