#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <sstream>

#ifndef _DEFINE_NOISY_CHANNEL_H
#define _DEFINE_NOISY_CHANNEL_H

#include "MED.h"

#define RECORD std::pair<std::string,std::vector<std::string>>
class DefineNoisyChannel {
 private:
  const std::string filename = "spell-errors.txt";
  const std::string debugFileName = "DEBUG_database_spelling_errors.txt";
  const int number_of_alphabets = 26;
  std::vector<RECORD>database;

  void load_file();
  std::vector<std::string> get_tokens(std::string line, char separator);
  void split_and_store(std::string line);
  void printDatabase(); // debug purpose

  void initialize_fields();
  void handleMultipleOccurenceOfWord(std::vector<std::string>*spellingErrors);
  
  std::vector<std::vector<int>>insertion_confusion_matrix;
  std::vector<std::vector<int>>deletion_confusion_matrix;
  std::vector<std::vector<int>>substitution_confusion_matrix;
  std::vector<std::vector<int>>transposition_confusion_matrix;

  void initialize_confusion_matrices();
  void backtracking(int i, int j, int direction[][MAX_WORD_SIZE], std::string A, std::string B);
  friend void addToMatrix(MED, DefineNoisyChannel);
public:
  DefineNoisyChannel();
  void loadMatrices();
  void printMatrices();
};

#endif
