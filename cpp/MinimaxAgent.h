//
//  MinimaxAgent.h
//
//  Created by Jeremy Lane
//

#ifndef MinimaxAgent_h
#define MinimaxAgent_h

#include <algorithm>
#include <cmath>
#include <random>
#include <string>

#include "Agent.h"
#include "Onitama.h"

constexpr float FLOAT_INF = std::numeric_limits<float>::max();

class MinimaxAgent : public Agent {
public:
  MinimaxAgent(std::default_random_engine& r, const int d): rng(r), max_depth(d){};
  void new_game(const Onitama::State&){};
  Onitama::Action get_action(const Onitama::State&, const Onitama::Action&);
  std::string get_description();
  
private:
  float heuristic_value(const Onitama::State&);
  float minimax(const Onitama::State&, int);
  
  int max_depth = 1;
  std::default_random_engine rng;
};

float MinimaxAgent::heuristic_value(const Onitama::State& s){
  // return heuristic reward for current player
  // current reward function:
  //  - reward of +/-2 for winning/losing
  //  - heuristic reward in [-1,1] for non-terminal states
  //  - heuristic accounts for pawn advantage and gate proximity
  float gate_capture_reward = 2;
  float master_capture_reward = 2;
  Onitama::Player player = s.get_player();
  switch(s.get_result()){
    case Onitama::BLUE_GATE_TAKEN:
      return gate_capture_reward * (1 - 2 * player);
    case Onitama::RED_GATE_TAKEN:
      return gate_capture_reward * (2 * player - 1);
    case Onitama::BLUE_MASTER_TAKEN:
      return master_capture_reward * (1 - 2 * player);
    case Onitama::RED_MASTER_TAKEN:
      return master_capture_reward * (2 * player - 1);
    case Onitama::NO_RESULT:
      break;
  }
  
  // pawn reward (advantage in pawn count)
  int red_pawns = s.red_pawn_count();
  int blue_pawns = s.blue_pawn_count();
  float pawn_reward = (red_pawns - blue_pawns)/(red_pawns + blue_pawns + 0.0001) * (1 - 2 * player);;  // takes values in [-1, 1]
  
  // master reward (advantage if you are closer to gate than they are)
  int red_master_bit = s.red_master_bit();
  int blue_master_bit = s.blue_master_bit();
  int red_master_l1 = abs(red_master_bit % 5 - 2) + abs(red_master_bit / 5 - 4); // L1 distance from blue gate, guaranteed > 0
  int blue_master_l1 = abs(blue_master_bit % 5 - 2) + abs(blue_master_bit / 5);

  // takes values in [-1,1].
  float master_reward = - (7 / 5) * (red_master_l1 - blue_master_l1)/(red_master_l1 + blue_master_l1 + 0.0001) * (1 - 2 * player) ;
  
  return 0.5 * pawn_reward + 0.5 * master_reward;
}

float MinimaxAgent::minimax(const Onitama::State& s, int current_depth){
  if(current_depth == max_depth or s.get_result() != Onitama::NO_RESULT){
    return -heuristic_value(s);
  }
  float value = -FLOAT_INF;
  for(auto a : s.get_valid_actions()){
    value = std::max(value, minimax(s.next_state(a), current_depth + 1));
  }
  return -value;
}

Onitama::Action MinimaxAgent::get_action(const Onitama::State& s, const Onitama::Action& prev_action){
  // return best action according to minimax
  Onitama::Action best_action{Onitama::NONE, Onitama::Master, 0, 0};
  float best_value = -FLOAT_INF;
  
  for(auto a : s.get_valid_actions()){
    float value = minimax(s.next_state(a), 1); // + eps
    if(value > best_value){
      best_value = value;
      best_action = a;
    }
  }
  return best_action;
}

std::string MinimaxAgent::get_description(){
  std::string description = "{\n    \"name\": \"MinimaxAgent\",\n    \"param\": {\n      \"max_depth\": " + std::to_string(max_depth) + "\n    }\n  }";
  return description;
}

#endif /* MinimaxAgent_h */
