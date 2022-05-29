#include "Continuation.h"
#include "Bigram.h"
#include "Stemmer.h"

int abj::Continuation::getCount(const abj::String& targetStem, int NGram, std::vector<abj::String>& stemList){
  abj::Set set;
  set.defineNGram(NGram);

  for(int i=0; i<stemList.size(); i++){
    stemList[i].capitalize();
    if(stemList[i].equals(targetStem)){
      std::vector<abj::String> NGram_packet;
      int back_index = i;
      while(back_index>=0 && back_index> i-NGram){
	NGram_packet.push_back(stemList[back_index]);
	back_index--;
      }
      if(NGram_packet.size()==NGram){
	abj::Continuation::reverseVector(NGram_packet);
	set.insert(NGram_packet);
      }
    }
  }
  set.print();
  return set.size();
}

int abj::Continuation::wordsThatFollow(const abj::String& targetStem,int NGram, const std::vector<abj::String>& stemList){ // Strings that starts with Target
  abj::Set set;
  set.defineNGram(NGram);

  for(int i=0; i<stemList.size(); i++){
    if(stemList[i].equals(targetStem)){
      std::vector<abj::String> NGram_packet;
      int forward_index = i;
      while(forward_index<stemList.size() && forward_index < i+NGram){
	NGram_packet.push_back(stemList[forward_index]);
	forward_index--;
      }
      if(NGram_packet.size()==NGram){
	set.insert(NGram_packet);
      }
    }
  }
  set.print(*new abj::String("debug_follower_contiuation.txt"));
  return set.size();
 
}

std::vector<abj::String> abj::Continuation::reverseVector(std::vector<abj::String>& data){
  std::reverse(data.begin(), data.end());
  return data;
}

int abj::Continuation::getNGramSize(std::vector<abj::String>& stemList, int nGram){
  abj::Set set;
  for(int i=0; i<stemList.size()-nGram+1; i++){
    std::vector<abj::String> nGram_packet;
    for(int j=0; j<nGram; j++){
      nGram_packet.push_back(stemList[i+j]);
    }

    set.insert(nGram_packet);
  } 
  return set.size();
}

void abj::Continuation::test_function(){
  abj::Bigram bigram;
  bigram.preprocess_corpus();
  
  abj::Stemmer stemmer(*new abj::String("paragraph"));
  abj::String target = stemmer.get_stem();
  target.capitalize();
  std::cout<<"Continuation Count="<<abj::Continuation::getCount(target,_BIGRAM_, bigram.getStemList())<<std::endl;
  std::cout<<"Follower Count="<<abj::Continuation::wordsThatFollow(target, _BIGRAM_, bigram.getStemList())<<std::endl;
}
