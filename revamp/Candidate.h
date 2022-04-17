
#include<iostream>

#ifndef _CANDIDATE_H_
#define _CANDIDATE_H_

#include "lib_string.h"
#include "lib_vector.h"

namespace abj{
#define DELETION_DOWN_ARROW 1
#define INSERTION_RIGHT_ARROW 2
#define SAME_CHARACTER_DIAGONAL_ARROW 3
#define SUBSTITUTION_DIAGONAL_ARROW 4
#define TRANSPOSITION_ARROW 5
#define NO_OPERATION 6

  class Candidate{
  private:
    abj::String str;
    int minimum_edit_distance;
    abj::Vector<int> backtrack_path;
    double probablity;

    
    void print_med_direction(int direction_Value);
  public:
    Candidate(abj::String str, int med, abj::Vector<int> backtrack_path);
    
    abj::String get_string();
    int get_med();
    abj::Vector<int> get_backtrack_path();

    void print();
  };
}

#endif
