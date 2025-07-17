#pragma once

#include "library/utils.h"

class client_player_t;
class usercmd_t;
class move_helper_t;
class move_data_t;

class prediction_t {
public:
  void set_local_view_angles(vector3_t& ang) {
    utils::get_virtual_function<void(__thiscall*)(prediction_t*, vector3_t&)>(this, 16)(this,
                                                                                        ang);
  }

  void run_command(client_player_t* player, usercmd_t* cmd, move_helper_t* move_helper) {
    utils::get_virtual_function<void(__thiscall*)(prediction_t*, client_player_t*, usercmd_t*,
                                                  move_helper_t*)>(this, 17)(this, player, cmd,
                                                                             move_helper);
  }

  void setup_move(client_player_t* player, usercmd_t* cmd, move_helper_t* move_helper,
                  move_data_t* move_data) {
    utils::get_virtual_function<void(__thiscall*)(prediction_t*, client_player_t*, usercmd_t*,
                                                  move_helper_t*, move_data_t*)>(this, 18)(
        this, player, cmd, move_helper, move_data);
  }

  void finish_move(client_player_t* player, usercmd_t* cmd, move_data_t* move_data) {
    utils::get_virtual_function<void(__thiscall*)(prediction_t*, client_player_t*, usercmd_t*,
                                                  move_data_t*)>(this, 19)(this, player, cmd,
                                                                           move_data);
  }

  void restore_entity_to_predicted_frame(unsigned int predicted_frame) {
    static auto func = (void(__thiscall*)(
        void*,
        unsigned int))client::g_addresses.client.functions.restore_entity_to_predicted_frame;
    func(this, predicted_frame);
  }

public:
  uintptr_t last_ground;
  bool      in_prediction;
  bool      first_time_predicted;
  bool      old_cl_predict_value;
  bool      engine_paused;
  int       previous_start_frame;
  int       commands_predicted;
};