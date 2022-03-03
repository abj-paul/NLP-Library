#include "sentence-segmentation.h"


/*int main(){
  char main_string[] = "I am only human. Dr. Albert told me to fetch him. PhD. professors are often very helpful. Selena is a great singer!";
  abj::SentenceSegmentation ss(main_string) ;
  ss.test_function();
  return 0;
  }*/

abj::SentenceSegmentation::SentenceSegmentation(char* string){
  //Prepare
  this->str=string;
  this->punctuation_list = getPunctuationList(this->punctuation_list_containing_file);
  
}

bool abj::SentenceSegmentation::decision_tree(int i){
  // Detedct punctuation in the string
    if(isPunctuation(str[i])){
      if(lots_of_space_after_it(i)){
	return true;
      }else{
	if(str[i]=='?' || str[i]=='!' || str[i]==':') return true;
	else if(str[i]=='.'){
	  if(!isAbbreviation(str,i)) return true;
	  else return false;
	}
	else return false;
      }
    }
    i++;
  return false;
}

void abj::SentenceSegmentation::use_decision_tree(){
  
  int start_index=0;
  for(int i=0; i<string_len(this->str); i++){
    if(this->decision_tree(i)){
      this->sentence_list.push_back(this->make_sentence(start_index, i));
      start_index=i+2; // Because there is a space between (dot) and first word of next sentence
    }
    //else printf("%c",this->str[i]);
  }
}

bool abj::SentenceSegmentation::isPunctuation(char c){
  for(int i=0; i<number_of_punctuation; i++){
    if(c==this->punctuation_list[i]) return true;
  }
  return false;
}

char* abj::SentenceSegmentation::getPunctuationList(const char* filename){
  FILE* fptr = fopen(filename, "r");
  if(fptr==NULL){
    printf("File not found.\n");
    exit(1);
  }

  fseek(fptr, 0L, SEEK_END);
  this->number_of_punctuation=ftell(fptr);

  fseek(fptr, 0L, SEEK_SET);
  char* punctuation_list = (char*)calloc(this->number_of_punctuation+1, sizeof(char));

  for(int i=0; i<this->number_of_punctuation; i++){
    fscanf(fptr,"%c\n",&punctuation_list[i]);
  }
  fclose(fptr);
  return punctuation_list;
}

void abj::SentenceSegmentation::test_function(){
  char* punctuation_list = this->getPunctuationList(this->punctuation_list_containing_file);

  print_array(punctuation_list, this->number_of_punctuation);

  char c = '!';
  printf("%d\n",this->isPunctuation(c));
  //  printf("Done printing.\n");

  this->use_decision_tree();
  printf("Number of sentences:%d\n",this->sentence_list.size());
  for(int i=0; i<this->sentence_list.size(); i++){
    printf("%s\n",this->sentence_list[i]);
  }
 
  // Punctuation List
}
abj::SentenceSegmentation::~SentenceSegmentation(){
  free(this->punctuation_list);
}



bool abj::SentenceSegmentation::lots_of_space_after_it(int i){
  if(str[i+1]=='\0' || str[i+1]==EOF) return true;

  i++;
  int space_count=0;
  while(str[i]!='\0'){
    if(str[i]==' ') space_count++;
    if(space_count>=2) return true;
    i++;
  }
  if(space_count>=2) return true;
  return false;
}

bool abj::SentenceSegmentation::isAbbreviation(char* str, int i){
  return false;
}

void abj::SentenceSegmentation::print_sentence(int start_index, int end_index){
  for(int i=start_index; i<=end_index; i++) printf("%c",this->str[i]);
  printf("\n");
}

char* abj::SentenceSegmentation::make_sentence(int start_index, int end_index){
  char* store_in_heap = (char*)calloc(end_index-start_index+1+1, sizeof(char));

  int j=0;
  for(int i=start_index; i<=end_index; i++) {
    store_in_heap[j]=this->str[i];
    j++;
  }
  store_in_heap[j]='\0';

  //  printf("j=%d\nInside: %s\n",j,store_in_heap);
  return store_in_heap;
}

