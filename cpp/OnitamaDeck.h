//
//  OnitamaDeck.h
//
//  Created by Jeremy Lane.
//
//  Defines deck of Onitama cards

#ifndef OnitamaDeck_h
#define OnitamaDeck_h

#include <bitset>
#include <array>
#include <map>

/*

 Move cards are represented by bitsets.

 Bit 5 * i + j corresponds to square (i,j).
 
 Rows of a card are indexed by i, columns by j.

 The bottom left square of a card is (0,0).

*/

//enum DECK {MONKEY,MANTIS,FROG,HORSE,CRANE,COBRA,CRAB,RABBIT,ROOSTR,GOOSE,OX,DRAGON,BOAR,ELEPHT,EEL,TIGER};
//
//std::map<DECK, std::bitset<25>> card_bitboard {
//  {MONKEY, std::bitset<25> {0b0000001010000000101000000}},
//  {MANTIS, std::bitset<25> {0b0000001010000000010000000}},
//  {FROG,   std::bitset<25> {0b0000000010000010100000000}},
//  {HORSE,  std::bitset<25> {0b0000000100000100010000000}},
//  {CRANE,  std::bitset<25> {0b0000000100000000101000000}},
//  {COBRA,  std::bitset<25> {0b0000001000000100100000000}},
//  {CRAB,   std::bitset<25> {0b0000000100100010000000000}},
//  {RABBIT, std::bitset<25> {0b0000000100000000101000000}},
//  {ROOSTR, std::bitset<25> {0b0000000100000000101000000}},
//  {GOOSE,  std::bitset<25> {0b0000000100000000101000000}},
//  {OX,     std::bitset<25> {0b0000000100000000101000000}},
//  {DRAGON, std::bitset<25> {0b0000000100000000101000000}},
//  {BOAR,   std::bitset<25> {0b0000000100000000101000000}},
//  {ELEPHT, std::bitset<25> {0b0000000100000000101000000}},
//  {EEL,    std::bitset<25> {0b0000000100000000101000000}},
//  {TIGER,  std::bitset<25> {0b0000000100000000101000000}}
//};

constexpr std::bitset<25> MONKEY = 0b0000001010000000101000000;
constexpr std::bitset<25> MANTIS = 0b0000001010000000010000000;
constexpr std::bitset<25> FROG   = 0b0000000010000010100000000;
constexpr std::bitset<25> HORSE  = 0b0000000100000100010000000;
constexpr std::bitset<25> CRANE  = 0b0000000100000000101000000;
constexpr std::bitset<25> COBRA  = 0b0000001000000100100000000;
constexpr std::bitset<25> CRAB   = 0b0000000100100010000000000;
constexpr std::bitset<25> RABBIT = 0b0000001000100000001000000;
constexpr std::bitset<25> ROOSTR = 0b0000001000010100001000000;
constexpr std::bitset<25> GOOSE  = 0b0000000010010100100000000;
constexpr std::bitset<25> OX     = 0b0000000100010000010000000;
constexpr std::bitset<25> DRAGON = 0b0000010001000000101000000;
constexpr std::bitset<25> BOAR   = 0b0000000100010100000000000;
constexpr std::bitset<25> ELEPHT = 0b0000001010010100000000000;
constexpr std::bitset<25> EEL    = 0b0000000010010000001000000;
constexpr std::bitset<25> TIGER  = 0b0010000000000000010000000;

const std::array<std::bitset<25>, 16> DECK = {MONKEY,MANTIS,FROG,HORSE,CRANE,COBRA,CRAB,RABBIT,ROOSTR,GOOSE,OX,DRAGON,BOAR,ELEPHT,EEL,TIGER};

#endif /* OnitamaDeck_h */
