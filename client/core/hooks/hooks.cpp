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

#include <fmt/core.h>

// =====================================================================================================
//                                          hooking functions

void hook_vmt(SafetyHookVmt& vmt, void* original, const std::string& name) {
  vmt                   = safetyhook::create_vmt(original);
  std::string formatted = fmt::format("\t{}:", name);
  client::g_console.print(formatted.c_str(), console_color_light_yellow);
}

template <typename T>
void hook_vm(SafetyHookVmt& vmt, SafetyHookVm& vm, T detour, int index,
             const std::string& name) {
  vm = safetyhook::create_vm(vmt, index, detour);

  std::string formatted = fmt::format("\t\thooked {}", name);
  client::g_console.print(formatted.c_str(), console_color_light_aqua);
}

template <typename T>
void hook_inline(SafetyHookInline& inline_hook, T detour, void* original,
                 const std::string& name) {
  inline_hook           = safetyhook::create_inline(original, detour);
  std::string formatted = fmt::format("\t\thooked {}", name);
  client::g_console.print(formatted.c_str(), console_color_light_aqua);
}

// =====================================================================================================
//                                          detour functions (vmt)
class hooked_d3d9_device {
public:
  // IDirect3DDevice9::Present( const RECT *pSourceRect, const RECT *pDestRect, HWND
  // hDestWindowOverride, const RGNDATA *pDirtyRegion)
  HRESULT hooked_present(IDirect3DDevice9* device, RECT* source_rect, RECT* dest_rect,
                         HWND dest_window_override, RGNDATA* dirty_region) {
    client::on_present();
    return client::g_hooks.d3d9_present_hook.thiscall<HRESULT>(
        this, device, source_rect, dest_rect, dest_window_override, dirty_region);
  }

  // IDirect3DDevice9::Reset( D3DPRESENT_PARAMETERS *pPresentationParameters )
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
  // ClientModeShared::CreateMove( float flInputSampleTime, CUserCmd *cmd )
  bool hooked_create_move(float input_sample_time, usercmd_t* cmd) {
    if (!cmd || !cmd->command_number)
      return false;

    bool* send_packet = reinterpret_cast<bool*>(_AddressOfReturnAddress()) + 0x138;

    client::on_create_move(cmd, send_packet);

    return false;
  }
  // ClientModeShared::OverrideView( CViewSetup *pSetup )
  void hooked_override_view(view_setup_t* setup) {
    client::g_hooks.override_view_hook.thiscall(this, setup);
  }
};

class hooked_surface {
public:
  // CMatSystemSurface::LockCursor()
  HCURSOR hooked_lock_cursor() {
    if (menu::open)
      return client::g_interfaces.surface->unlock_cursor();

    return client::g_hooks.lock_cursor_hook.thiscall<HCURSOR>(this);
  }
};

class hooked_prediction {
public:
  // CPrediction::RunCommand( C_BasePlayer *player, CUserCmd *ucmd, IMoveHelper *moveHelper )
  void hooked_run_command(client_player_t* player, usercmd_t* cmd, move_helper_t* move_helper) {
    if (move_helper)
      client::g_interfaces.move_helper = move_helper;

    client::g_hooks.run_command_hook.thiscall(this, player, cmd, move_helper);
  }
};

class hooked_base_client {
public:
  // void CHLClient::LevelShutdown( void )
  void hooked_level_shutdown() {
    client::g_hooks.level_shutdown_hook.thiscall(this);
    client::on_level_shutdown();
  }

  // void CHLClient::FrameStageNotify( ClientFrameStage_t curStage )
  void hooked_frame_stage_notify(client_frame_stage_e current_stage) {
    client::g_hooks.frame_stage_notify_hook.thiscall(this, current_stage);
  }
};

class hooked_model_render {
public:
  // CModelRender::DrawModelExecute( const DrawModelState_t &state, const ModelRenderInfo_t
  // &pInfo, matrix3x4_t *pBoneToWorld )
  void hooked_draw_model_execute(const draw_model_state_t&  state,
                                 const model_render_info_t& info,
                                 matrix_3x4_t*              custom_bone_to_world) {
    client::g_hooks.draw_model_execute_hook.thiscall(this, state, info, custom_bone_to_world);
  }
};

class hooked_engine_vgui {
public:
  // CEngineVGui::Paint( PaintMode_t mode )
  void hooked_paint(int32_t mode) {
    client::g_render.get_view_matrix();
    client::g_hooks.paint_hook.thiscall(this, mode);
  }
};

class hooked_panel {
public:
  // Panel::PaintTraverse( bool repaint, bool allowForce )
  void hooked_paint_traverse(unsigned long long vgui_panel, bool force_repaint,
                             bool allow_force) {
    client::g_hooks.paint_traverse_hook.thiscall(this, vgui_panel, force_repaint, allow_force);
  }
};

// =====================================================================================================
//                                          detour functions (sig)

// =====================================================================================================
//                                          initialization / unloading
bool hooks_t::initialize() {
  { // d3d9_device hooks
    hook_vmt(this->d3d9_device_hook, client::g_interfaces.d3d9_device, "d3d9_device");
    hook_vm(this->d3d9_device_hook, this->d3d9_present_hook,
            &hooked_d3d9_device::hooked_present, 17, "present");
    hook_vm(this->d3d9_device_hook, this->d3d9_reset_hook, &hooked_d3d9_device::hooked_reset,
            16, "reset");
  }

  { // client_mode_shared hooks
    hook_vmt(this->client_mode_hook, client::g_interfaces.client_mode, "client_mode");
    hook_vm(this->client_mode_hook, this->create_move_hook,
            &hooked_client_mode::hooked_create_move, 21, "createmove");
    hook_vm(this->client_mode_hook, this->override_view_hook,
            &hooked_client_mode::hooked_override_view, 16, "overrideview");
  }

  { // surface hooks
    hook_vmt(this->surface_hook, client::g_interfaces.surface, "surface");
    hook_vm(this->surface_hook, this->lock_cursor_hook, &hooked_surface::hooked_lock_cursor, 62,
            "lockcursor");
  }

  { // prediction hooks
    hook_vmt(this->prediction_hook, client::g_interfaces.prediction, "prediction");
    hook_vm(this->prediction_hook, this->run_command_hook,
            &hooked_prediction::hooked_run_command, 17, "runcommand");
  }

  { // base_client hooks
    hook_vmt(this->base_client_hook, client::g_interfaces.base_client, "base client");
    hook_vm(this->base_client_hook, this->level_shutdown_hook,
            &hooked_base_client::hooked_level_shutdown, 7, "levelshutdown");
    hook_vm(this->base_client_hook, this->frame_stage_notify_hook,
            &hooked_base_client::hooked_frame_stage_notify, 35, "frame stage notify");
  }
  { // model_render hooks
    hook_vmt(this->model_render_hook, client::g_interfaces.model_render, "model render");
    hook_vm(this->model_render_hook, this->draw_model_execute_hook,
            &hooked_model_render::hooked_draw_model_execute, 19, "draw model execute");
  }

  { // engine_vgui hooks
    hook_vmt(this->engine_vgui_hook, client::g_interfaces.engine_vgui, "engine vgui");
    hook_vm(this->engine_vgui_hook, this->paint_hook, &hooked_engine_vgui::hooked_paint, 14,
            "paint");
  }

  { // panel hooks
    hook_vmt(this->panel_hook, client::g_interfaces.panel, "panel");
    hook_vm(this->panel_hook, this->paint_traverse_hook, &hooked_panel::hooked_paint_traverse,
            41, "paint traverse");
  }

  client::g_console.printf("\tinline hooks:", console_color_light_yellow);

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
  engine_vgui_hook  = {};
  panel_hook        = {};
}