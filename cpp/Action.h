//
//  Action.h
//
//  Created by Jeremy Lane.
//

#ifndef Action_h
#define Action_h

#include <list>
#include "State.h"

// PASS indicates a player is passing (only state.player is changed)
// NONE indicates a null move (no effect)
enum Card { CARD_0 = 0, CARD_1, PASS, NONE };

struct Action{
  Card card;
  int piece_bit;  // 0 - 24
  int move_bit;   // 0 - 24
};

inline bool operator==(const Action& a1, const Action& a2){
    return a1.card == a2.card && a1.piece_bit == a2.piece_bit && a1.move_bit == a2.move_bit;
}

inline std::vector<Action> get_valid_actions(const State& s){
  
  std::list<Action> l = {};
  
  // bitboard of current player pieces
  std::bitset<25> cur_pieces = s.board[0 + s.player] | s.board[2 + s.player];
  
  for(int piece_bit = 0; piece_bit < 25; piece_bit++){
    if(cur_pieces.test(piece_bit)){
      for(int move_bit = 0; move_bit < 25; move_bit++){
        if(s.player == RED){
          
          int i = (piece_bit / 5) + (move_bit / 5);
          int j = (piece_bit % 5) + (move_bit % 5);
          
          if(2 <= i && i < 7 && 2 <= j && j < 7 && !cur_pieces.test(piece_bit + move_bit - 12)){
            if(s.board[4].test(move_bit)){
              l.push_back(Action{CARD_0, piece_bit, move_bit});
            } else if(s.board[5].test(move_bit)){
              l.push_back(Action{CARD_1, piece_bit, move_bit});
            }
          }
          
        } else {
          int i = (piece_bit / 5) - (move_bit / 5);
          int j = (piece_bit % 5) - (move_bit % 5);
          
          if(-2 <= i && i < 3 && -2 <= j && j < 3 && !cur_pieces.test(piece_bit - move_bit + 12)){
            if(s.board[6].test(move_bit)){
              l.push_back(Action{CARD_0, piece_bit, move_bit});
            }
            if(s.board[7].test(move_bit)){
              l.push_back(Action{CARD_1, piece_bit, move_bit});
            }
          }
        }
      }
    }
  }
  if(l.empty()){
    return std::vector<Action>{Action{PASS, 0, 0}};
  } else {
    return std::vector<Action>{std::begin(l), std::end(l)};
  }
}

inline bool is_valid(const State& s, const Action& a){
  for(Action a_i : get_valid_actions(s)){
    if(a_i == a){
      return true;
    }
  }
  return false;
}

inline State next_state(State s, const Action& a){
  // assumes move is valid
  
  if(a.card == PASS){
    s.player = next_player(s.player);
    return s;
  } else if (a.card == NONE){
    return s;
  }
  
  int new_piece_bit;
  if(s.player == RED){
    new_piece_bit = a.piece_bit + a.move_bit - 12;
    
    // move current player piece
    if(s.board[2].test(a.piece_bit)){ // move pawn
      s.board[2].flip(a.piece_bit);
      s.board[2].flip(new_piece_bit);
      
    } else {                          // move master
      s.board[0].flip(a.piece_bit);
      s.board[0].flip(new_piece_bit);
    }
    
    // take opposing player piece
    s.board[3].set(new_piece_bit, 0);
    s.board[1].set(new_piece_bit, 0);

    // swap played card with side card
    std::swap(s.board[8], s.board[4 + a.card]);
    
  } else {
    new_piece_bit = a.piece_bit - a.move_bit + 12;
    
    // move current player piece
    if(s.board[3].test(a.piece_bit)){ // move pawn
      s.board[3].flip(a.piece_bit);
      s.board[3].flip(new_piece_bit);
      
    } else {                          // move master
      s.board[1].flip(a.piece_bit);
      s.board[1].flip(new_piece_bit);
    }
    
    // take opposing player piece
    s.board[2].set(new_piece_bit, 0);
    s.board[0].set(new_piece_bit, 0);

    // swap played card with side card
    std::swap(s.board[8], s.board[6 + a.card]);
  }
  
  s.player = next_player(s.player);

  return s;
}

#endif /* Action_h */
