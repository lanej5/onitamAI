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
#include "Logger.h"

class Gym {
public:
  Gym(Agent& red, Agent& blue, std::default_random_engine& r, Logger& l) : red_agent {red}, blue_agent {blue}, rng {r}, logger {l} {};
  void play_game();
  void pit(int);
  
private:
  Agent& red_agent;
  Agent& blue_agent;
  std::default_random_engine& rng;
  Logger& logger;
};

void Gym::play_game(){

  State start_state = new_game(rng);
  State s = start_state;
  
  red_agent.new_game(s);
  blue_agent.new_game(s);
  
  Action a{NONE, 0, 0};
  
  int t = 0;
  Result result = get_result(s);
  
  while (result == NO_RESULT && t < 200){
    if(s.player == RED){
      a = red_agent.get_action(s, a);
    } else {
      a = blue_agent.get_action(s, a);
    }
    s = next_state(s, a);
    t++;
    result = get_result(s);
  }
  
  logger.log(start_state, s, result, t);
  
  return;
}

void Gym::pit(int num_games){
  for(int i = 0; i < num_games; i++){
    play_game();
  }
}

#endif /* Gym_h */
