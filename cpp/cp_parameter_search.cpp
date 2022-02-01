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
  
  RandomAgent p0(rng);
  UCTAgent p1(rng, 4);
  UCTAgent p2(rng, 6);
  UCTAgent p3(rng, 10);
  
  Gym g1(p0, p1, rng);
  Gym g2(p0, p2, rng);
  Gym g3(p0, p3, rng);
  
  g1.pit(10);
  g2.pit(10);
  g3.pit(10);
  
}
