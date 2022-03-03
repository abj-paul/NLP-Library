#include "bigram.h"

int main(){
  abj::Bigram bg(CORPUS);
  bg.test_function();
  return 0;
}

abj::Bigram::Bigram(const char* corpus){
  this->corpus_fptr = fopen(corpus, "r");
  if(this->compiled_corpus==NULL){
    printf("File not found.\n");
    exit(1);
  }
  fseek(this->corpus_fptr,0L, SEEK_END);
  this->corpus_size = ftell(this->corpus_fptr);
  fseek(this->corpus_fptr, 0L, SEEK_SET);
  
  this->compiled_corpus_strings=(char*)calloc(this->corpus_size, sizeof(char));
  compiled_corpus_strings[0]='\0';
  
}
abj::Bigram::~Bigram(){
  printf("\nDestruction!\n");
  //  fclose(this->corpus_fptr);
  //free(this->compiled_corpus_strings);
}
double probablity(){
  return 1; 
}

bool abj::Bigram::compile_and_normalize_corpus(){
  this->load_all_corpus_strings();
  SentenceSegmentation ss(this->compiled_corpus_strings);
  ss.use_decision_tree();
  printf("Sentence list size: %d\n",ss.sentence_list.size());
  for(int i=0; i<ss.sentence_list.size(); i++){
    std::vector<char*>words = this->get_word_from_sentence(ss.sentence_list[i]);
    printf("Word list size: %d\n",words.size());
    for(int j=0; j<words.size(); j++){
      string_concatenate(this->compiled_corpus_strings, get_stem(words[j]), ' ');
    }
    for(int i=0; i<words.size(); i++) free(words[i]);
  }
 
  // free words and sentence
  //printf("%s\n",this->compiled_corpus_strings);
  return true;
}


std::vector<char*> abj::Bigram::get_word_from_sentence(char* sentence){
  std::vector<char*>words;
  int i=0, start_index=0;
  while(sentence[i]!='\0'){
    if(sentence[i]==' '){
      words.push_back(this->make_word(start_index, i-1, sentence));
      start_index=i+1;
    }
    i++;
  }
  words.push_back(this->make_word(start_index, i-1, sentence));
  return words;
  
}

char* abj::Bigram::make_word(int start_index, int end_index, char* sentence){
  if(start_index>=corpus_size || end_index>=corpus_size) return NULL; 
  char* word = (char*)calloc(MAX_WORD_SIZE*2, sizeof(char));
  int i=0,j=0;
  for(i=start_index,j=0; i<=end_index; i++,j++) word[j]=sentence[i];
  word[i]='\0';
  return word;
}

bool abj::Bigram::load_all_corpus_strings(){
  while(!feof(this->corpus_fptr)){
    char* passage = (char*)calloc(MAX_WORD_SIZE,sizeof(char));
    fscanf(this->corpus_fptr,"%s",passage);
    string_concatenate(this->compiled_corpus_strings, passage, ' ');
    free(passage);
  }
  //printf("Loading corpus: \n%s\n",this->compiled_corpus_strings);
  return true;
}

void abj::Bigram::test_function(){
  //char str[] = "Abhi am only human hoooo.";
  //std::vector<char*>words = this->get_word_from_sentence(str);
  //for(int i=0; i<words.size(); i++) printf("%s\n",words[i]);

  //Testing Sentence Segmentation
  this->load_all_corpus_strings();
  //printf("Loaded corpus: \n%s\n",this->compiled_corpus_strings);
  SentenceSegmentation ss(this->compiled_corpus_strings);
  ss.use_decision_tree();
  free(compiled_corpus_strings);
  for(int i=0; i<ss.sentence_list.size(); i++){
    //printf("%d)%s\n",i+1, ss.sentence_list[i]);
    std::vector<char*>words = get_word_from_sentence(ss.sentence_list[i]);
    for(int i=0; i<words.size(); i++){
      printf("%d)%s->",i+1, words[i]);
      printf("%s\n",get_stem(words[i]));
      string_concatenate(this->compiled_corpus_strings, get_stem(words[i]), ' ');
    }
  }
  printf(this->compiled_corpus_strings);




  //printf("Compiled Corpus:\n");
  //this->compile_and_normalize_corpus();
  //printf("Control reaches here after test function.\n");
  //  this->load_all_corpus_strings();
}
