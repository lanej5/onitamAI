//
//  Player.h
//
//  Created by Jeremy Lane
//

#ifndef Player_h
#define Player_h

enum Player { RED = 0, BLUE };

inline Player next_player(const Player& p){
  return Player(1 - p);
}

#endif /* Player_h */
