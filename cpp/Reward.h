//
//  Reward.h
//
//  Created by Jeremy Lane.
//

#ifndef Reward_h
#define Reward_h

#include "State.h"

inline float get_reward(const State& s, const float gate_reward = 1, const float master_reward = 0.5){
  switch(get_result(s)){
    case BLUE_GATE_TAKEN:
      return gate_reward * (1 - 2 * s.player);
    case RED_GATE_TAKEN:
      return gate_reward * (2 * s.player - 1);
    case BLUE_MASTER_TAKEN:
      return master_reward * (1 - 2 * s.player);
    case RED_MASTER_TAKEN:
      return master_reward * (2 * s.player - 1);
    case NO_RESULT:
      return 0;
  }
}

#endif /* Reward_h */
