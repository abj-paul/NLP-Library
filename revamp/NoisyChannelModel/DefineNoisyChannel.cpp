#include "DefineNoisyChannel.h"

DefineNoisyChannel::DefineNoisyChannel(){
  printf("Running Define Noisy Channel.\n");
  this->load_file();
  this->printDatabase();
  this->initialize_fields();
}


void DefineNoisyChannel::initialize_fields(){
  for(int i=0; i<this->number_of_alphabets; i++){
    std::vector<int> row;
    for(int j=0; j<this->number_of_alphabets; j++) row.push_back(0);
    this->insertion_confusion_matrix.push_back(row);
    this->deletion_confusion_matrix.push_back(row);
    this->substitution_confusion_matrix.push_back(row);
    this->transposition_confusion_matrix.push_back(row);
  }
}

void DefineNoisyChannel::load_file(){
  std::ifstream fileStream;
  fileStream.open(this->filename);

  if(fileStream.is_open()){
    std::string line;
    while(fileStream.good()){
      if(std::getline(fileStream,line)) this->split_and_store(line);
    }
  }
}

void DefineNoisyChannel::split_and_store(std::string line){
  char portionSeparator = ':';
  std::vector<std::string> portions = this->get_tokens(line, portionSeparator);

  std::string correction = portions[0];

  char wordSeparator = ',';
  std::vector<std::string> spellingErrors = this->get_tokens(portions[1], wordSeparator);

  this->handleMultipleOccurenceOfWord(&spellingErrors);
  
  RECORD record = make_pair(correction,spellingErrors);
  this->database.push_back(record);
}


void DefineNoisyChannel::handleMultipleOccurenceOfWord(std::vector<std::string>*spellingErrors){
  char occurenceSeparator = '*';
  for(int i=0; i<spellingErrors->size(); i++){
    std::string word = (*spellingErrors)[i];
    std::vector<std::string> occurenceCount = this->get_tokens(word, occurenceSeparator);
    word = occurenceCount[0];
    if(occurenceCount.size()==2) {
      int occurences = std::stoi(occurenceCount[1]);
      spellingErrors->erase(spellingErrors->begin()+i);
      for(int j=1; j<=occurences; j++) (*spellingErrors).push_back(word);
    } 
  }
}

std::vector<std::string> DefineNoisyChannel::get_tokens(std::string line, char separator){
  std::string token;
  std::vector<std::string> tokens;
  std::stringstream stringStream(line);
  while(std::getline(stringStream,token,separator)) tokens.push_back(token);
  return tokens;
}


void DefineNoisyChannel::printDatabase(){
  std::ofstream file;
  file.open(this->debugFileName);
  
  file<<"Total Words="<<this->database.size()<<std::endl;
  for(int i=0; i<this->database.size(); i++){
    file<<i+1<<") "<<database[i].first<<": ";
    for(int j=0; j<this->database[i].second.size(); j++) file<<database[i].second[j]<<", ";
    file<<std::endl;
  }

  file.close();
}



void addToMatrix(MED med, DefineNoisyChannel dnc){
  dnc.backtracking(med.correction.size(), med.typo.size(), med.direction, med.correction, med.typo);
}

//Overloading
void DefineNoisyChannel::backtracking(int i, int j, int direction[][MAX_WORD_SIZE], std::string A, std::string B){
  if(i<=0 || j<=0) return;
  int a = A[i-1]-'A';
  int b = B[j-1]-'A'; 
  if(a<0 || a>this->number_of_alphabets) return; // We won't handle punctuation errors.
  if(b<0 || b>this->number_of_alphabets) return;

  if(direction[i][j]==INSERTION_RIGHT_ARROW){
    this->insertion_confusion_matrix[a][b]++;
    this->backtracking(i, j-1, direction, A, B);
  }
  else if(direction[i][j]==DELETION_DOWN_ARROW) {
    this->deletion_confusion_matrix[a][b]++;
    this->backtracking(i-1, j, direction, A, B);
  }
  else if(direction[i][j]==SAME_CHARACTER_DIAGONAL_ARROW) this->backtracking(i-1, j-1, direction, A, B);
  else if(direction[i][j]==SUBSTITUTION_DIAGONAL_ARROW){
    this->substitution_confusion_matrix[a][b]++;
    this->backtracking(i-1, j-1, direction, A, B);
  }
  else if(direction[i][j]==TRANSPOSITION_ARROW){
    this->transposition_confusion_matrix[a][b]++;
    this->backtracking(i-2, j-2, direction, A, B);
  }

  return;
}


void DefineNoisyChannel::loadMatrices(){
  for(int i=0; i<this->database.size(); i++){
    for(int j=0; j<this->database[i].second.size(); j++){
      MED med(database[i].first,database[i].second[j]);
      med.domerau_levensthein_edit_distance();
      // addToMatrix(med, *this);
      this->backtracking(med.correction.size(), med.typo.size(), med.direction, med.correction, med.typo);
    }
  }
}

void DefineNoisyChannel::printMatrices(){
  // Insertion Confusion Matrix
  std::ofstream fileStream;
  fileStream.open(insertion_filename);
  for(int i=0; i<this->number_of_alphabets; i++){
    for(int j=0; j<this->number_of_alphabets; j++) fileStream << this->insertion_confusion_matrix[i][j] <<" ";
    fileStream<<std::endl;
  }
  fileStream.close();

  // Deletion Confusion Matrix
  fileStream.open(deletion_filename);
  for(int i=0; i<this->number_of_alphabets; i++){
    for(int j=0; j<this->number_of_alphabets; j++) fileStream << this->deletion_confusion_matrix[i][j] <<" ";
    fileStream<<std::endl;
  }
  fileStream.close();


  // Substitution Confusion Matrix
  fileStream.open(substitution_filename);
  for(int i=0; i<this->number_of_alphabets; i++){
    for(int j=0; j<this->number_of_alphabets; j++) fileStream << this->substitution_confusion_matrix[i][j] <<" ";
    fileStream<<std::endl;
  }
  fileStream.close(); 

  // Transposition Confusion Matrix
  fileStream.open(transposition_filename);
  for(int i=0; i<this->number_of_alphabets; i++){
    for(int j=0; j<this->number_of_alphabets; j++) fileStream << this->transposition_confusion_matrix[i][j] <<" ";
    fileStream<<std::endl;
  }
  fileStream.close(); 

}

void DefineNoisyChannel::test_function(){
  DefineNoisyChannel dnc;
  dnc.loadMatrices();
  dnc.printMatrices();
}

int main(){
  DefineNoisyChannel::test_function();
  return 0;
}
