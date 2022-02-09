//
//  test_agent.cpp
//
//  Created by Jeremy Lane
//

#include "RandomAgent.h"
#include "MinimaxAgent.h"
#include "UCTAgent.h"
#include "Logger.h"
#include "Gym.h"


int main(){
  
  int seed = 2;
  std::default_random_engine rng(seed);
  
  RandomAgent p1(rng);
  UCTAgent p2(rng);
  MinimaxAgent p3(rng, 5);
  
  CSVLogger l1(p1.get_description(), p2.get_description());
  Gym g1(p1, p2, rng, l1);
  g1.pit(10);
  
  CSVLogger l2(p1.get_description(), p3.get_description());
  Gym g2(p1, p3, rng, l2);
  g2.pit(10);
  
  CSVLogger l3(p2.get_description(), p3.get_description());
  Gym g3(p2, p3, rng, l3);
  g3.pit(20);
  
}
