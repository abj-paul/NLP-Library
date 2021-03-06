#include "bigram.h"
#include<cmath> // for only one function = log

int main(){
  char str[]= "Antonio sacrificed himself.";
  abj::Bigram bg(CORPUS);
  //bg.display_process_in_detail(str);
  //bg.test_function();
  bg.take_input_and_find_probablity();
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
  //printf("\nDestruction!\n");
  //  fclose(this->corpus_fptr);
  //free(this->compiled_corpus_strings);
}
double abj::Bigram::probablity(char* sentence){
  std::vector<char*>word = this->get_word_from_sentence(sentence);
  //print_vector(word);
  double total_prob=1;
  for(int i=1; i<=word.size()-1; i++){
    double prob = 0;
    (double)get_word_count(get_stem(word[i]), (get_stem(word[i+1])))/(double)get_word_count(get_stem(word[i]));
    printf("%s %s / %s = %lf\n", word[i], word[i+1], word[i],prob);
    if(prob=0){
      total_prob=0.01;
      prob=0.01;
    }
    total_prob = total_prob+std::log(prob);
  }
  return total_prob;
}
double abj::Bigram::probablity(const char* sentence){
  std::vector<char*>word = this->get_word_from_sentence(sentence);
  //print_vector(word);
  double total_prob=1;
  for(int i=0; i<=word.size()-1; i++){
    double prob = (double)get_word_count(get_stem(word[i]),get_stem(word[i+1]))/(double)get_word_count(get_stem(word[i]));
    printf("%s %s / %s = %lf\n", word[i], word[i+1], word[i],prob);
    total_prob*=prob;
  }
  return total_prob;
}

bool abj::Bigram::compile_and_normalize_corpus(){
  this->load_all_corpus_strings();
  //printf("Loaded corpus: \n%s\n",this->compiled_corpus_strings);
  SentenceSegmentation ss(this->compiled_corpus_strings);
  ss.use_decision_tree();
  free(compiled_corpus_strings);
  compiled_corpus_strings[0]='\0';
  for(int i=0; i<ss.sentence_list.size(); i++){
    //printf("%d)%s\n",i+1, ss.sentence_list[i]);
    string_concatenate(compiled_corpus_strings, this->start_symbol, ' ');
    std::vector<char*>words = get_word_from_sentence(ss.sentence_list[i]);
    for(int i=0; i<words.size(); i++){
      //  printf("%d)%s->",i+1, words[i]);
      //printf("%s\n",get_stem(words[i]));
      string_concatenate(this->compiled_corpus_strings, get_stem(words[i]), ' ');
    }
    string_concatenate(compiled_corpus_strings, this->end_symbol, ' ');
  }
  //printf(this->compiled_corpus_strings);
  this->naive_punctuation_handling(this->compiled_corpus_strings);
  //printf("%s\n",compiled_corpus_strings);

   // Creating new corpus
   FILE* compiled_fptr = fopen(COMPILED_CORPUS, "w");
   if(compiled_fptr==NULL)exit(1);
   
   int i=0;
   while(this->compiled_corpus_strings[i]!='\0'){
     fprintf(compiled_fptr,"%c",this->compiled_corpus_strings[i]);
     i++;
   }
   fclose(compiled_fptr);
   
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

std::vector<char*> abj::Bigram::get_word_from_sentence(const char* sentence){
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
  char* word = (char*)calloc(MAX_WORD_SIZE*3, sizeof(char));
  int i=0,j=0;
  for(i=start_index,j=0; i<=end_index; i++,j++) word[j]=sentence[i];
  word[i]='\0';
  return word;
}

char* abj::Bigram::make_word(int start_index, int end_index, const char* sentence){
  if(start_index>=corpus_size || end_index>=corpus_size) return NULL; 
  char* word = (char*)calloc(MAX_WORD_SIZE*3, sizeof(char));
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


int abj::Bigram::get_word_count(char* word1, char* word2){
  capitalize(word1);
  capitalize(word2);
  
  FILE* fptr = fopen(COMPILED_CORPUS, "r");
  char word1_corpus[MAX_WORD_SIZE], word2_corpus[MAX_WORD_SIZE];
  int i=0, count=0;
  while(this->compiled_corpus_strings[i]!='\0'){
    fscanf(fptr,"%s %s",word1_corpus, word2_corpus);
     capitalize(word1_corpus);
     capitalize(word2_corpus);
    if(is_same_string( (word1),  (word1_corpus)) && is_same_string( (word2),  (word2_corpus)))  count++;
    i++;
  }
  fclose(fptr);
  return count;
}

int abj::Bigram::get_word_count(char* word){
  capitalize(word);
  FILE* fptr = fopen(COMPILED_CORPUS, "r");
  char word_corpus[MAX_WORD_SIZE];
  int i=0, count=0;
  while(this->compiled_corpus_strings[i]!='\0'){
    fscanf(fptr,"%s",word_corpus);
     capitalize(word_corpus);
    if(is_same_string( (word), word_corpus)){
      count++;
    }
    i++;
  }
  fclose(fptr);
  return count;
}

void abj::Bigram::naive_punctuation_handling(char* str){
  char temp[5]="temp";
  abj::SentenceSegmentation ss(temp);

  int i=0;
  while(str[i]!='\0'){
    if(ss.isPunctuation(str[i])) string_insert_behind(str,&i,' ');
    i++;
  }
}
char* abj::Bigram::normalize_string(char* str){
  SentenceSegmentation ss(str);
  ss.use_decision_tree();

  //  print_vector(ss.sentence_list);

  char* normalized_str = (char*)calloc(string_len(str),sizeof(char));
  normalized_str[0]='\0';
  
for(int i=0; i<ss.sentence_list.size(); i++){
    //printf("%d)%s\n",i+1, ss.sentence_list[i]);
    string_concatenate(normalized_str, this->start_symbol, ' ');
    std::vector<char*>words = get_word_from_sentence(ss.sentence_list[i]);
    for(int i=0; i<words.size(); i++){
      //  printf("%d)%s->",i+1, words[i]);
      //printf("%s\n",get_stem(words[i]));
      string_concatenate(normalized_str, get_stem(words[i]), ' ');
    }
    string_concatenate(normalized_str, this->end_symbol, ' ');
  }
  this->naive_punctuation_handling(normalized_str);
  return normalized_str;
}


void abj::Bigram::test_function(){
  //char str[] = "Abhi am only human hoooo.";
  //std::vector<char*>words = this->get_word_from_sentence(str);
  //for(int i=0; i<words.size(); i++) printf("%s\n",words[i]);

  //Testing Sentence Segmentation
  /*  this->load_all_corpus_strings();
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
  printf(this->compiled_corpus_strings);*/
  // FINAL this->compile_and_normalize_corpus(); //Only line that matters
  //char test_word[] = "Victorious";
  //printf("%s=%d",test_word,get_string_count(get_stem(test_word)));
  // FINAL this->probablity("Antonio sacrificed himself");
  //this->probablity(normalize_string("Antonio sacrificed himself"));

  //  string_insert_behind(str,18,'!');
  //printf("\nInserting %c --> %s\n",'!',str);

  //char str[] = "the";
  //printf("the=%d\n",get_word_count(get_stem(str)));


  //printf("Compiled Corpus:\n");
  //this->compile_and_normalize_corpus();
  //printf("Control reaches here after test function.\n");
  //  this->load_all_corpus_strings();
  //this->input_string_and_get_probablity();

  char temp0[] = "sacrificed";
  printf("Sacrificed - occurs: %d\n",this->get_word_count(get_stem(temp0)));
}

void abj::Bigram::take_input_and_find_probablity(){
  char input_str[MAX_WORD_SIZE*100];
  printf("Enter a string(related to corpus): ");
  scanf("%[^\n]s",input_str);
  this->display_process_in_detail(input_str);
}

void abj::Bigram::display_process_in_detail(char* input_str){
  printf("Raw Corpus:\n");
  this->print_raw_corpus();
  this->compile_and_normalize_corpus();
  printf("\n-----------------------------------------------------------------------------------------\nCompiled Corpus:\n");
  this->print_compiled_corpus();

  printf("-----------------------------------------------------------------------------------------\nOur input is:\n%s\n",input_str);
  printf("After normalizing, input string becomes:\n%s\n",this->normalize_string(input_str));
  string_copy(input_str, this->normalize_string(input_str));

  SentenceSegmentation ss(input_str);
  ss.use_decision_tree();
  printf("-----------------------------------------------------------------------------------------\nAfter sentence segmentation, we get the following sentences.\n");
  print_vector(ss.sentence_list);


  double total_prob=0;
  for(int sentence_count=0; sentence_count<ss.sentence_list.size(); sentence_count++){
    std::vector<char*>words = this->get_word_from_sentence(ss.sentence_list[sentence_count]);
    printf("For sentence %d, we get the following tokens(Stemmed).\n",sentence_count+1);
    print_vector(words);

    double total_prob_sentence=0;
    for(int word_count=1; word_count<words.size()-1; word_count++){
      double both = (double)get_word_count(words[word_count],words[word_count+1]);
      double single = (double)get_word_count(words[word_count]);
      printf("c(%s | %s)=%.2lf\n",words[word_count+1],words[word_count], both);
      printf("c(%s)=%.2lf\n",words[word_count], single);

      double prob = std::log((both+1)/(single+1));
      printf("-----------------------------------------------------------------------------------------\nSo probablity = %.2lf\n",prob);

      total_prob_sentence +=prob;
    }
    printf("Probablity for the sentence is=%.2lf\n",total_prob_sentence);
    total_prob += total_prob_sentence;
  }
  printf("---------------------------\nTotal Probablity for the passage is=%.2lf\n",total_prob);
}

void abj::Bigram::print_raw_corpus(){
  char str[MAX_WORD_SIZE];
  while(!feof(this->corpus_fptr)){
    fscanf(this->corpus_fptr,"%s", str);
    printf("%s ",str);
  }
  fseek(this->corpus_fptr, 0L, SEEK_SET);
}

void abj::Bigram::print_compiled_corpus(){
  printf("%s\n",this->compiled_corpus_strings);
}

void abj::Bigram::unigram(char* str){
  string_copy(str, normalize_string(str));
  std::vector<char*>words = get_word_from_sentence(str);
}
