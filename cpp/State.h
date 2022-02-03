//
//  State.h
//
//  Created by Jeremy Lane
//
//  Establishes the logic and representation for Onitama states and actions.

#ifndef State_h
#define State_h

#include <random>
#include <bitset>
#include <array>

#include "OnitamaDeck.h"
#include "Player.h"

/*

 As with cards (cf. OnitamaDeck.h), board positions are represented by bitsets.

 Bit 5 * i + j corresponds to square (i,j).
 
 Rows of a card are indexed by i, columns by j.

 The bottom left square of a card is (0,0).
 
 Conveniently, the board has the same dimensions as cards.

*/

constexpr std::bitset<25> RED_GATE = 0b0000000000000000000000100; // starting position of red master
constexpr std::bitset<25> BLUE_GATE = 0b0010000000000000000000000;
constexpr std::bitset<25> RED_PAWN_START = 0b0000000000000000000011011;
constexpr std::bitset<25> BLUE_PAWN_START = 0b1101100000000000000000000;

enum Result { NO_RESULT = 0, BLUE_GATE_TAKEN, BLUE_MASTER_TAKEN, RED_GATE_TAKEN, RED_MASTER_TAKEN };

struct State{
/*
 Each State is represented by an array of 9 bitboards
 and the current player, i.e., the player whose turn it is.
   
 The meaning of each bitboard in the array is as follows:
   b[0] - RED master
   b[1] - BLUE master
   b[2] - RED pawns
   b[3] - BLUE pawns
   b[4] - RED first card
   b[5] - RED second card
   b[6] - BLUE first card
   b[7] - BLUE second card
   b[8] - side card
*/
  Player player;
  std::array<std::bitset<25>, 9> board;
};

inline bool operator==(const State& s1, const State& s2){
    return s1.player == s2.player && s1.board == s2.board;
}

inline State new_game(std::default_random_engine& rng){
  // generate random new game
  std::array<int, 16> deck_index = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  std::shuffle (deck_index.begin(), deck_index.end(), rng);
  
  std::array<std::bitset<25>, 9> s = {RED_GATE, BLUE_GATE, RED_PAWN_START, BLUE_PAWN_START, DECK[deck_index[0]], DECK[deck_index[1]], DECK[deck_index[2]], DECK[deck_index[3]], DECK[deck_index[4]]};
  
  // choose the player to go first (in the official game each card has a colour and it is the colour of the side card that determines this choice)
  std::uniform_int_distribution<int> uni(0, 1);
  
  return State{Player(uni(rng)), s};
}

inline State new_game(const int& seed){
  std::default_random_engine rng(seed);
  return new_game(rng);
}

inline State new_game(){
  std::random_device rd;
  return new_game(rd());
}

inline Result get_result(const State& s){

  if(s.board[0].test(22)){
    return BLUE_GATE_TAKEN;
  }
  
  if(s.board[1].test(2)){
    return RED_GATE_TAKEN;
  }

  if(!s.board[0].any()){
    return RED_MASTER_TAKEN;
  }
  
  if(!s.board[1].any()){
    return BLUE_MASTER_TAKEN;
  }
  
  return NO_RESULT;
}

#endif /* State_h */
