//
//  test_logger.cpp
//
//  Created by Jeremy Lane
//

#include <random>

#include "Logger.h"
#include "RandomAgent.h"
#include "Gym.h"

using namespace std;

int main(){

  int seed = 1;
  std::default_random_engine rng(seed);

  RandomAgent p1(rng);
  RandomAgent p2(rng);
  CSVLogger logger(p1.get_description(), p2.get_description());
  Gym g(p1, p2, rng, logger);

  g.pit(1000);

}
