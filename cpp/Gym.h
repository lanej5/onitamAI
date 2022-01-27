//
//  Gym.h
//
//  Created by Jeremy Lane
//
//  Todo: record data
//        impose resource limits

#ifndef Gym_h
#define Gym_h

#include <map>
#include "Agent.h"
#include "Utils.h"

class Gym {
public:
  Gym(Agent& red, Agent& blue, std::default_random_engine& r) : red_agent {red}, blue_agent {blue}, rng {r} {};
  Result play_game();
  void pit(int);
  
private:
  Agent& red_agent;
  Agent& blue_agent;
  std::default_random_engine& rng;
};

Result Gym::play_game(){

  State s = new_game(rng);
  
  red_agent.new_game(s);
  blue_agent.new_game(s);
  
  Action a{NONE, 0, 0};
  
  int t = 0;
  
  while (get_result(s) == NO_RESULT && t < 200){
    if(s.player == RED){
      a = red_agent.get_action(s, a);
    } else {
      a = blue_agent.get_action(s, a);
    }
    s = next_state(s, a);
    t++;
  }

  // make optional
  //std::cout << "Game ended on turn " << t << std::endl;
  //display_board(s);
  
  return get_result(s);
}

void Gym::pit(int num_games){
  std::map<Result, int> results{{BLUE_GATE_TAKEN, 0}, {RED_GATE_TAKEN, 0}, {BLUE_MASTER_TAKEN, 0}, {RED_MASTER_TAKEN, 0}, {NO_RESULT, 0}};
  
  for(int i = 0; i < num_games; i++){
    results[play_game()]++;
  }
  
  std::cout << "Total red wins: " << results[BLUE_GATE_TAKEN] + results[BLUE_MASTER_TAKEN] << std::endl;
  std::cout << "  Number of master captures: " << results[BLUE_MASTER_TAKEN] << std::endl;
  std::cout << "  Number of gate captures: " << results[BLUE_GATE_TAKEN] << std::endl;
  std::cout << "Total blue wins: " << results[RED_GATE_TAKEN] + results[RED_MASTER_TAKEN] << std::endl;
  std::cout << "  Number of master captures: " << results[RED_MASTER_TAKEN] << std::endl;
  std::cout << "  Number of gate captures: " << results[RED_GATE_TAKEN] << std::endl;
  std::cout << "Total gate captures: " << results[RED_GATE_TAKEN] + results[BLUE_GATE_TAKEN] << std::endl;
  std::cout << "Total master captures: " << results[RED_MASTER_TAKEN] + results[BLUE_MASTER_TAKEN] << std::endl;
}


#endif /* Gym_h */
