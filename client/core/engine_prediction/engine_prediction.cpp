#include "engine_prediction.h"

#include "valve/cusercmd.h"
#include "valve/move_data.h"
#include "valve/client_local_player.h"
#include "client/client.h"
#include "valve/move_helper.h"
#include "valve/prediction.h"
#include "valve/global_vars_base.h"
#include "library/md5.h"

float ticks_to_time(int ticks) {
  return client::g_interfaces.global_vars->interval_per_tick * (float)ticks;
}

int get_tickbase(client_player_t* local, usercmd_t* cmd) {
  static int        tick     = 0;
  static usercmd_t* last_cmd = nullptr;

  if (cmd) {
    if (!last_cmd || last_cmd->predicted)
      tick = local->tick_base();
    else
      tick++;

    last_cmd = cmd;
  }

  return tick;
}

inline usercmd_t*& set_command(client_player_t* player) {
  return *reinterpret_cast<usercmd_t**>(reinterpret_cast<uintptr_t>(player) + 0x15B8);
}

void engine_prediction_t::start_prediction(usercmd_t* cmd) {
  if (!client::g_interfaces.move_helper)
    return;

  client_local_player_t* local_player = client_player_t::get_local_player();
  if (!local_player || !local_player->is_alive())
    return;

  old_curtime                                = client::g_interfaces.global_vars->cur_time;
  old_frametime                              = client::g_interfaces.global_vars->frame_time;
  old_flags                                  = local_player->flags();
  client::g_interfaces.global_vars->cur_time = ticks_to_time(local_player->tick_base());
  client::g_interfaces.global_vars->frame_time =
      client::g_interfaces.global_vars->interval_per_tick;

  client::g_interfaces.move_helper->set_host(local_player);

  client::g_interfaces.prediction->run_command(local_player, cmd,
                                               client::g_interfaces.move_helper);
}

void engine_prediction_t::finish_prediction() {
  if (!client::g_interfaces.move_helper)
    return;

  client_player_t* local_player = client_player_t::get_local_player();
  if (!local_player || !local_player->is_alive())
    return;

  client::g_interfaces.global_vars->cur_time   = old_curtime;
  client::g_interfaces.global_vars->frame_time = old_frametime;
  local_player->flags()                        = old_flags;

  client::g_interfaces.move_helper->set_host(nullptr);
}