#include "NonWord.h"
int main(){

  abj::NonWord nonWord;
  abj::Vector<abj::Candidate>v = nonWord.generate_candidate_set("book");

  for(int i=0; i<v.size(); i++) v[i].print();
  return 0;
}
