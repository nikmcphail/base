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
#include "valve/panel.h"
#include "valve/game_event.h"
#include "valve/net_channel.h"
#include "valve/start_sound_params.h"

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
    return client::g_hooks.d3d9_present_hook.fastcall<HRESULT>(
        this, device, source_rect, dest_rect, dest_window_override, dirty_region);
  }

  // IDirect3DDevice9::Reset( D3DPRESENT_PARAMETERS *pPresentationParameters )
  HRESULT hooked_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_parameters) {
    HRESULT result;

    {
      std::scoped_lock _{client::g_render.imgui_mutex};
      client::g_render.detach();
      result =
          client::g_hooks.d3d9_reset_hook.fastcall<HRESULT>(this, device, present_parameters);
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
    client::g_hooks.override_view_hook.fastcall(this, setup);
  }

  // ClientModeShared::GetViewModelFOV( void )
  float hooked_get_viewmodel_fov() {
    return client::g_hooks.get_viewmodel_fov_hook.fastcall<float>(this);
  }
};

class hooked_surface {
public:
  // CMatSystemSurface::LockCursor()
  HCURSOR hooked_lock_cursor() {
    if (menu::open)
      return client::g_interfaces.surface->unlock_cursor();

    return client::g_hooks.lock_cursor_hook.fastcall<HCURSOR>(this);
  }
};

class hooked_prediction {
public:
  // CPrediction::RunCommand( C_BasePlayer *player, CUserCmd *ucmd, IMoveHelper *moveHelper )
  void hooked_run_command(player_t* player, usercmd_t* cmd, move_helper_t* move_helper) {
    if (move_helper)
      client::g_interfaces.move_helper = move_helper;

    client::g_hooks.run_command_hook.fastcall(this, player, cmd, move_helper);
  }
};

class hooked_base_client {
public:
  // void CHLClient::LevelShutdown( void )
  void hooked_level_shutdown() {
    client::g_hooks.level_shutdown_hook.fastcall(this);
    client::on_level_shutdown();
  }

  // void CHLClient::FrameStageNotify( ClientFrameStage_t curStage )
  void hooked_frame_stage_notify(client_frame_stage_e current_stage) {
    client::g_hooks.frame_stage_notify_hook.fastcall(this, current_stage);
    client::on_frame_stage_notify(current_stage);
  }
};

class hooked_model_render {
public:
  // CModelRender::DrawModelExecute( const DrawModelState_t &state, const ModelRenderInfo_t
  // &pInfo, matrix3x4_t *pBoneToWorld )
  void hooked_draw_model_execute(const draw_model_state_t&  state,
                                 const model_render_info_t& info,
                                 matrix_3x4_t*              custom_bone_to_world) {
    client::g_hooks.draw_model_execute_hook.fastcall(this, state, info, custom_bone_to_world);
  }
};

class hooked_engine_vgui {
public:
  // CEngineVGui::Paint( PaintMode_t mode )
  void hooked_paint(int32_t mode) {
    client::on_paint();
    client::g_hooks.paint_hook.fastcall(this, mode);
  }
};

class hooked_panel {
public:
  // Panel::PaintTraverse( bool repaint, bool allowForce )
  void hooked_paint_traverse(unsigned long long vgui_panel, bool force_repaint,
                             bool allow_force) {
    static unsigned long long panel_id = 0;

    client::g_hooks.paint_traverse_hook.fastcall(this, vgui_panel, force_repaint, allow_force);

    if (!panel_id) {
      const auto panel_name = client::g_interfaces.panel->get_name(vgui_panel);
      if (!strcmp(panel_name, "MatSystemTopPanel"))
        panel_id = vgui_panel;
    }

    if (vgui_panel == panel_id) {}
  }
};

class hooked_game_events_manager {
public:
  // bool CGameEventManager::FireEvent( IGameEvent* event, bool bServerOnly)
  bool hooked_fire_event(game_event_t* event, bool dont_broadcast) {
    return client::g_hooks.fire_event_hook.fastcall<bool>(this, event, dont_broadcast);
  }
};

class hooked_engine_client {
public:
  // void CEngineClient::ClientCmd_Unrestricted(const char* szCmdString)
  void hooked_client_cmd_unrestricted(const char* cmd) {
    return client::g_hooks.client_cmd_unrestricted_hook.fastcall(this, cmd);
  }
};

// =====================================================================================================
//                                           detour functions (sig)

// void CL_Move( float accumulated_extra_samples, bool bFinalTick )
// void hooked_cl_move(float accumulated_extra_samples, bool final_tick) {
//   client::g_hooks.cl_move_hook.fastcall(accumulated_extra_samples, final_tick);
// }

// int CNetChan::SendDataGram( bf_write* datagram )
int hooked_send_datagram(net_channel_t* _thisptr, void* datagram) {
  return client::g_hooks.send_datagram_hook.fastcall<int>(_thisptr, datagram);
}

// int S_StartDynamicSound( StartSoundParams_t& params )
int hooked_start_dynamic_sound(start_sound_params_t& params) {
  return client::g_hooks.start_dynamic_sound_hook.fastcall<int>(params);
}

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
    hook_vm(this->client_mode_hook, this->get_viewmodel_fov_hook,
            &hooked_client_mode::hooked_get_viewmodel_fov, 32, "getviewmodelfov");
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

  { // game events manager hooks
    hook_vmt(this->game_events_manager_hook, client::g_interfaces.game_events_manager,
             "game events manager");
    hook_vm(this->game_events_manager_hook, this->fire_event_hook,
            &hooked_game_events_manager::hooked_fire_event, 8, "fire event");
  }

  { // engine client hooks
    hook_vmt(this->engine_client_hook, client::g_interfaces.engine_client, "engine client");
    hook_vm(this->engine_client_hook, this->client_cmd_unrestricted_hook,
            &hooked_engine_client::hooked_client_cmd_unrestricted, 106,
            "client cmd unrestricted");
  }

  client::g_console.printf("\tinline hooks:", console_color_light_yellow);
  { // inline hooks
    // hook_inline(this->cl_move_hook, &hooked_cl_move,
    //             (void*)client::g_addresses.engine.functions.cl_move, "cl move");
    hook_inline(this->send_datagram_hook, &hooked_send_datagram,
                (void*)client::g_addresses.engine.functions.send_datagram, "send datagram");
    hook_inline(this->start_dynamic_sound_hook, &hooked_start_dynamic_sound,
                (void*)client::g_addresses.engine.functions.start_dynamic_sound,
                "start dynamic sound");
  }

  client::g_console.print("\thooks initialized", console_color_gray);
  return true;
}

void hooks_t::unload() {
  d3d9_device_hook         = {};
  client_mode_hook         = {};
  surface_hook             = {};
  prediction_hook          = {};
  base_client_hook         = {};
  model_render_hook        = {};
  engine_vgui_hook         = {};
  panel_hook               = {};
  game_events_manager_hook = {};
  engine_client_hook       = {};
}