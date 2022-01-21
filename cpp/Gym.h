//
//  Gym.h
//
//  Created by Jeremy Lane
//
//  Todo: swap who goes first each turn
//        record data
//        impose resource limits

#ifndef Gym_h
#define Gym_h

#include "Agent.h"
#include "Utils.h"

class Gym {
public:
  Gym(Agent& p0, Agent& p1, std::default_random_engine& r) : player0 {p0}, player1 {p1}, rng {r} {};
  void play_game();
  void pit(int);
  
private:
  Agent& player0;
  Agent& player1;
  std::default_random_engine& rng;
};

void Gym::play_game(){
  
  State s = new_game(rng);
  
  player0.new_game(s);
  player1.new_game(s);
  
  Action a{PASS, 0, 0};
  
  int t = 0;
  
  while (get_result(s) == NO_RESULT && t < 1000){
    if(t % 2 == 0){
      a = player0.get_action(s, a);
    } else {
      a = player1.get_action(s, a);
    }
    s = next_state(s, a);
    t++;
  }
  
  // optional
  std::cout << "Game ended on turn " << t << std::endl;
  display_board(s);
}

void Gym::pit(int num_games){
  // currently player 0 goes first every time. Add shuffle later.
  
//  std::array<int, 3> outcomes(3, 0);
  
  for(int i = 0; i < num_games; i++){
    play_game();
  }
    
//    // currently bad logic
//    if(r > 0){
//      outcomes[0]++;
//    } else if(r < 0){
//      outcomes[1]++;
//    } else {
//      outcomes[2]++;
//    }
//  }
//
//  std::cout << "Player 0 won " << outcomes[0] << " times." << std::endl;
//  std::cout << "Player 1 won " << outcomes[1] << " times." << std::endl;
//  std::cout << "There were " << outcomes[2] << " draws." << std::endl;
}


#endif /* Gym_h */
