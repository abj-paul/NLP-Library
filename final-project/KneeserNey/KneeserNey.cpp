#include "KneeserNey.h"
#include<algorithm>

abj::KneeserNey::KneeserNey(int nGram, const abj::String& text, const std::vector<abj::String>& corpusStemList){
  this->highestNGramValue = nGram;
  this->textStemList = abj::PrecomputeNGram::getStemList(text);
  this->corpusStemList = corpusStemList;
  this->text = text;
}

double abj::KneeserNey::kneeserNey(int nGram, int stemIndex){
  double firstPart = 0;
  double lambdaPart = 0;
  double p_continuation = 0;
  std::vector<abj::String> previous_packet;
  std::vector<abj::String> total_packet;
  for(int a=0; a<nGram; a++) total_packet.push_back(this->textStemList[stemIndex+a]); 
  for(int a=0; a<nGram-1; a++) previous_packet.push_back(this->textStemList[stemIndex+a]); 
  
  if(nGram!=highestNGramValue){
    firstPart = std::max((double)this->getSuffixCount(nGram, total_packet)-d_value,0.0)/(double)this->getSuffixCount(nGram-1, previous_packet);
  }else{
    abj::NGram ng(nGram, "./Resources/100_lines.txt");
    firstPart = ng.probablity_sentence(text);
  }

  lambdaPart = (d_value/(double)this->getSuffixCount(nGram-1, previous_packet))  * (double)getPrefixCount(nGram-1, previous_packet);

  if(nGram==2){
    abj::NGram ng(2, "./Resources/100_lines.txt");
    int _BIGRAM_SIZE_ = ng.getNGramSize();
    p_continuation = (double)this->getSuffixCount(nGram-1, previous_packet)/(double)_BIGRAM_SIZE_;
  }
  else p_continuation = kneeserNey(nGram-1, stemIndex);
    
  printf("%d ==> %lf + %lf * %lf\n",nGram, firstPart, lambdaPart, p_continuation);
  return std::log(firstPart + lambdaPart*p_continuation);
}


double abj::KneeserNey::kneeserNey_with_delta(int nGram, int stemIndex){
  double firstPart = 0;
  double lambdaPart = 0;
  double p_continuation = 0;

  double bigDelta = 1;
  double smallDelta = 0.0001;
  std::vector<abj::String> previous_packet;
  std::vector<abj::String> total_packet;
  for(int a=0; a<nGram; a++) total_packet.push_back(this->textStemList[stemIndex+a]); 
  for(int a=0; a<nGram-1; a++) previous_packet.push_back(this->textStemList[stemIndex+a]); 
    
    
  if(nGram!=highestNGramValue){
    firstPart = std::max((double)this->getSuffixCount(nGram, total_packet)-d_value,0.0+smallDelta)/((double)this->getSuffixCount(nGram-1, previous_packet)+bigDelta);
  }else{
    abj::NGram ng(nGram, "./Resources/100_lines.txt");
    firstPart = ng.probablity_sentence(text)+ smallDelta/10000;
  }


  lambdaPart = (d_value/((double)this->getSuffixCount(nGram-1, previous_packet)+bigDelta))  * ((double)getPrefixCount(nGram-1, previous_packet)+smallDelta);

  if(nGram==2){
    abj::NGram ng(2, "./Resources/100_lines.txt");
    int _BIGRAM_SIZE_ = ng.getNGramSize();
    p_continuation = (double)(this->getSuffixCount(nGram-1, previous_packet)+smallDelta)/(double)_BIGRAM_SIZE_;
  }
  else p_continuation = kneeserNey_with_delta(nGram-1, stemIndex);

  printf("%d ==> %lf + %lf * %lf\n",nGram, firstPart, lambdaPart, p_continuation);
  
  return firstPart + lambdaPart*p_continuation;
}



int abj::KneeserNey::getSuffixCount(int ngram, const std::vector<abj::String>& ngram_packet){
  abj::Set<std::vector<abj::String>> suffix_set;

  for(int i=0; i<=this->corpusStemList.size()-ngram; i++){
    std::vector<abj::String> corpus_ngram_packet;
    int j;
    for(j=0; j<ngram; j++) corpus_ngram_packet.push_back(this->corpusStemList[i+j]);
    if(ngram_packet == corpus_ngram_packet){
      corpus_ngram_packet.push_back(this->corpusStemList[i+j]); // push the next word as well, for finding different novel continuation types
      suffix_set.insert(corpus_ngram_packet);
    }
  }

  // printf("Suffix Continuation: \n");
  // suffix_set.print();
  return suffix_set.size();
}


int abj::KneeserNey::getPrefixCount(int ngram, const std::vector<abj::String>& ngram_packet){
  abj::Set<std::vector<abj::String>> prefix_set;
  for(int i=1; i<=this->corpusStemList.size()-ngram; i++){
    std::vector<abj::String> corpus_ngram_packet;
    int j;
    for(j=0; j<ngram; j++) corpus_ngram_packet.push_back(this->corpusStemList[i+j]);
    if(ngram_packet==corpus_ngram_packet){
      corpus_ngram_packet.push_back(this->corpusStemList[i-1]); //pushing back at wrong place, but oh well, we only need that to differ strings and our code does that.
      prefix_set.insert(corpus_ngram_packet);
    }
  }

  // printf("Prefix Continuation: \n");
  // prefix_set.print();
  return prefix_set.size();
}


void abj::KneeserNey::test_function(){
  abj::KneeserNey kn(4, *new abj::String("Lord of the rings"), abj::PrecomputeNGram::getStemList(abj::PrecomputeNGram::getFileData(*new abj::String("./Resources/100_lines.txt"))));
  std::cout<<kn.kneeserNey_with_delta(4, 0)<<std::endl;

  // std::vector<abj::String> bigram_packet;
  // bigram_packet.push_back((*new abj::Stemmer(*new abj::String("paragraph"))).get_stem());
  // bigram_packet.push_back((*new abj::Stemmer(*new abj::String("is"))).get_stem());
  
  // std::cout<<kn.getPrefixCount(3-1, bigram_packet)<<"\n";
  // std::cout<<kn.getSuffixCount(3-1, bigram_packet)<<"\n";
  // // std::cout<<kn.kneeserNey(4, 0)<<std::endl;
}
