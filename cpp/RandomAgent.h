//
//  RandomAgent.h
//
//  Created by Jeremy Lane
//
//  This baseline agent plays Onitama by randomly choosing actions.

#ifndef RandomAgent_h
#define RandomAgent_h

#include <random>
#include <string>
#include "Agent.h"

class RandomAgent : public Agent {
public:
  RandomAgent(std::default_random_engine& r) : rng{r}{};
  Action get_action(const State&, const Action&);
  std::string get_description();
  void new_game(const State&){};
private:
  std::default_random_engine& rng;
};

Action RandomAgent::get_action(const State& s, const Action& a){
  std::vector<Action> actions = get_valid_actions(s);
  std::uniform_int_distribution<int> unif(0, int(actions.size()) - 1);
  return actions[unif(rng)];
}

std::string RandomAgent::get_description(){
  std::string description ="{\n    \"name\": \"RandomAgent\",\n    \"param\": {}\n  }";
  return description;
}

#endif /* RandomAgent_h */
