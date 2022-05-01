#include "NoisyChannelModel.h"

abj::NoisyChannelModel::NoisyChannelModel(abj::String& mainWord, abj::String& newWord){
  filename.initialize("spell-errors.txt");
  this->total_probablity = 0;
  this->loadSpellingFile();
  this->load_confusion_matrices();
}

void abj::NoisyChannelModel::loadSpellingFile(){
  FILE* fptr = fopen(this->filename.get_raw_data(),"r");
  if(fptr==NULL) {
    printf("File not found! Exiting....");
    exit(1);
  }
  fseek(fptr, 0, SEEK_END);
  int file_size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET); 

  char *file_data = (char*)malloc(file_size + 1);
  fread(file_data, file_size, 1, fptr);

  file_data[file_size] = '\0';
  fclose(fptr);

  fileText.initialize(file_data); 
}

double abj::NoisyChannelModel::getProbablity(){
  std::string mainWord_STL(mainWord.get_raw_data());
  std::string newWord_STL(newWord.get_raw_data());

  MED med(mainWord_STL, newWord_STL);
  med.domerau_levensthein_edit_distance();
  this->backtrace_noisy_path(mainWord.size(), newWord.size(), med.direction);
}

void abj::NoisyChannelModel::backtrace_noisy_path(int i, int j, int direction[][MAX_WORD_SIZE]){
  if(i<=0 || j<=0) return;
 
  if(direction[i][j]==INSERTION_RIGHT_ARROW){
    int a = this->newWord[j-1]-'A';
    int b = this->mainWord[j]-'A'; 

    int error_occurence = this->insertion_confusion_matrix[a][b];
    int char_occurence = this->substringCount(this->newWord[j-1]); 
    double error_probablity = std::log((double)error_occurence/(double)char_occurence);

    this->total_probablity+=error_occurence;
    this->backtrace_noisy_path(i, j-1, direction);
  }
  else if(direction[i][j]==DELETION_DOWN_ARROW) {
    int a = this->newWord[j-1]-'A';
    int b = this->newWord[j]-'A'; 

    int error_occurence = this->insertion_confusion_matrix[a][b];
    int char_occurence = this->substringCount(this->newWord[j-1]); 
    double error_probablity = std::log((double)error_occurence/(double)char_occurence);

    this->total_probablity+=error_occurence;

    this->backtrace_noisy_path(i-1, j, direction);
  }
  else if(direction[i][j]==SAME_CHARACTER_DIAGONAL_ARROW) this->backtrace_noisy_path(i-1, j-1, direction);
  else if(direction[i][j]==SUBSTITUTION_DIAGONAL_ARROW){
    this->backtrace_noisy_path(i-1, j-1, direction);
  }
  else if(direction[i][j]==TRANSPOSITION_ARROW){
    this->backtrace_noisy_path(i-2, j-2, direction);
  }
  return;
}

int abj::NoisyChannelModel::substringCount(char a){
  std::string pattern(1,a);
  std::string text(this->fileText.get_raw_data());
  KMP kmp(text,pattern);
  return kmp.occurences.size();
}
int abj::NoisyChannelModel::substringCount(char a, char b){
  char temp[2];
  temp[0]=a;
  temp[1]=b;
  std::string pattern(temp);
  std::string text(this->fileText.get_raw_data());
  KMP kmp(text,pattern);
  return kmp.occurences.size();
}
