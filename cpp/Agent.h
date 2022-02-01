//
//  Agent.h
//
//  Created by Jeremy Lane.
//

#ifndef Agent_h
#define Agent_h

#include <string>

#include "State.h"
#include "Action.h"


class Agent {
public:
  virtual void new_game(const State&) = 0;
  virtual Action get_action(const State&, const Action&) = 0;
  virtual std::string get_description() = 0;
};


#endif /* Agent_h */
