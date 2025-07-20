#include "interfaces.h"

#include "library/pe.h"
#include "library/utils.h"

#include "client/client.h"
#include "valve/base_client_dll.h"
#include "valve/client_player.h"

bool interfaces_t::collect_interfaces() {

  client::g_console.printf("\tmodules:", console_color_light_yellow);
  pe::module_t shaderapidx9_dll;
  if (!pe::get_module("shaderapidx9.dll", shaderapidx9_dll)) {
    client::g_console.print("\t\tfailed to find shader api", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound shader api", console_color_light_aqua);

  pe::module_t vstdlib_dll;
  if (!pe::get_module("vstdlib.dll", vstdlib_dll)) {
    client::g_console.print("\t\tfailed to find vstdlib", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound vstdlib", console_color_light_aqua);

  pe::module_t client_dll;
  if (!pe::get_module("client.dll", client_dll)) {
    client::g_console.print("\t\tfailed to find client", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound client", console_color_light_aqua);

  pe::module_t vguimatsurface_dll;
  if (!pe::get_module("vguimatsurface.dll", vguimatsurface_dll)) {
    client::g_console.print("\t\tfailed to find vguimatsurface", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound vguimatsurface", console_color_light_aqua);

  pe::module_t engine_dll;
  if (!pe::get_module("engine.dll", engine_dll)) {
    client::g_console.print("\t\tfailed to find engine", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound engine", console_color_light_aqua);

  pe::module_t inputsystem_dll;
  if (!pe::get_module("inputsystem.dll", inputsystem_dll)) {
    client::g_console.print("\t\tfailed to find inputsystem", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound inputsystem", console_color_light_aqua);

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

  client::g_console.printf("\tinterfaces:", console_color_light_yellow);

  this->cvar = vstdlib_dll.get_interface<cvar_t*>(HASH("VEngineCvar004"));
  if (!this->cvar) {
    client::g_console.print("\t\tfailed to find cvar", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound cvar", console_color_light_aqua);

  this->base_client = client_dll.get_interface<base_client_dll_t*>(HASH("VClient017"));
  if (!this->base_client) {
    client::g_console.print("\t\tfailed to find base client", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound base client", console_color_light_aqua);

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

  this->surface = vguimatsurface_dll.get_interface<surface_t*>(HASH("VGUI_Surface030"));
  if (!this->surface) {
    client::g_console.print("\t\tfailed to find surface", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound surface", console_color_light_aqua);

  this->entity_list = client_dll.get_interface<entity_list_t*>(HASH("VClientEntityList003"));
  if (!this->entity_list) {
    client::g_console.print("\t\tfailed to find entity list", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound entity list", console_color_light_aqua);

  this->prediction = client_dll.get_interface<prediction_t*>(HASH("VClientPrediction001"));
  if (!this->prediction) {
    client::g_console.print("\t\tfailed to find prediction", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound prediction", console_color_light_aqua);

  this->game_movement = client_dll.get_interface<game_movement_t*>(HASH("GameMovement001"));
  if (!this->game_movement) {
    client::g_console.print("\t\tfailed to find game movement", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound game movement", console_color_light_aqua);

  this->engine_client = engine_dll.get_interface<engine_client_t*>(HASH("VEngineClient013"));
  if (!this->engine_client) {
    client::g_console.print("\t\tfailed to find engine client", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound engine client", console_color_light_aqua);

  this->input_system =
      inputsystem_dll.get_interface<input_system_t*>(HASH("InputSystemVersion001"));
  if (!this->input_system) {
    client::g_console.print("\t\tfailed to find input system", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound input system", console_color_light_aqua);

  this->model_info = engine_dll.get_interface<model_info_t*>(HASH("VModelInfoClient006"));
  if (!this->model_info) {
    client::g_console.print("\t\tfailed to find model info", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound model info", console_color_light_aqua);

  this->engine_trace = engine_dll.get_interface<engine_trace_t*>(HASH("EngineTraceClient003"));
  if (!this->engine_trace) {
    client::g_console.print("\t\tfailed to find engine trace", console_color_red);
    return false;
  }
  client::g_console.print("\t\tfound engine trace", console_color_light_aqua);

  client::g_console.print("\tinterfaces initialized", console_color_gray);
  return true;
}