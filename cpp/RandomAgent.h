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

#include "Onitama.h"
#include "Agent.h"

class RandomAgent : public Agent {
public:
  RandomAgent(std::default_random_engine& r) : rng{r}{};
  Onitama::Action get_action(const Onitama::State&, const Onitama::Action&);
  std::string get_description();
  void new_game(const Onitama::State&){};
private:
  std::default_random_engine& rng;
};

Onitama::Action RandomAgent::get_action(const Onitama::State& s, const Onitama::Action& a){
  std::vector<Onitama::Action> actions = s.get_valid_actions();
  std::uniform_int_distribution<int> unif(0, int(actions.size()) - 1);
  return actions[unif(rng)];
}

std::string RandomAgent::get_description(){
  std::string description ="{\n    \"name\": \"RandomAgent\",\n    \"param\": {}\n  }";
  return description;
}

#endif /* RandomAgent_h */
