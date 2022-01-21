//
//  Reward.h
//
//  Created by Jeremy Lane.
//

#ifndef Reward_h
#define Reward_h

#include "State.h"

const float GATE_CAPTURE_REWARD = 1;
const float MASTER_CAPTURE_REWARD = .5;

inline float get_reward(const State& s){
  switch(get_result(s)){
    case BLUE_GATE_TAKEN:
      return GATE_CAPTURE_REWARD * (1 - 2 * s.player);
    case RED_GATE_TAKEN:
      return GATE_CAPTURE_REWARD * (2 * s.player - 1);
    case BLUE_MASTER_TAKEN:
      return MASTER_CAPTURE_REWARD * (1 - 2 * s.player);
    case RED_MASTER_TAKEN:
      return MASTER_CAPTURE_REWARD * (2 * s.player - 1);
    case NO_RESULT:
      return 0;
  }
}

#endif /* Reward_h */
