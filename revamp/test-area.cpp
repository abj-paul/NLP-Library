#include "NonWord.h"
int main(){
  abj::String word("abrevat");
  
  abj::NonWord nonWord;
  abj::Stemmer stemmer(word);

  abj::String stem = stemmer.get_stem();
  printf("The stemmed word is=%s\n",stem.get_raw_data());
  printf("Size=%d\n",stem.size());
  
  abj::Vector<abj::Candidate>v = nonWord.generate_candidate_set(stem);

  printf("Size=%d\n",v.size());
  //for(int i=0; i<v.size(); i++) v[i].print();
  return 0;
}
