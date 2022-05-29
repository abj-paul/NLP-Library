#include "KMP.h"
using namespace std;

KMP::KMP(string text, string pattern){
  // printf("Running KMP.\n");
  this->text = text;
  this->pattern = pattern;
  this->initialize();
  this->KMP_algorithm();
}


void KMP::initialize(){
  for(int i=0; i<pattern.size(); i++) this->lps.push_back(0);
}

char* getSpellingFile(){
  char fileName[] = "../Resources/spell-errors.txt";
  FILE* fptr = fopen(fileName,"r");
  if(fptr==NULL) {
    printf("\"%s\" File not found! Exiting....", fileName);
    exit(1);
  }
  fseek(fptr, 0, SEEK_END);
  int file_size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET); 

  char *file_data = (char*)malloc(file_size + 1);
  fread(file_data, file_size, 1, fptr);

  file_data[file_size] = '\0';
  fclose(fptr);

  return file_data;
}

void KMP::KMP_algorithm(){
  int n = text.size();
  int m = pattern.size();

  this->computeLPS();

  int i=0, j=0;

  while(i<n){
    if(text[i]==pattern[j]){
      i++;
      j++;
    }else{
      if(j==0) i++;
      else j=lps[j-1];
    }

    if(j==m){
      // printf("Match found at shift(End Index) %d,\n",i);
      this->occurences.push_back(i);
      j=lps[j-1];
    }
  }
}


void KMP::computeLPS(){
  int len = 0;
  int i = 1;
  this->lps[0]=0;

  while(i<pattern.size()){
    if(pattern[i]==pattern[len]) {
      this->lps[i]=len+1;
      len++;
      i++;
    }else{
      if(len==0){
	lps[i]=0;
	i++;
      }else len = this->lps[len-1];
    }
  }
}
void KMP::printMatchingIndices(){
  for(int i=0; i<this->occurences.size(); i++) printf("%d ",occurences[i]);
  printf("\n");
}

void KMP::test_function(){
  std::string text(getSpellingFile());
  std::string pattern="u";

  KMP kmp(text, pattern);
  // kmp.printMatchingIndices();
  printf("Matches= %d\n", kmp.occurences.size());
}

// int main(){
//   KMP::test_function();
//   return 0;
// }
