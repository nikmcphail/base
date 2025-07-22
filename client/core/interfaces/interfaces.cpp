#include "interfaces.h"

#include "library/pe.h"
#include "library/utils.h"

#include "client/client.h"
#include "valve/base_client_dll.h"
#include "valve/client_player.h"

#include <fmt/core.h>

std::vector<std::string> all_modules = {
    "shaderapidx9.dll",   "vstdlib.dll",      "client.dll",
    "vguimatsurface.dll", "engine.dll",       "inputsystem.dll",
    "materialsystem.dll", "studiorender.dll", "vgui2.dll"};

bool find_module(pe::module_t& module, const std::string& module_name) {
  if (!pe::get_module(module_name.c_str(), module)) {
    std::string formatted = fmt::format("\t\tfailed to find {}", module_name);
    client::g_console.print(formatted.c_str(), console_color_red);
    return false;
  }

  std::string formatted = fmt::format("\t\tfound {}", module_name);
  client::g_console.print(formatted.c_str(), console_color_light_aqua);
  return true;
}

bool find_all_modules(const std::vector<std::string>&                module_names,
                      std::unordered_map<std::string, pe::module_t>& out_modules) {
  for (const auto& name : module_names) {
    pe::module_t module;
    if (!find_module(module, name)) {
      return false;
    }
    out_modules[name] = module;
  }
  return true;
}

template <typename T>
bool find_interface(pe::module_t& module, T& out_interface, const std::string& interface_name,
                    const std::string& friendly_name) {
  out_interface = module.get_interface<T>(hash::hash_crc(interface_name.c_str()));
  if (!out_interface) {
    std::string msg = fmt::format("\t\tfailed to find {}", friendly_name);
    client::g_console.print(msg.c_str(), console_color_red);
    return false;
  }

  std::string msg = fmt::format("\t\tfound {}", friendly_name);
  client::g_console.print(msg.c_str(), console_color_light_aqua);
  return true;
}

bool interfaces_t::collect_interfaces() {

  client::g_console.printf("\tmodules:", console_color_light_yellow);
  std::unordered_map<std::string, pe::module_t> loaded_modules;
  if (!find_all_modules(all_modules, loaded_modules)) {
    client::g_console.print("\tOne or more required modules failed to load.",
                            console_color_red);
    return false;
  }

  pe::module_t& shaderapidx9_dll   = loaded_modules["shaderapidx9.dll"];
  pe::module_t& vstdlib_dll        = loaded_modules["vstdlib.dll"];
  pe::module_t& client_dll         = loaded_modules["client.dll"];
  pe::module_t& vguimatsurface_dll = loaded_modules["vguimatsurface.dll"];
  pe::module_t& engine_dll         = loaded_modules["engine.dll"];
  pe::module_t& inputsystem_dll    = loaded_modules["inputsystem.dll"];
  pe::module_t& materialsystem_dll = loaded_modules["materialsystem.dll"];
  pe::module_t& studiorender_dll   = loaded_modules["studiorender.dll"];
  pe::module_t& vgui2_dll          = loaded_modules["vgui2.dll"];

  client::g_console.printf("\taddresses:", console_color_light_yellow);
  this->d3d9_device = *(shaderapidx9_dll.find_pattern_in_memory("48 89 1D ?? ?? ?? ?? 48 8B CF")
                            .rel32<IDirect3DDevice9**>(0x3));
  if (!this->d3d9_device) {
    client::g_console.print("\t\tfailed to find d3d9 device", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound d3d9 device", console_color_light_aqua);

  this->global_vars =
      engine_dll.find_pattern_in_memory("48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 8B CA")
          .rel32<global_vars_base_t*>(0x3);
  if (!this->global_vars) {
    client::g_console.print("\t\tfailed to find global vars", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound global vars", console_color_light_aqua);

  this->input =
      *(client_dll
            .find_pattern_in_memory(
                "48 8B 0D ? ? ? ? 48 8B 01 FF 90 ? ? ? ? 85 C0 0F 84 ? ? ? ? F3 0F 10 05")
            .rel32<input_t**>(0x3));
  if (!this->input) {
    client::g_console.print("\t\tfailed to find input", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound input", console_color_light_aqua);

  this->prediction_player = client_dll.find_pattern_in_memory("48 89 3D ? ? ? ? 66 0F 6E 87")
                                .rel32<client_player_t**>(0x3);

  if (!this->prediction_player) {
    client::g_console.print("\t\tfailed to find prediction player", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound prediction player", console_color_light_aqua);

  this->client_state =
      engine_dll
          .find_pattern_in_memory("48 8D 0D ? ? ? ? 48 8B 5C 24 ? 48 83 C4 ? 5F E9 ? ? ? ? CC "
                                  "CC CC CC CC CC CC CC CC CC CC 48 89 6C 24")
          .rel32<client_state_t*>(0x3);
  if (!this->client_state) {
    client::g_console.print("\t\tfailed to find client state", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound client state", console_color_light_aqua);

  this->client_mode =
      *(client_dll
            .find_pattern_in_memory(
                "48 8B 0D ? ? ? ? 48 8B 01 48 FF 60 ? CC CC 48 83 EC ? 48 8D 0D")
            .rel32<void**>(0x3));
  if (!this->client_mode) {
    client::g_console.print("\t\tfailed to find client mode", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound client mode", console_color_light_aqua);

  client::g_console.printf("\tinterfaces:", console_color_light_yellow);

  if (!find_interface(vstdlib_dll, this->cvar, "VEngineCvar004", "cvar"))
    return false;

  if (!find_interface(client_dll, this->base_client, "VClient017", "base client"))
    return false;

  if (!find_interface(vguimatsurface_dll, this->surface, "VGUI_Surface030", "surface"))
    return false;

  if (!find_interface(client_dll, this->entity_list, "VClientEntityList003", "entity list"))
    return false;

  if (!find_interface(client_dll, this->prediction, "VClientPrediction001", "prediction"))
    return false;

  if (!find_interface(client_dll, this->game_movement, "GameMovement001", "game movement"))
    return false;

  if (!find_interface(engine_dll, this->engine_client, "VEngineClient013", "engine client"))
    return false;

  if (!find_interface(inputsystem_dll, this->input_system, "InputSystemVersion001",
                      "input system"))
    return false;

  if (!find_interface(engine_dll, this->model_info, "VModelInfoClient006", "model info"))
    return false;

  if (!find_interface(engine_dll, this->engine_trace, "EngineTraceClient003", "engine trace"))
    return false;

  if (!find_interface(materialsystem_dll, this->material_system, "VMaterialSystem082",
                      "material system"))
    return false;

  if (!find_interface(engine_dll, this->model_render, "VEngineModel016", "model render"))
    return false;

  if (!find_interface(engine_dll, this->render_view, "VEngineRenderView014", "render view"))
    return false;

  if (!find_interface(engine_dll, this->engine_vgui, "VEngineVGui001", "engine vgui"))
    return false;

  if (!find_interface(vgui2_dll, this->panel, "VGUI_Panel009", "panel"))
    return false;

  client::g_console.print("\tinterfaces initialized", console_color_gray);
  return true;
}