#include "Bigram.h"
using namespace abj;

Bigram::Bigram(){
  this->corpus.initialize(this->extract_content_from_file(DEFAULT_CORPUS));

  Vector<String>initializer;
  abj::String temp("Initializer");
  initializer.push(temp);
  this->stemmed_corpus.push(initializer);
}
Bigram::Bigram(const char* filename){
  // this->stemmed_corpus.push(initializer);
  this->corpus.initialize(this->extract_content_from_file(filename));
}

char* Bigram::extract_content_from_file(const char* filename){ //auxiliary function
  FILE* fptr = fopen(DEFAULT_CORPUS,"r");
  if(fptr==NULL){
    printf("Error! %s-File not found!\n",filename);
    exit(1);
  }

  fseek(fptr,0L,SEEK_END);
  int size = ftell(fptr);
  fseek(fptr, 0L, SEEK_SET);
  
  char* content = (char*)calloc(size+1, sizeof(char));
  fread(content, size, 1, fptr);
  content[size]='\0';

  return content;
}

Vector<Vector<String>> Bigram::get_stems_list(abj::String& text){
  printf("Printing corpus:\n");
  this->corpus.print();
  
  SentenceSegmenter ss;
  ss.setCorpus(text);
  ss.use_decision_tree();

  printf("Printing sentences:-----------------------\n");
  ss.print();

  Vector<String>sentences;
  for(int i=0; i<ss.sentence_list.size(); i++){
    Punctuation p;
    p.setCorpus(ss.sentence_list.get(i));
    p.handle_punctuation();
    String sentence = p.getUpdatedCorpus();
    sentences.push(sentence);
  }
  printf("After punctuation handling, Printing sentences:--------------\n");
  for(int i=0; i<sentences.size(); i++) sentences[i].print();
  
  Vector<Vector<String>> all_tokens;
  for(int i=0; i<ss.sentence_list.size(); i++){
      Tokenizer t ;
      t.setString(ss.sentence_list.get(i));
      t.tokenize();
      Vector<String>tokens = t.getTokens();
      all_tokens.push(tokens);

      printf("Printing tokens for sentence:%d\n",i+1);
      t.print();
  }

  //Stemming the tokens
  Vector<Vector<String>> all_stems;
  for(int i=0; i<all_tokens.size(); i++){
    Vector<String> sentence_stems;
    for(int j=0; j<all_tokens[i].size(); j++){
      String current_token = all_tokens[i].get(j);
      Stemmer stemmer;
      stemmer.initialize(current_token);
      String current_stem = stemmer.get_stem();
      sentence_stems.push(current_stem);
    }
    all_stems.push(sentence_stems);
  }
  return all_stems;
}

bool Bigram::preprocess_corpus(){
  this->stemmed_corpus = this->get_stems_list(this->corpus);

  int stem_count=0;
  for(int i=0; i<stemmed_corpus.size(); i++)
    for(int j=0; j<stemmed_corpus[i].size(); j++) stem_count++;
  this->VOCABULARY_SIZE_FOR_BIGRAM = stem_count-1;

  return true;
}

int Bigram::count_of_stem(String stem){
  int count=0;
  for(int i=0; i<stemmed_corpus.size(); i++){
    for(int j=0; j<stemmed_corpus[i].size(); j++){
      String corpus_stem(stemmed_corpus[i].get(j));
      if(stem.equals(corpus_stem)) count++;
    }
  }
  return count;
}

int Bigram::count_of_two_stem(String stem1, String stem2){
  int count=0;
  for(int i=0; i<stemmed_corpus.size(); i++){
    for(int j=1; j<stemmed_corpus[i].size(); j++){
      if(stemmed_corpus[i][j-1].equals(stem1) && stemmed_corpus[i][j].equals(stem2)) count++;
    }
  }
  return count;
}

double Bigram::probablity_laplace_smoothing(String word2, char PIPE, String word1 ){
  int x = count_of_two_stem(word1,word2)+1;
  int y = count_of_stem(word1)+VOCABULARY_SIZE_FOR_BIGRAM;
  return std::log(((double)x / (double)y));
}

double Bigram::text_probablity_using_laplace_smoothing(String text){
  // // First preprocess the sentence
  // SentenceSegmenter sentenceSegmenter(text);
  // sentenceSegmenter.use_decision_tree();

  // // Handling Puctuation
  // for(int i=0; i<sentenceSegmenter.sentence_list.size(); i++){
  //   Punctuation punctuation(sentenceSegmenter.sentence_list[i]);
  //   punctuation.handle_punctuation();
  //   sentenceSegmenter.sentence_list.set(i,punctuation.getUpdatedCorpus());
  // }
  // // Tokenize it
  // Vector<Vector<String>> tokenized_text;
  // for(int i=0; i<sentenceSegmenter.sentence_list.size(); i++){
  //   Tokenizer tokenizer(sentenceSegmenter.sentence_list[i]);
  //   tokenizer.tokenize();
  //   Vector<String> tokens = tokenizer.getTokens();
  //   tokenized_text.push(tokens);
  // }
  // //sentenceSegmenter.~SentenceSegmenter();
  // // Now stem it
  // Vector<Vector<String>> text_stems;
  // for(int i=0; i<tokenized_text.size(); i++){
  //   Vector<String> sentence_stem_list;
  //   for(int j=0; j<tokenized_text[i].size(); j++){
  //     Stemmer t;
  //     t.initialize(tokenized_text[i][j]);
  //     String temp = t.get_stem();
  //     sentence_stem_list.push(temp);
  //   }
  //   text_stems.push(sentence_stem_list);
  // }
  Vector<Vector<String>> text_stems;
  text_stems = this->get_stems_list(text);

  // text_stem is our final output! We will work on it.
  double total_probablity=0;
  for(int i=0; i<text_stems.size(); i++){
    for(int j=1; j<text_stems[i].size(); j++){
      double curr_probablity = probablity_laplace_smoothing(text_stems[i][j], '|', text_stems[i][j-1]);
      text_stems[i][j].print();
      printf("Probablity=%lf\n",curr_probablity);
      total_probablity += curr_probablity;
    }
  }
  return total_probablity;
}

void Bigram::print_stems(){
  for(int i=0; i<stemmed_corpus.size(); i++){
    for(int j=0; j<stemmed_corpus[i].size(); j++){
      this->stemmed_corpus[i].get(j).print();
    }
  }
}

void Bigram::test_function(){
  printf("Testing bigram---------------------------\n");

  /*  String phrase("Victorious Soldiers !");
  Tokenizer tokenizer(phrase);
  tokenizer.tokenize();
  Vector<String>tokens = tokenizer.getTokens();
  Stemmer w1, w2;
  w1.initialize(tokens[0]);
  w2.initialize(tokens[1]);
  
  double p = bigram.probablity_laplace_smoothing(w2.get_stem(), '|', w1.get_stem());
  phrase.print();
  printf("probablity=%lf\n",p);
  */

  String phrase("Stupid Soldiers must work together to achieve big things!");
  Bigram bigram;
  bigram.preprocess_corpus();
  std::cout<<"Probablity: "<<bigram.text_probablity_using_laplace_smoothing(phrase)<<std::endl;

}

