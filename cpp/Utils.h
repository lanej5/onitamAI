//
//  Utils.h
//
//  Created by Jeremy Lane.
//

#ifndef Utils_h
#define Utils_h

#include <iostream>
#include "State.h"

std::array<std::bitset<25>, 9> rotate_board(std::array<std::bitset<25>, 9> b){
  // rotate board by reversing bitsets
  for(int i = 0; i < 12; i++){
    std::swap(b[0][i], b[0][24-i]);
    std::swap(b[1][i], b[1][24-i]);
    std::swap(b[2][i], b[2][24-i]);
    std::swap(b[3][i], b[3][24-i]);
  }
  return b;
}

inline void print_result(const State& s){
  Result result = get_result(s);
  
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

inline void display_board(const State& s){
  // print board to terminal
  std::cout << " Board        Red player cards          Blue player cards         Side card  " << std::endl;
  std::cout << " +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+" << std::endl;
  for(int i = 0; i < 5; i++){
    
    std::cout << 4-i << "|";
    
    for(int j = 0; j < 5; j++){
      int bit = 5 * (4 - i) + j;
      if(s.board[0].test(bit)){
        std::cout << "R|";
      } else if(s.board[2].test(bit)) {
        std::cout << "r|";
      } else if(s.board[1].test(bit)) {
        std::cout << "B|";
      } else if(s.board[3].test(bit)) {
        std::cout << "b|";
      } else {
        std::cout << " |";
      }
    }
    
    std::cout << "  |";
    
    for(int j = 0; j < 5; j++){
      int bit = 5 * (4 - i) + j;
      if(s.board[4].test(bit)){
        std::cout << "x|";
      } else {
        std::cout << " |";
      }
    }
    
    std::cout << "  |";
    
    for(int j = 0; j < 5; j++){
      int bit = 5 * (4 - i) + j;
      if(s.board[5].test(bit)){
        std::cout << "x|";
      } else {
        std::cout << " |";
      }
    }
    
    std::cout << "  |";
    
    for(int j = 0; j < 5; j++){
      int bit = 5*(4-i)+j;
      if(s.board[6].test(bit)){
        std::cout << "x|";
      } else {
        std::cout << " |";
      }
    }
    
    std::cout << "  |";
    
    for(int j = 0; j < 5; j++){
      int bit = 5*(4-i)+j;
      if(s.board[7].test(bit)){
        std::cout << "x|";
      } else {
        std::cout << " |";
      }
    }
    
    std::cout << "  |";
    
    for(int j = 0; j < 5; j++){
      int bit = 5*(4-i)+j;
      if(s.board[8].test(bit)){
        std::cout << "x|";
      } else {
        std::cout << " |";
      }
    }
    
    std::cout << std::endl;
    std::cout << " +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+" << std::endl;
  }
  std::cout << "  0 1 2 3 4"<< std::endl;
  print_result(s);
  std::cout << std::endl;
}

inline void display_card(const std::bitset<25>& c){
  // print board to terminal
  
  std::cout << " +-+-+-+-+-+"<< std::endl;
  for(int i = 0; i < 5; i++){
    std::cout << 4-i << "|";
    for(int j = 0; j < 5; j++){
      if(c.test(5 * (4 - i) + j)){
        std::cout << "x|";
      } else {
        std::cout << " |";
      }
    }
    std::cout << std::endl;
    std::cout << " +-+-+-+-+-+"<< std::endl;
  }
  std::cout << "  0 1 2 3 4"<< std::endl;
}

inline void display_board_indices(){
  // print board indexing
  
  std::cout << " +-+-+-+-+-+"<< std::endl;
  for(int i = 0; i < 5; i++){
    std::cout << 4-i << "|";
    for(int j = 0; j < 5; j++){
      int bit = 5 * (4 - i) + j;
      std::cout << bit << "|";
    }
    std::cout << std::endl;
    std::cout << " +-+-+-+-+-+"<< std::endl;
  }
  std::cout << "  0 1 2 3 4"<< std::endl;
}


#endif /* Utils_h */
