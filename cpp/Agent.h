//
//  Agent.h
//
//  Created by Jeremy Lane.
//

#ifndef Agent_h
#define Agent_h

#include <string>

#include "Onitama.h"
  
class Agent {
public:
  virtual void new_game(const Onitama::State&) = 0;
  virtual Onitama::Action get_action(const Onitama::State&, const Onitama::Action&) = 0;
  virtual std::string get_description() = 0;
};

#endif /* Agent_h */
