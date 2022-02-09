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
#include "Onitama.h"

class Logger{
public:
  virtual void log(const Onitama::State&, const Onitama::State&, const int&) = 0;
};

class NoLogger : public Logger {
// this logger does nothing
public:
  NoLogger(const std::string&, const std::string&){};
  void log(const Onitama::State&, const Onitama::State&, const int&){};
};

class CSVLogger : public Logger {
// this logger logs results to a csv
public:
  CSVLogger(const std::string&, const std::string&);
  void log(const Onitama::State&, const Onitama::State&, const int&);
private:
  std::ofstream csvfile;
};

CSVLogger::CSVLogger(const std::string& red_agent, const std::string& blue_agent){
  // generate filename from timestamp
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "log-%d-%m-%Y-%H-%M-%S");
  auto filename = oss.str();
  
  // write metadata to file
  std::ofstream datfile;
  datfile.open(filename + ".json");
  datfile << "{\n  \"red\": " << red_agent << ",\n  \"blue\": " << blue_agent << "\n}";
  datfile.close();
  
  // open csv file
  csvfile.open (filename + ".csv");
  csvfile << "card_0,card_1,card_2,card_3,card_4, start_colour, result, red_pawn_count, blue_pawn_count, num_turns\n";
  
}

void CSVLogger::log(const Onitama::State& start_state, const Onitama::State& end_state, const int& num_turns){
  for(int i = 0; i < 5; i++){
    csvfile << start_state.get_card(i).to_ulong() << ",";
  }
  csvfile << start_state.get_player() << ",";
  csvfile << end_state.get_result() << ",";
  csvfile << end_state.red_pawn_count() << ",";
  csvfile << end_state.blue_pawn_count() << ",";
  csvfile << num_turns << "\n";
}

#endif /* Logger_h */
