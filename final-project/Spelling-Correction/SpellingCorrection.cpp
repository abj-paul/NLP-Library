#include "SpellingCorrection.h"

abj::SpellingCorrection::SpellingCorrection(const abj::String& filename){
  this->bigram = new abj::Bigram(filename);
  this->prepareModel();
  this->filename.initialize(filename);
}
abj::SpellingCorrection::~SpellingCorrection(){
  for(int i=0; i<this->candidateList.size(); i++)
    this->candidateList[i].~Candidate();
}



void abj::SpellingCorrection::prepareModel(){
  this->bigram->preprocess_corpus();
  printf("DEBUG: Done preparing bigram\n");
}

void abj::SpellingCorrection::clearCandidateList(){
  this->candidateList.clear();
}


void abj::SpellingCorrection::setStem(const abj::String& givenWord, const abj::String& previousWord){
  this->givenWord = givenWord;
  this->previousWord = previousWord;
  this->clearCandidateList();

  this->generateCandidateList();
  printf("DEBUG: Done preparing candidate list for stem \"%s\"\n",this->givenWord.get_raw_data());
}

void abj::SpellingCorrection::generateCandidateList(){
  abj::String givenStem = (new abj::Stemmer(givenWord))->get_stem();
  abj::String previousStem = (new abj::Stemmer(previousWord))->get_stem();
  
  abj::SentenceSegmenter ss(abj::PrecomputeNGram::getFileData(this->filename.get_raw_data()));
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


  
  for(int i=0; i<tokens.size(); i++){
    MED med(tokens[i], this->givenWord);
    med.domerau_levensthein_edit_distance();
    if(med.getDistance()<=2 && med.getDistance()!=0){
      Candidate candidate(tokens[i], med.getDistance());
      abj::NoisyChannelModel ncm(candidate.getWord(), this->givenWord);

      abj::Stemmer stemmer(tokens[i]);
      abj::String currentStem(stemmer.get_stem());
      candidate.setNoisyChannelProbablity(ncm.getProbablity());
      candidate.setLanguageProbablity(this->bigram->laplace_smoothing_probablity(currentStem, '|', previousStem));
      
      this->candidateList.push_back(candidate);
    }
  }
}


void abj::SpellingCorrection::printCandidateList(){
  FILE* fptr = fopen(this->CANDIDATE_LIST_FILE, "w");
  if(fptr==NULL){
    printf("\"%s\" file not found! Exiting...\n",this->CANDIDATE_LIST_FILE);
    exit(1);
  }

  fprintf(fptr, "The word is = %s\n",this->givenWord.get_raw_data());
  fprintf(fptr, "Number of candidates = %d\n", this->candidateList.size());
  for(int i=0; i<this->candidateList.size(); i++){
    candidateList[i].print(fptr);
  }

  fclose(fptr);
}


void abj::SpellingCorrection::test_function(){
  abj::String filename("./Resources/100_lines.txt");
  abj::SpellingCorrection sc(filename);
  sc.setStem(*new abj::String("watchng"), *new abj::String("am"));
  // sc.setStem((*new abj::Stemmer(*new abj::String("banana"))).get_stem(), (*new abj::Stemmer(*new abj::String("eating"))).get_stem());
  sc.printCandidateList();
}
