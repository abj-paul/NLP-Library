#include "find_string_match.cpp"

#define MULTIPLIER 100000

int total_words_in_corpus(const char* filename){
  FILE* fptr = fopen(filename, "r");
  int count=0;
  while(!feof(fptr)){
    fgetc(fptr);
    count++;
  }
  return count;
}

void find_probablity(const char* sentence, const char* filename){
  char** x = tokenizer_revamp(sentence);
  char* bi_word = (char*)calloc(MAX_WORD_SIZE*2, sizeof(char));
  
  int i=2, total_count=total_words_in_corpus(filename);
  
  while(x[i]!=NULL){
    string_concatenate(x[i-1], x[i], bi_word);
    int word_count = find_match(bi_word,filename);
    double probablity = word_count*MULTIPLIER/total_count;
    printf("%d) %s=%lf\n",i,bi_word,probablity);

    i++;
   }
}

int main(){
  //  char** x = tokenizer_revamp("Abhijit is only human duh.");
  //print_word_list(x);

  find_probablity("The students found it very good.","korpus/stanfordSentimentTreebank/datasetSentences.txt");
  return 0;
}
