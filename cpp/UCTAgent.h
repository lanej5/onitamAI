//
//  UCTAgent.h
//
//  Created by Jeremy Lane
//
//  Plays Onitama with UCT MCTS

#ifndef UCTAgent_h
#define UCTAgent_h

#include <iostream>
#include <stack>
#include <string>

#include "Agent.h"
#include "UCTNode.h"
#include "Reward.h"

const int TREE_POLICY_MAX_DEPTH = 100;
const int DEFAULT_POLICY_MAX_DEPTH = 100;
const int UCTSEARCH_BUDGET = 150;

class UCTAgent : public Agent {
public:
  UCTAgent(std::default_random_engine& r) : rng(r){};
  UCTAgent(std::default_random_engine& r, float c) : rng(r), cp(c){};
  void new_game(const State&);
  Action get_action(const State&, const Action&);
  std::string get_description();
  ~UCTAgent(){};
  void print_stats();
  
private:
  void update_root(const Action&);
  std::stack<std::shared_ptr<UCTNode>> uct_tree_policy();
  float default_policy(State);
  void backup(std::stack<std::shared_ptr<UCTNode>>, float);
  Action UCTSearch();
  
  std::default_random_engine& rng;
  std::shared_ptr<UCTNode> root;
  int node_count = 0;
  float branching_factor = 0;
  float cp = 0.7071;
};

void UCTAgent::new_game(const State& s){
  // (re-)initialize the tree
  // Must be called when a new game is started
  root = std::make_shared<UCTNode>(s);
  node_count = 0;
  branching_factor = 0;
}

void UCTAgent::update_root(const Action& a){
  // use a to update root
  if(a.card == NONE){
    return;
  }
  // find edge
  int k = 0;
  while((k < root->actions.size()) && !(root->actions[k] == a)){
    ++k;
  }
  if(k == root->actions.size()){
    // error: edge not found.
  }
  
  // update root
  if(root->children[k]){  // child is already expanded
    root = std::move(root->children[k]);
  } else {                // start from scratch
    root = std::make_shared<UCTNode>(next_state(root->state, a));
  }
}

std::stack<std::shared_ptr<UCTNode>> UCTAgent::uct_tree_policy(){
  // UCT TREE POLICY
  //
  // Side effects: Unless it reaches a terminal state, calls expand() on a descendent of v
  //
  // Returns a stack recording the path taken.
  
  int d = 0;
  std::stack<std::shared_ptr<UCTNode>> path;
  path.push(root);
  
  while(path.top()->r == 0 && d < TREE_POLICY_MAX_DEPTH){
    if(path.top()->fully_expanded()){
      
      int k = path.top()->best_child(rng, cp);
      path.push(path.top()->children[k]);
    } else {
      // expand
      path.push(path.top()->children[path.top()->expand(rng)]);
      
      // update tree statistics
      node_count++;
      branching_factor = ((node_count - 1) * branching_factor + int(path.top()->actions.size())) / node_count;
      return path;
    }
    d++;
  }
  return path; // reached terminal state
}

inline float UCTAgent::default_policy(State s){
  // DEFAULT POLICY
  //
  // Plays out a random simulation and returns reward for s.player
  
  int turn = 0;
  float reward = get_reward(s);
  State n = s;
  
  while(reward == 0 && turn < DEFAULT_POLICY_MAX_DEPTH){
    std::vector<Action> actions = get_valid_actions(n);
    std::uniform_int_distribution<int> unif(0, int(actions.size()) - 1);
    n = next_state(n, actions[unif(rng)]);
    reward = get_reward(n);
    turn++;
  }
  if(s.player == n.player){
    return reward;
  } else {
    return -reward;
  }
}

void UCTAgent::backup(std::stack<std::shared_ptr<UCTNode>> path, float delta){
  // BACKUP
  //
  // Arguments: delta represents reward for player at v (initially a leaf)
  // Side effects: modifies data of anscetors of v
  
  while (!path.empty()) {
    path.top()->N = path.top()->N + 1;
    path.top()->Q = path.top()->Q + delta;
    path.pop();
    delta = -delta; // since 2-player, zero-sum game
  }
}

Action UCTAgent::UCTSearch(){
  // Upper Confidence bound for Trees (UCT) search algorithm
  
  // parallelize this
  // turn loop into while condition based on time/memory constraint
  
  for(int i = 0; i < UCTSEARCH_BUDGET; i++)
  {
    auto path = uct_tree_policy();
    float delta = default_policy(path.top()->state);
    backup(path, delta);
  }

  return root->actions[root->best_child(rng, 0)];
}

Action UCTAgent::get_action(const State& curr_s, const Action& prev_a){
  // Interface for UCTAgent
  // Computes and returns the best action according to UCT MCTS
  // Side-effects: updates root, calls UCTSearch (which has side-effects)

  update_root(prev_a);
  Action a = UCTSearch();
  update_root(a);
  
  return a;
}

std::string UCTAgent::get_description(){
  std::string description = "{\n    \"name\": \"UCTAgent\",\n    \"param\": {\n      \"cp\": " + std::to_string(cp) + "\n    }\n  }";
  return description;
}

void UCTAgent::print_stats(){
  // Total statistics
  // Prints statistics for the historical tree
  std::cout << "Total tree size: " << node_count << std::endl;
  std::cout << "Mean branching factor: " << branching_factor << std::endl;
  
  // Todo
  // Current statistics
  // Compute statistics for the current tree
  
}

#endif /* UCTAgent_h */
