#include "DefineNoisyChannel.h"

DefineNoisyChannel::DefineNoisyChannel(){
  this->load_file();
  this->printDatabase();
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

  std::string mainWord = portions[0];

  char wordSeparator = ',';
  std::vector<std::string> spellingErrors = this->get_tokens(portions[1], wordSeparator);
  RECORD record = make_pair(mainWord,spellingErrors);
  this->database.push_back(record);
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
