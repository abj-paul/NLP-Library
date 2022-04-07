#include "NoisyChannelModel.h"
using namespace abj;

NoisyChannelModel::NoisyChannelModel(){
  this->load_confusion_matrices();
}

void NoisyChannelModel::load_confusion_matrices(){
  this->extract_content_from_file_into_matrix(new abj::String("INSERTION_CONFUSION_MATRIX.txt"), new abj::String(ID_INSERTION));
  this->extract_content_from_file_into_matrix(new abj::String("DELETION_CONFUSION_MATRIX.txt"),new abj::String(ID_DELETION));
  this->extract_content_from_file_into_matrix(new abj::String("SUBTITION_CONFUSION_MATRIX.txt"), new abj::String(ID_SUBSTITUTION));
  this->extract_content_from_file_into_matrix(new abj::String("TRANSPOSITION_CONFUSION_MATRIX.txt"), new abj::String(ID_TRANSPOSITION));
}

void NoisyChannelModel::extract_content_from_file_into_matrix(abj::String* filename, abj::String* matrix_name){
  FILE *fptr = fopen(filename->get_raw_data(), "r");
  if(fptr==NULL){
    printf("FILE %s not found!\n", filename->get_raw_data());
    exit(1);
  }

  int count=0;
  for(int i=0; i<ALPHABET_SIZE; i++){
    abj::Vector<int> row_value;
    for(int j=0; j<ALPHABET_SIZE; j++){ // According to confusion matrix
      fscanf(fptr, "%d", &count);
      row_value.push(count);
    }
    if(matrix_name->equals(ID_INSERTION)) this->insertion_confusion_matrix.push(row_value);
    else if(matrix_name->equals(ID_DELETION)) this->deletion_confusion_matrix.push(row_value);
    else if(matrix_name->equals(ID_SUBSTITUTION)) this->substitution_confusion_matrix.push(row_value);
    else if(matrix_name->equals(ID_TRANSPOSITION)) this->transposition_confusion_matrix.push(row_value);
  }
  fclose(fptr);
}



void NoisyChannelModel::print_confusion_matrix(abj::Vector<abj::Vector<int>> confusion_matrix, abj::String* filename){
  FILE* fptr = fopen(filename->get_raw_data(), "w");
  if(fptr==NULL){
    printf("Error opening %s!\n",filename->get_raw_data());
    exit(1);
  }
  
  for(int i=0; i<confusion_matrix.size(); i++){
    for(int j=0; j<confusion_matrix[i].size(); j++){
      fprintf(fptr,"%d ",confusion_matrix[i][j]);
    }
    fprintf(fptr,"\n");
  }
  fclose(fptr);
}


double NoisyChannelModel::probablity(abj::String main_word, char separator, abj::String candidate){}

void NoisyChannelModel::test_function(){
  abj::NoisyChannelModel noisyChannelModel;
  noisyChannelModel.print_confusion_matrix(noisyChannelModel.insertion_confusion_matrix, new abj::String("INS_OUTPUT.txt"));
  noisyChannelModel.print_confusion_matrix(noisyChannelModel.deletion_confusion_matrix, new abj::String("DEL_OUTPUT.txt"));
  noisyChannelModel.print_confusion_matrix(noisyChannelModel.substitution_confusion_matrix, new abj::String("SUB_OUTPUT.txt"));
  noisyChannelModel.print_confusion_matrix(noisyChannelModel.transposition_confusion_matrix, new abj::String("TRANS_OUTPUT.txt"));

  //noisyChannelModel.print_vocabulary();
}
