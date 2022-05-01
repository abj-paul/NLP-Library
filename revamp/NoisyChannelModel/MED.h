#include<iostream>
#include<string>
#include<vector>


#ifndef _MED_H_
#define _MED_H_

#define DELETION_DOWN_ARROW 1
#define INSERTION_RIGHT_ARROW 2
#define SAME_CHARACTER_DIAGONAL_ARROW 3
#define SUBSTITUTION_DIAGONAL_ARROW 4
#define TRANSPOSITION_ARROW 5
#define NO_OPERATION 6

#define MAX_WORD_SIZE 30

class DefineNoisyChannel;

class MED {
 private:
  void print_med_direction(int direction_value);
  friend void addToMatrix(MED, DefineNoisyChannel);
 public:
  const std::string STRING_START="@";
  const std::string STRING_END="[";
  int direction[MAX_WORD_SIZE][MAX_WORD_SIZE];
  int m_distance[MAX_WORD_SIZE][MAX_WORD_SIZE];
  std::vector<int> backtrack_path;
  std::string typo;
  std::string correction;

  void backtracking(int i, int j);
  void print_direction();

  MED(std::string correction, std::string typo); //(newWord, mainWord)
  void domerau_levensthein_edit_distance();

  static void test_function();
};


#endif
