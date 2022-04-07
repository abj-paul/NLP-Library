
#include "Candidate.h"
using namespace abj;

Candidate::Candidate(abj::String str, int med, abj::Vector<int> backtrack_path){
  this->str.initialize(str.get_raw_data());
  this->minimum_edit_distance=med;
  this->backtrack_path=backtrack_path;
}

abj::String Candidate::get_string(){
  return this->str;
}

int Candidate::get_med(){
  return this->minimum_edit_distance;
}

abj::Vector<int> Candidate::get_backtrack_path(){
  return this->backtrack_path;
}
void Candidate::print_med_direction(int direction_Value){
      if(direction_Value==INSERTION_RIGHT_ARROW) printf("<- ");
      else if(direction_Value==DELETION_DOWN_ARROW) printf("DW ");
      else if(direction_Value==SAME_CHARACTER_DIAGONAL_ARROW) printf("SM ");
      else if(direction_Value==SUBSTITUTION_DIAGONAL_ARROW) printf("^| ");
      else if(direction_Value==TRANSPOSITION_ARROW) printf("TP ");
      else if(direction_Value==NO_OPERATION) printf("NA ");
}

void Candidate::print(){
  printf("Candidate: %s\n",this->str.get_raw_data());
  printf("MED=%d\n",this->minimum_edit_distance);
  // for(int i=0; i<backtrack_path.size(); i++)print_med_direction(backtrack_path[i]);
  printf("\n");
}
