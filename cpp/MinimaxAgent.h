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

constexpr float FLOAT_INF = std::numeric_limits<float>::max();

class MinimaxAgent : public Agent {
public:
  MinimaxAgent(std::default_random_engine& r, const int d): rng(r), max_depth(d){};
  void new_game(const State&){};
  Action get_action(const State&, const Action&);
  std::string get_description();
  
private:
  float heuristic_value(const State&);
  float minimax(const State&, int);
  
  int max_depth = 1;
  std::default_random_engine rng;
};

float MinimaxAgent::heuristic_value(const State& s){
  // return heuristic reward for current player
  // current reward function:
  //  - reward of +/-2 for winning/losing
  //  - heuristic reward in [-1,1] for non-terminal states
  //  - heuristic accounts for pawn advantage and gate proximity
  float gate_capture_reward = 2;
  float master_capture_reward = 2;
  switch(get_result(s)){
    case BLUE_GATE_TAKEN:
      return gate_capture_reward * (1 - 2 * s.player);
    case RED_GATE_TAKEN:
      return gate_capture_reward * (2 * s.player - 1);
    case BLUE_MASTER_TAKEN:
      return master_capture_reward * (1 - 2 * s.player);
    case RED_MASTER_TAKEN:
      return master_capture_reward * (2 * s.player - 1);
    case NO_RESULT:
      break;
  }
  
  // pawn reward (advantage in pawn count)
  float red_pawns = 0;
  float blue_pawns = 0;
  for(int i = 0; i < 25; i++){
    if(s.board[2].test(i)){
      red_pawns++;
      
    } else if(s.board[3].test(i)){
      blue_pawns++;
    }
  }
  float pawn_reward = 0;  // takes values in [-1,1]
  if(red_pawns + blue_pawns > 0){
    pawn_reward = (red_pawns - blue_pawns)/(red_pawns + blue_pawns) * (1 - 2 * s.player);
  }
  
  // master reward (advantage if you are closer to gate than they are)
  float red_master = 0;
  float blue_master = 0;
  for(int i = 0; i < 25; i++){
    if(s.board[0].test(i)){
      red_master = abs(i % 5 - 2) + abs(i / 5 - 4); // L1 distance from blue gate
    } else if(s.board[1].test(i)){
      blue_master = abs(i % 5 - 2) + abs(i / 5);
    }
  }
  // takes values in [-1,1].
  float master_reward = - (7 / 5) * (red_master - blue_master)/(red_master + blue_master) * (1 - 2 * s.player) ;
  
  return 0.5 * pawn_reward + 0.5 * master_reward;
}

float MinimaxAgent::minimax(const State& s, int current_depth){
  if(current_depth == max_depth or get_result(s) != NO_RESULT){
    return -heuristic_value(s);
  }
  float value = -FLOAT_INF;
  for(auto a : get_valid_actions(s)){
    value = std::max(value, minimax(next_state(s, a), current_depth + 1));
  }
  return -value;
}

Action MinimaxAgent::get_action(const State& s, const Action& prev_action){
  // return best action according to minimax
  Action best_action{NONE, 0, 0};
  float best_value = -FLOAT_INF;
  
  for(auto a : get_valid_actions(s)){
    float value = minimax(next_state(s, a), 1); // + eps
    if(value > best_value){
      best_value = value;
      best_action = a;
    }
  }
  return best_action;
}

std::string MinimaxAgent::get_description(){
  std::string description = "{\n    \"name\": \"MinimaxAgent\",\n    \"param\": [\n      \"max_depth\": " + std::to_string(max_depth) + "\n    ]\n  }";
  return description;
}

#endif /* MinimaxAgent_h */
