#include "NGram.h"

abj::NGram::NGram(int ngram, const abj::String& corpusFileName){
  this->ngram = ngram;
  this->corpusFileName = corpusFileName;
  abj::PrecomputeNGram precomputengram(ngram, corpusFileName);
  precomputengram.build_ngram();
  this->ngram_packet_set = precomputengram.get_ngram_packet_set();

  abj::PrecomputeNGram precomputengram_2(ngram-1, corpusFileName);
  precomputengram_2.build_ngram();
  this->nMinusOnegram_packet_set = precomputengram_2.get_ngram_packet_set();

  // printf("Done creating NGram set!\n");
  // printf("NGram:\n");
  // precomputengram.print_ngram();
  // printf("N-1Gram:\n");
  // precomputengram_2.print_ngram();

  FILE* fptr = fopen(this->debugFileName, "w");
  if(fptr==NULL){
    printf("Error opening file \"%s\". Exiting....",this->debugFileName);
    exit(1);
  }
}

abj::NGram::~NGram(){
  // fclose(debug_fptr);
}

double abj::NGram::probablity_sentence(const abj::String& text){
  std::vector<abj::String> textStemlist = PrecomputeNGram::getStemList(text);

  // Make NGram Packet
  double sentence_probablity_log=0;
  for(int i=0; i<=textStemlist.size()-this->ngram; i++){

    // total
    std::vector<abj::String> ngram_packet;
    for(int j=0; j<this->ngram; j++) ngram_packet.push_back(textStemlist[i+j]);
    double total_ngram_packet_occurences = (double)this->ngram_packet_set.getOccurences(ngram_packet);

    //previous
    std::vector<abj::String> nMinusOnegram_packet;
    for(int j=0; j<this->ngram-1; j++) nMinusOnegram_packet.push_back(textStemlist[i+j]);
    double previous_ngram_packet_occurences = (double)this->nMinusOnegram_packet_set.getOccurences(nMinusOnegram_packet);

    // p = previous / total
    double current_probablity = (double)this->probablity(total_ngram_packet_occurences, '|', previous_ngram_packet_occurences);
    sentence_probablity_log += current_probablity;

    fprintf(debug_fptr, "%d) p(%s|%s)=%.1lf/%.1lf=%lf\n", i, ngram_packet[this->ngram-1].get_raw_data(), ngram_packet[0].get_raw_data(), total_ngram_packet_occurences, previous_ngram_packet_occurences, current_probablity);
  }

  return sentence_probablity_log;
}

double abj::NGram::normalize(double log_probablity, int textSize){
  return log_probablity/(double)textSize;
}

double abj::NGram::probablity(double totalCount, char separator, double previousCount){
  // return this->no_smoothing_probablity(totalCount, '|', previousCount);
  return this->laplace_smoothing_probablity(totalCount, '|', previousCount);
}

double abj::NGram::no_smoothing_probablity(double totalCount, char separator, double previousCount){
  return std::log(totalCount/previousCount);
}
double abj::NGram::laplace_smoothing_probablity(double totalCount, char separator, double previousCount){
  totalCount += 1;
  previousCount += this->ngram_packet_set.size();
  return std::log(totalCount/previousCount);
}


int abj::NGram::getNGramSize(){
  return this->ngram_packet_set.size();
}

void abj::NGram::test_function(){
  abj::NGram bigram(2, "./Resources/100_lines.txt");
  std::cout<<"P(\"a Paragraph is\")=";
  std::cout<<bigram.probablity_sentence(*new abj::String("a paragraph is"))<<std::endl;

  std::cout<<"P(\"is Paragraph a\")=";
  std::cout<<bigram.probablity_sentence(*new abj::String("a is paragraph"))<<std::endl;

  std::cout<<"Precomputation is done! Enter sentences to get their probablity!\n";
  double truthValue = false;
  char buffer[1000];
  while(truthValue==false){
    std::cout<<">>";
    std::cin.getline(buffer, 999);
    abj::String sentence(buffer);
    std::cout<<"p("<<buffer<<")="<<abj::NGram::normalize(bigram.probablity_sentence(sentence), sentence.size())<<"\n";
    truthValue = sentence==(*new abj::String("Exit!"));
  }
}

