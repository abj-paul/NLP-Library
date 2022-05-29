
#ifndef _CANDIDATE_H_
#define _CANDIDATE_H_

#include "../Data-Structures/lib_string.h"

namespace abj{
class Candidate{
 private:
  abj::String word;
  int MED;
  double languageProbablity;
  double noisyChannelProbablity;
 public:
  ~Candidate(){
    // this->word.~String();
  }
  Candidate(const abj::String& word){
    this->word = word;
    this->languageProbablity = 0;
    this->noisyChannelProbablity = 0;
    this->MED = 0;
  }
  Candidate(const abj::String& word, int MED){
    this->word = word;
    this->MED = MED;
    this->languageProbablity = 0;
    this->noisyChannelProbablity = 0;
  }
  void setLanguageProbablity(double probablity){
    this->languageProbablity = probablity;
  }
  void setNoisyChannelProbablity(double probablity){
    this->noisyChannelProbablity = probablity;
  }
  double getLanguageProbablity(){
    return this->languageProbablity;
  }
  double getNoisyChannelProbablity(){
    return this->noisyChannelProbablity;
  }
  void print(FILE* fptr){
    fprintf(fptr, "%lf = (%lf,%lf) | \"%s\" | MED = %d \n", this->getTotalProbablity(), this->languageProbablity, this->noisyChannelProbablity, this->word.get_raw_data(), this->MED);
    // fprintf(fptr, "\"%s\" | MED = %d | (%lf,%lf)=%lf\n",this->word.get_raw_data(), this->MED, this->languageProbablity, this->noisyChannelProbablity, this->getTotalProbablity());
  }

  double getTotalProbablity(){
    return this->noisyChannelProbablity + this->languageProbablity;
  }

  abj::String& getWord(){
    return this->word;
  }
};
}

  #endif
