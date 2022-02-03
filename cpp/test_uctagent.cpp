//
//  test_uctagent.cpp
//
//  Created by Jeremy Lane
//

#include <random>

#include "Gym.h"
#include "RandomAgent.h"
#include "UCTAgent.h"
#include "MinimaxAgent.h"
#include "Logger.h"

using namespace std;

int main(){
  int seed = 1;
  std::default_random_engine rng(seed);
  
  MinimaxAgent p1(rng, 5);
  UCTAgent p2(rng, 0.707);
  CSVLogger logger(p1.get_description(), p2.get_description());
  Gym g(p1, p2, rng, logger);
  
  g.pit(100);
  
}

