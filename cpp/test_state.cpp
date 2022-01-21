//
//  test_state.cpp
//
//  Created by Jeremy Lane.
//

#include <iostream>

#include "State.h"

using namespace std;

int main(){
  int max_turns = 100;
  int seed = 6;
  std::default_random_engine rng(seed);
  State s = new_game(rng);
  
  display_board(s);
  
  int t = 0;
  while (get_result(s) == NO_RESULT && t <= max_turns){
    
    std::vector<Action> actions = get_valid_actions(s);
    
    std::uniform_int_distribution<int> unif(0, int(actions.size()-1));
    Action a = actions[unif(rng)];
    s = next_state(s, a);
    
    std::cout << "Turn " << t << std::endl;
    
    display_board(s);
    
    t++;
  }

  return 0;
};
