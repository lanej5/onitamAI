//
//  Onitama.h
//
//  Created by Jeremy Lane
//

#ifndef Onitama_h
#define Onitama_h

#include <bitset>
#include <vector>
#include <array>
#include <list>
#include <random>
#include <cstdint>

#include "Utils.h"

namespace Onitama
{
  // when the game begins
  // the color of the side card
  // tells us who goes first
  constexpr std::array<std::bitset<25>, 16> Deck {
    // blue cards
    0b0000001010000000101000000, // monkey
    0b0000000010010000001000000, // eel
    0b0010000000000000010000000, // tiger
    0b0000000100000000101000000, // crane
    0b0000000100100010000000000, // crab
    0b0000001000100000001000000, // rabbit
    0b0000000010010100100000000, // goose
    0b0000000100010000010000000, // ox
    // red cards
    0b0000001000000100100000000, // cobra
    0b0000001010000000010000000, // mantis
    0b0000000010000010100000000, // frog
    0b0000000100000100010000000, // horse
    0b0000001000010100001000000, // rooster
    0b0000010001000000101000000, // dragon
    0b0000000100010100000000000, // boar
    0b0000001010010100000000000  // elephant
  };

  constexpr std::array<std::bitset<25>, 5> V_MASK {
    0b1111111111111110000000000,
    0b1111111111111111111100000,
    0b1111111111111111111111111,
    0b0000011111111111111111111,
    0b0000000000111111111111111
  };

  constexpr std::array<std::bitset<25>, 5> H_MASK {
    0b1110011100111001110011100,
    0b1111011110111101111011110,
    0b1111111111111111111111111,
    0b0111101111011110111101111,
    0b0011100111001110011100111
  };

  inline std::bitset<25> get_mask(int bit){
    return V_MASK[ bit / 5 ] & H_MASK[ bit % 5 ];
  }

  constexpr std::bitset<25> RED_GATE = 0b0000000000000000000000100;
  constexpr std::bitset<25> BLUE_GATE = 0b0010000000000000000000000;
  constexpr std::bitset<25> RED_PAWN_START = 0b0000000000000000000011011;
  constexpr std::bitset<25> BLUE_PAWN_START = 0b1101100000000000000000000;

  // representation of game results
  enum Result : std::uint8_t {
    NO_RESULT,
    BLUE_GATE_TAKEN,
    BLUE_MASTER_TAKEN,
    RED_GATE_TAKEN,
    RED_MASTER_TAKEN
  };

  // representation of current player
  enum Player : std::uint8_t {
    RED,
    BLUE
  };

  inline Player next_player(const Player& p){
    return Player(1 - p);
  }

  // representation of possible action types
  enum ActionType : std::uint8_t {
    CARD_0,
    CARD_1,
    PASS,
    NONE
  };

  enum PieceType : std::uint8_t {
    Master,
    Pawn
  };

  // representation of an action
  struct Action{
    ActionType action_type;
    PieceType piece_type;
    std::uint8_t piece_bit;
    std::uint8_t move_bit;
  };

  inline bool operator==(const Action& a1, const Action& a2){
    return ( a1.action_type == a2.action_type &&
             a1.piece_type == a2.piece_type &&
             a1.piece_bit == a2.piece_bit &&
             a1.move_bit == a2.move_bit
           );
  }

  class State{
  public:
    State(std::default_random_engine& rng);
    State(const State &s) : player{s.player}, board{s.board} {};
    int red_pawn_count() const { return int(board[2].count()); }
    int blue_pawn_count() const { return int(board[3].count()); }
    int red_master_bit() const { return __builtin_ctz((unsigned int) board[0].to_ulong()); }
    int blue_master_bit() const { return __builtin_ctz((unsigned int) board[1].to_ulong()); }
    Player get_player() const { return player; };
    Result get_result() const;
    std::bitset<25> get_card(int i) const { return board[4+i]; };
    std::vector<Action> get_valid_actions() const;
    State next_state(const Action&) const;
    bool is_valid(const Action& ) const;
    void display_board() const { Utils::display_board(board); }
    void display_card(int i) const { Utils::display_card(board[4 + i]); }
    void display_result() const;
    
  private:
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

  inline State::State(std::default_random_engine& rng){
    // generate random new game
    
    std::array<int, 16> deck_index = {
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
    };
    std::shuffle (deck_index.begin(), deck_index.end(), rng);
    
    board = {
      RED_GATE,
      BLUE_GATE,
      RED_PAWN_START,
      BLUE_PAWN_START,
      Deck[deck_index[0]],
      Deck[deck_index[1]],
      Deck[deck_index[2]],
      Deck[deck_index[3]],
      Deck[deck_index[4]]
    };
    player = Player(int(deck_index[4] >= 8));
    return;
  }

  inline Result State::get_result() const{
    if (board[0].test(22)){ return BLUE_GATE_TAKEN; }
    else if (board[1].test(2)){ return RED_GATE_TAKEN; }
    else if (board[0].none()){ return RED_MASTER_TAKEN; }
    else if (board[1].none()){ return BLUE_MASTER_TAKEN; }
    return NO_RESULT;
  }

  inline std::vector<Action> State::get_valid_actions() const {
    // currently uses a homemade implementation of the gcc builtin _Find_next
    // because I'm compiling with clang for now
    
    std::list<Action> l = {};
    std::bitset<25> cur_pieces = board[0 + player] | board[2 + player];
    if(player == BLUE){ Utils::rotate(cur_pieces); }
      
    // generate master moves
    int piece_bit = __builtin_ctz((unsigned int)board[player].to_ulong());
    // if RED get mask for piece_bit.
    // if BLUE get mask for 24 - piece_bit
    // if RED, delete bits from curr_pieces left shifted by 12 - piece_bit
    // if BLUE, delete bits from curr_pieces left shifted by piece_bit - 12
    std::bitset<25> mask = get_mask(piece_bit + player * (24 - 2 * piece_bit)) &
                           ~(cur_pieces << (12 - (piece_bit + player * (24 - 2 * piece_bit))));
    
    for (int card = 0; card < 2; ++card){
      unsigned int moves = (unsigned int)(mask & board[4 + 2 * player + card]).to_ulong();
      int move_bit = __builtin_ffs(moves) - 1;
      while(move_bit > -1){
        l.push_back(Action{
          ActionType(card),
          Master,
          (uint8_t) piece_bit,
          (uint8_t) move_bit
        });
        moves -= (1 << move_bit);
        move_bit = __builtin_ffs(moves) - 1;
      }
    }
    
    // generate pawn moves
    unsigned int pawns = (unsigned int) board[2 + player].to_ulong();
    piece_bit = __builtin_ffs(pawns) - 1;
    while (piece_bit > -1) {
      mask = get_mask(piece_bit + player * (24 - 2 * piece_bit)) &
             ~(cur_pieces << ((1 - player) * (12 - piece_bit) + player * (piece_bit - 12)));
      for (int card = 0; card < 2; ++card){
        unsigned int moves = (unsigned int)(mask & board[4 + 2 * player + card]).to_ulong();
        int move_bit = __builtin_ffs(moves) - 1;
        while(move_bit > -1){
          l.push_back(Action{
            ActionType(card),
            Pawn,
            (uint8_t) piece_bit,
            (uint8_t) move_bit
          });
          moves -= (1 << move_bit);
          move_bit = __builtin_ffs(moves) - 1;
        }
      }
      pawns -= (1 << piece_bit);
      piece_bit = __builtin_ffs(pawns) - 1;
    }
  
    if(l.empty()){
      return std::vector<Action>{Action{PASS, Master, 0, 0}};
    } else {
      return std::vector<Action>{std::begin(l), std::end(l)};
    }
  }

  inline bool State::is_valid(const Action& a) const {
    // lazy implementation
    for(Action a_i : get_valid_actions()){
      if(a_i == a){
        return true;
      }
    }
    return false;
  }

  inline State State::next_state(const Action& a) const {
    // assumes move is valid
    
    State next(*this);
    
    switch(a.action_type){
      case NONE:
        return next;
      case PASS:
        next.player = next_player(player);
        return next;
      case CARD_0:
      case CARD_1:
        int new_piece_bit = a.piece_bit + (1 - player) * (a.move_bit - 12) + player * (12 - a.move_bit);
        
        // move current player piece
        next.board[player + 2 * a.piece_type].flip(a.piece_bit);
        next.board[player + 2 * a.piece_type].flip(new_piece_bit);

        // take opposing player piece
        next.board[(1 - player)].set(new_piece_bit, 0);
        next.board[(1 - player) + 2].set(new_piece_bit, 0);

        // swap played card with side card
        std::swap(next.board[8], next.board[4 + 2 * player + a.action_type]);
        
        next.player = next_player(next.player);

        return next;
    }
  }

  inline void State::display_result() const {
    Result result = get_result();
    switch(result){
      case BLUE_GATE_TAKEN:
        std::cout << "Blue gate taken. Red wins!" << std::endl;
        break;
      case RED_GATE_TAKEN:
        std::cout << "Red gate taken. Blue wins!" << std::endl;
        break;
      case BLUE_MASTER_TAKEN:
        std::cout << "Blue master taken. Red wins!" << std::endl;
        break;
      case RED_MASTER_TAKEN:
        std::cout << "Red master taken. Blue wins!" << std::endl;
        break;
      case NO_RESULT: break;
    }
  }

}

#endif /* Onitama_h */
