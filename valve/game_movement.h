#pragma once

class client_player_t;
class move_data_t;

class game_movement_t {
public:
  virtual ~game_movement_t(void) {}
  virtual void process_movement(client_player_t* player, move_data_t* move_data) = 0;
  virtual void start_track_prediction_errors(client_player_t* player = 0);
  virtual void finish_track_prediction_errors(client_player_t* player = 0);
};