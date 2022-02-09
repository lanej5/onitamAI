//
//  Utils.h
//
//  Created by Jeremy Lane.
//

#ifndef Utils_h
#define Utils_h

#include <iostream>
#include <bitset>
#include <array>

namespace Utils
{
  inline void rotate(std::bitset<25>& b){
    // rotate board by reversing bitsets
    for(int i = 0; i < 12; i++){
      std::swap(b[i], b[24-i]);
    }
  }
  
  inline void display_board(const std::array<std::bitset<25>, 9>& board){
    // print board to terminal
    std::cout << " Board        Red player cards          Blue player cards         Side card  " << std::endl;
    std::cout << " +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+" << std::endl;
    for(int i = 0; i < 5; i++){
      
      std::cout << 4-i << "|";
      
      for(int j = 0; j < 5; j++){
        int bit = 5 * (4 - i) + j;
        if(board[0].test(bit)){
          std::cout << "R|";
        } else if(board[2].test(bit)) {
          std::cout << "r|";
        } else if(board[1].test(bit)) {
          std::cout << "B|";
        } else if(board[3].test(bit)) {
          std::cout << "b|";
        } else {
          std::cout << " |";
        }
      }
      
      std::cout << "  |";
      
      for(int j = 0; j < 5; j++){
        int bit = 5 * (4 - i) + j;
        if(board[4].test(bit)){
          std::cout << "x|";
        } else {
          std::cout << " |";
        }
      }
      
      std::cout << "  |";
      
      for(int j = 0; j < 5; j++){
        int bit = 5 * (4 - i) + j;
        if(board[5].test(bit)){
          std::cout << "x|";
        } else {
          std::cout << " |";
        }
      }
      
      std::cout << "  |";
      
      for(int j = 0; j < 5; j++){
        int bit = 5*(4-i)+j;
        if(board[6].test(bit)){
          std::cout << "x|";
        } else {
          std::cout << " |";
        }
      }
      
      std::cout << "  |";
      
      for(int j = 0; j < 5; j++){
        int bit = 5*(4-i)+j;
        if(board[7].test(bit)){
          std::cout << "x|";
        } else {
          std::cout << " |";
        }
      }
      
      std::cout << "  |";
      
      for(int j = 0; j < 5; j++){
        int bit = 5*(4-i)+j;
        if(board[8].test(bit)){
          std::cout << "x|";
        } else {
          std::cout << " |";
        }
      }
      
      std::cout << std::endl;
      std::cout << " +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+  +-+-+-+-+-+" << std::endl;
    }
    std::cout << "  0 1 2 3 4"<< std::endl;
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
}

#endif /* Utils_h */
