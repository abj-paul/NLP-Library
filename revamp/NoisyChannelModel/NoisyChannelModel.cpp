#include "NoisyChannelModel.h"

abj::NoisyChannelModel::NoisyChannelModel(abj::String& correction, abj::String& typo){
  printf("Running Noisy Channel Model.\n");
  this->correction = correction;
  this->typo = typo;

  this->total_probablity = 0;

  filename.initialize("spell-errors.txt");
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
  std::string correction_STL(correction.get_raw_data());
  std::string typo_STL(typo.get_raw_data());

  MED med(correction_STL, typo_STL);
  med.domerau_levensthein_edit_distance();

  abj::String c(med.correction);
  abj::String t(med.typo);
  this->correction = c;
  this->typo = t;
  this->backtrace_noisy_path(correction.size()-1, typo.size()-1, med.direction);

  return this->total_probablity;
}
void abj::NoisyChannelModel::backtrace_noisy_path(int i, int j, int direction[][MAX_WORD_SIZE]){
  if(i<=0 || j<=0) return;
  int alphabets = this->insertion_confusion_matrix.size();
  if(direction[i][j]==INSERTION_RIGHT_ARROW){
    int a = correction[i]-'A';
    int b = typo[j]-'A'; 

    int error_occurence = this->insertion_confusion_matrix[a][b];
    int char_occurence = this->substringCount(correction[i]); 
    double error_probablity = std::log(
				       ((double)error_occurence+1)
				       /
				       ((double)char_occurence+alphabets)
				       );

    this->total_probablity+=error_probablity;
    this->backtrace_noisy_path(i, j-1, direction);
  }
  else if(direction[i][j]==DELETION_DOWN_ARROW) {
    int a = typo[j]-'A';
    int b = correction[i]-'A';  // Can not handle insertion at EOL

    int error_occurence = this->deletion_confusion_matrix[a][b];
    int char_occurence = this->substringCount(typo[j], correction[i]); 
    double error_probablity = std::log(
				       ((double)error_occurence+1)
				       /
				       ((double)char_occurence+alphabets)
				       );

    this->total_probablity+=error_probablity;
    this->backtrace_noisy_path(i-1, j, direction);
  }
  else if(direction[i][j]==SAME_CHARACTER_DIAGONAL_ARROW) this->backtrace_noisy_path(i-1, j-1, direction);
  else if(direction[i][j]==SUBSTITUTION_DIAGONAL_ARROW){
    int a = typo[j]-'A';
    int b = correction[i]-'A'; 

    int error_occurence = this->substitution_confusion_matrix[a][b];
    int char_occurence = this->substringCount(correction[i]); 
    double error_probablity = std::log(
				       ((double)error_occurence+1)
				       /
				       ((double)char_occurence+alphabets)
				       );

    this->total_probablity+=error_probablity;
    this->backtrace_noisy_path(i-1, j-1, direction);
  }
  else if(direction[i][j]==TRANSPOSITION_ARROW){
    int a = typo[j]-'A';
    int b = correction[i]-'A'; 

    int error_occurence = this->transposition_confusion_matrix[a][b];
    int char_occurence = this->substringCount(typo[j], correction[i]); 
    double error_probablity = std::log(
				       ((double)error_occurence+1)
				       /
				       ((double)char_occurence+alphabets)
				       );

    this->total_probablity+=error_probablity;
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
double abj::NoisyChannelModel::normalize(double log_value){
  double probablity = std::pow(10, log_value);
  probablity = pow(probablity, 1.0/(double)this->correction.size());
  return probablity;
}

double abj::NoisyChannelModel::getNormalizedProbablity(){
  if(this->total_probablity==0){
    std::string correction_STL(correction.get_raw_data());
    std::string typo_STL(typo.get_raw_data());
    
    MED med(correction_STL, typo_STL);
    med.domerau_levensthein_edit_distance();
    abj::String c(med.correction);
    abj::String t(med.typo);

    this->backtrace_noisy_path(correction_STL.size(), typo_STL.size(), med.direction);
  }
  return this->normalize(this->total_probablity);
}

void abj::NoisyChannelModel::test_function(){
  //piece, peace | elephant, elephunt
  abj::String mainWord("elephan");
  abj::String candidate("elephant");
  printf("Main Word:%s\n",mainWord.get_raw_data());
  printf("Candidate:%s\n",candidate.get_raw_data());
  
  abj::NoisyChannelModel ncm(candidate, mainWord);
  double probablity = ncm.getProbablity();
  printf("Probablity=%lf\n",probablity);
  probablity = ncm.getNormalizedProbablity();
  printf("Normalized Probablity=%lf\n",probablity);
}

int main(){
  abj::NoisyChannelModel::test_function();
  return 0;
}
