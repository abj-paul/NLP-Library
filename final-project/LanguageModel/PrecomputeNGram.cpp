#include "PrecomputeNGram.h"

bool operator==(std::vector<abj::String>& packet_one, std::vector<abj::String>& packet_two){
  for(int i=0; i<packet_one.size(); i++){
    packet_one[i].capitalize();
    packet_two[i].capitalize();
    if(packet_one[i]==packet_two[i]) continue;
    else return false;
  }
  return true;
}
std::ostream& operator<<(std::ostream& os, const std::vector<abj::String>& ngram_packet) {
  os<<"[";
  for(int i=0; i<ngram_packet.size(); i++)
    os<<ngram_packet[i]<<",";
  os<<"]\n";
  return os;
}

abj::PrecomputeNGram::PrecomputeNGram(int nGram, const abj::String& corpusFileName){
  this->nGram = nGram;
  this->corpusFileName = corpusFileName;
}

abj::PrecomputeNGram::~PrecomputeNGram(){
  //call set destructor
}

abj::String abj::PrecomputeNGram::getFileData(const abj::String& filename){
  FILE *fptr = fopen(filename.get_raw_data(), "r");
  if(fptr==NULL){
    printf("Error opening file %s. Exiting....\n",filename.get_raw_data());
    exit(1);
  }
  fseek(fptr, 0, SEEK_END);
  unsigned int file_size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);  /* same as rewind(f); */

  char *buffer = (char*)malloc(file_size + 1);
  fread(buffer, file_size, 1, fptr);
  fclose(fptr);

  buffer[file_size] = 0;

  abj::String ans(buffer);
  free(buffer);
  return ans;
}

std::vector<abj::String>  abj::PrecomputeNGram::getStemList(const abj::String& text){
  // First, Segment sentence
  abj::SentenceSegmenter ss(text);
  ss.use_decision_tree();
  std::vector<abj::String> sentences = ss.getSentenceList();

  // Then handle punctuaio
  for(int i=0; i<sentences.size(); i++){
    abj::Punctuation punctuation(sentences[i]);
    punctuation.handle_punctuation();
    sentences[i] = punctuation.getUpdatedCorpus();
  }
  // Then tokenize
 std::vector<abj::String> tokens;
 for(int i=0; i<sentences.size(); i++){
   abj::Tokenizer tokenizer(sentences[i]);
   tokenizer.tokenize();
   std::vector<abj::String> current_sentence_tokens = tokenizer.getTokens();
   for(int j=0; j<current_sentence_tokens.size(); j++)
     tokens.push_back(current_sentence_tokens[j]);
 }
 // Now Stem them
 std::vector<abj::String> stems;
 for(int i=0; i<tokens.size(); i++){
   abj::Stemmer stemmer(tokens[i]);
   stems.push_back(stemmer.get_stem());
 }
 return stems;
}

void abj::PrecomputeNGram::build_ngram(){
  std::vector<abj::String> stemList = this->getStemList(this->getFileData(this->corpusFileName.get_raw_data()));

  for(int i=0; i<=stemList.size()-nGram; i++){
    //make nGram packet
    std::vector<abj::String> nGram_packet;
    for(int j=0; j<nGram; j++) nGram_packet.push_back(stemList[i+j]);

    this->ngram_packet_set.insert(nGram_packet);
  }
}

void abj::PrecomputeNGram::print_ngram(){
  this->ngram_packet_set.print();
}

abj::Set<std::vector<abj::String>>& abj::PrecomputeNGram::get_ngram_packet_set(){
  return this->ngram_packet_set;
}


void abj::PrecomputeNGram::test_function(){
  std::vector<abj::String> packet_one;
  packet_one.push_back(*new abj::String("I"));
  packet_one.push_back(*new abj::String("eat"));
  packet_one.push_back(*new abj::String("rice"));

  std::vector<abj::String> packet_two;
  packet_two.push_back(*new abj::String("He"));
  packet_two.push_back(*new abj::String("eat"));
  packet_two.push_back(*new abj::String("rice"));

  bool truth_value = packet_one==packet_two;
  std::cout << "Same NGram packets? " << truth_value << std::endl;

  PrecomputeNGram precomputengram(2, "./Resources/100_lines.txt");
  precomputengram.build_ngram();
  precomputengram.print_ngram();

}
