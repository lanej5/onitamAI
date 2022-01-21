//
//  UCTNode.cpp
//
//  Created by Jeremy Lane
//

#include "UCTNode.h"
#include "Reward.h"

#include <cmath>

const float FLOAT_N_INF = -std::numeric_limits<float>::max();
const int INT_N_INF = std::numeric_limits<int>::min();

std::uniform_real_distribution<float> EPS(-1e-6, 1e-6);

UCTNode::UCTNode(State s){
  state = s;
  r = get_reward(state);
  if(r == 0){
    actions = get_valid_actions(state);
    children = std::vector<std::shared_ptr<UCTNode>>(actions.size());
  }
}

bool UCTNode::fully_expanded(){
  for(int i = 0; i < children.size(); i++){
    if(!children[i]){
      return false;
    }
  }
  return true;
}

inline std::vector<int> UCTNode::unexpanded_indices(){
  // Return vector of indices of actions that have not been expanded.
  std::list<int> l;
  for(int i = 0; i < children.size(); i++){
    if(!children[i]){
      l.push_back(i);
    }
  }
  return std::vector<int>{l.begin(), l.end()};
}

int UCTNode::expand(std::default_random_engine& rng){
  // EXPAND
  //
  // Randomly expand an unexpanded child node.
  //
  auto idx = unexpanded_indices();
  
  if(idx.empty()){
    // error
  }
  
  // randomly select child to expand
  std::uniform_int_distribution<int> unif(0, int(idx.size() - 1));
  auto i = idx[unif(rng)];
  
  expand(i);
  return i;
}

void UCTNode::expand(int k){
  // Creates a new node as children[k]
  if(!children[k]){
    children[k] = std::make_shared<UCTNode>(next_state(state, actions[k]));
  }
}

int UCTNode::best_child(std::default_random_engine& rng, const float& c){
  // Assumes node is fully expanded
  
  if(!fully_expanded()){
    // error
  }
  
  float best_uct = FLOAT_N_INF;
  int idx = INT_N_INF;
  float uct = 0;
  
  if(N != 0){
    for(int i = 0; i < actions.size(); i++){
      if(children[i]->N != 0){
        uct = children[i]->Q / children[i]->N + c * sqrt(2 * log(N) / children[i]->N);
      } else {
        uct = 1000000;
      }
      if (uct + EPS(rng) > best_uct){
        best_uct = uct;
        idx = i;
      }
    }
    return idx;
  } else {
    std::uniform_int_distribution<int> unif(0, int(actions.size()) - 1);
    return unif(rng);
  }
}
