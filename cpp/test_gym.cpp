//
//  test_gym.cpp
//  Node
//
//  Created by Jeremy Lane on 2022-01-19.
//

#include "Gym.h"
#include "RandomAgent.h"

using namespace std;

int main(){
  int seed = 1;
  std::default_random_engine rng(seed);
  
  RandomAgent p1(rng);
  RandomAgent p2(rng);
  
  Gym g(p1, p2, rng);
  
  g.pit(3);
  
}

