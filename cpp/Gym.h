//
//  Gym.h
//
//  Created by Jeremy Lane
//
//  Todo: record data
//        impose resource limits

#ifndef Gym_h
#define Gym_h

#include "Agent.h"
#include "Utils.h"

class Gym {
public:
  Gym(Agent& red, Agent& blue, std::default_random_engine& r) : red_agent {red}, blue_agent {blue}, rng {r} {};
  void play_game();
  void pit(int);
  
private:
  Agent& red_agent;
  Agent& blue_agent;
  std::default_random_engine& rng;
};

void Gym::play_game(){
  
  State s = new_game(rng);
  
  red_agent.new_game(s);
  blue_agent.new_game(s);
  
  Action a{NONE, 0, 0};
  
  int t = 0;
  
  while (get_result(s) == NO_RESULT && t < 1000){
    if(s.player == RED){
      a = red_agent.get_action(s, a);
    } else {
      a = blue_agent.get_action(s, a);
    }
    s = next_state(s, a);
    t++;
  }
  
  // optional
  std::cout << "Game ended on turn " << t << std::endl;
  display_board(s);
}

void Gym::pit(int num_games){
  
  for(int i = 0; i < num_games; i++){
    play_game();
  }
}


#endif /* Gym_h */
