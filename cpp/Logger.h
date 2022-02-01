//
//  Logger.h
//
//  Created by Jeremy Lane
//

#ifndef Logger_h
#define Logger_h

#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>

#include "State.h"
#include "Action.h"

class Logger{
public:
  virtual void log(const State&, const State&, const Result&, const int&) = 0;
};

class NoLogger : public Logger {
public:
  NoLogger(const std::string&, const std::string&){};
  void log(const State&, const State&, const Result&, const int&){};
};

class CSVLogger : public Logger {
public:
  CSVLogger(const std::string&, const std::string&);
  void log(const State&, const State&, const Result&, const int&);
private:
  std::ofstream csvfile;
};

CSVLogger::CSVLogger(const std::string& red_agent, const std::string& blue_agent){
  
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "log-%d-%m-%Y-%H-%M-%S");
  auto filename = oss.str();
  
  std::ofstream datfile;
  datfile.open(filename + ".json");
  datfile << "{\n  \"red\": " << red_agent << ",\n  \"blue\": " << blue_agent << "\n}";
  datfile.close();
  
  csvfile.open (filename + ".csv");
  csvfile << "card_0, card_1, card_2, card_3, card_4, start_colour, result, red_pawn_count, blue_pawn_count, num_turns\n";
  
}

void CSVLogger::log(const State& start_state, const State& end_state, const Result& result, const int& num_turns){
  for(int i = 4; i < 9; i++){
    csvfile << start_state.board.at(i).to_ulong() << ", ";
  }
  csvfile << start_state.player << ", ";
  csvfile << result << ", ";
  int red_pawn_count = 0;
  int blue_pawn_count = 0;
  for(int i = 0; i < 25; i++){
    if(end_state.board[2].test(i)){
      red_pawn_count++;
    }
    if(end_state.board[3].test(i)){
      blue_pawn_count++;
    }
  }
  csvfile << red_pawn_count << ", ";
  csvfile << blue_pawn_count << ", ";
  csvfile << num_turns << "\n";
  
}

#endif /* Logger_h */
