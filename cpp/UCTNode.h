//
//  UCTNode.h
//
//  Created by Jeremy Lane
//
//  Implements node class used by UCTAgent.h

#ifndef UCTNode_h
#define UCTNode_h

#include <memory>
#include <limits>

#include "Action.h"
#include "State.h"

class UCTNode {
public:
  UCTNode(State);
  int expand(std::default_random_engine& rng);
  int best_child(std::default_random_engine& rng, const float&);
  bool fully_expanded();
  
  State state;
  int N = 0;    // number of times visited
  float Q = 0.; // Q-value
  float r;      // reward associated with state
  std::vector<std::shared_ptr<UCTNode>> children;
  std::vector<Action> actions;

private:
  std::vector<int> unexpanded_indices();
  void expand(int);
};

#endif /* UCTNode_h */
