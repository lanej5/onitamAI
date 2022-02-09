//
//  Reward.h
//
//  Created by Jeremy Lane.
//

#ifndef Reward_h
#define Reward_h

#include "Onitama.h"

inline float get_reward(const Onitama::State& s, const float gate_reward = 1, const float master_reward = 0.5){
  switch(s.get_result()){
    case Onitama::BLUE_GATE_TAKEN:
      return gate_reward * (1 - 2 * s.get_player());
    case Onitama::RED_GATE_TAKEN:
      return gate_reward * (2 * s.get_player() - 1);
    case Onitama::BLUE_MASTER_TAKEN:
      return master_reward * (1 - 2 * s.get_player());
    case Onitama::RED_MASTER_TAKEN:
      return master_reward * (2 * s.get_player() - 1);
    case Onitama::NO_RESULT:
      return 0;
  }
}

#endif /* Reward_h */
