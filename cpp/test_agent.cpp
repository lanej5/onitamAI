//
//  test_agent.cpp
//
//  Created by Jeremy Lane
//

#include "Gym.h"
#include "RandomAgent.h"
#include "UCTAgent.h"

using namespace std;

int main(){
  
  int seed = 1;
  std::default_random_engine rng(seed);
  
  RandomAgent p1(rng);
  UCTAgent p2(rng);
  
  Gym g(p1, p2, rng);
  
  g.pit(5);
  
}
