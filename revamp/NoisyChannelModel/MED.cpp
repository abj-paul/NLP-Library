#include "MED.h"

MED::MED(std::string correction, std::string typo){
  this->correction = correction;
  this->typo = typo;
}

void MED::domerau_levensthein_edit_distance(){
  for (auto & c: correction) c = toupper(c);
  for (auto & c: typo) c = toupper(c);
  
  // Converting A to B
  for(int i=0; i<=correction.size(); i++) {
    m_distance[i][0]=i;
    direction[i][0]=DELETION_DOWN_ARROW;
  }
  for(int j=0; j<=typo.size(); j++){
    direction[0][j]=INSERTION_RIGHT_ARROW;
    m_distance[0][j]=j;
  }
  direction[0][0]=NO_OPERATION;
  m_distance[0][0]=0;

  int cost=0;
  // A,B indexing starts from 1 and m's indexing starts from 0 according to the algorithm. But our A,B starts from 0. So to compensate that, we start from 1 in the loop but subtract 1 (i-1 or j-1) when accessing A or typo.
  for(int i=1; i<=correction.size(); i++){
    for(int j=1; j<=typo.size(); j++){
      if(correction[i]==typo[j]) cost=0;
      else cost=1;

      m_distance[i][j] = std::min(m_distance[i-1][j]+1,                //deletion
			std::min(m_distance[i][j-1]+1,       //insertion
				 m_distance[i-1][j-1]+cost));//substitution
      // Direction
      if(m_distance[i][j]==m_distance[i-1][j]+1) direction[i][j]=DELETION_DOWN_ARROW;
      else if(m_distance[i][j]==m_distance[i][j-1]+1) direction[i][j]=INSERTION_RIGHT_ARROW;
      else if(m_distance[i-1][j-1]==m_distance[i][j]) direction[i][j]=SAME_CHARACTER_DIAGONAL_ARROW;
      else if(m_distance[i-1][j-1]+1==m_distance[i][j]) direction[i][j]=SUBSTITUTION_DIAGONAL_ARROW;
      
      if(i>1 && j>1 && correction[i-1]==typo[j-1-1] && correction[i-1-1]==typo[j-1]){
	m_distance[i][j] = std::min(m_distance[i][j], m_distance[i-2][j-2]+1); //transposition
	if(m_distance[i][j]==m_distance[i-2][j-2]+1) direction[i][j] = TRANSPOSITION_ARROW;
      }
    }
  }
}

void MED::backtracking(int i, int j){
  if(i<0 || j<0) return;
  backtrack_path.push_back(direction[i][j]);
  
  if(direction[i][j]==INSERTION_RIGHT_ARROW){
    // weight_matrix+=weight[][];
    this->backtracking(i, j-1);
  }
  else if(direction[i][j]==DELETION_DOWN_ARROW) this->backtracking(i-1, j);
  else if(direction[i][j]==SAME_CHARACTER_DIAGONAL_ARROW) this->backtracking(i-1, j-1);
  else if(direction[i][j]==SUBSTITUTION_DIAGONAL_ARROW) this->backtracking(i-1, j-1);
  else if(direction[i][j]==TRANSPOSITION_ARROW) this->backtracking(i-2, j-2);

  return;
}

void MED::print_direction(){
  std::cout<<"A: "<<this->correction<<std::endl;
  std::cout<<"B: "<<this->typo<<std::endl;
  for(int i=0; i<=correction.size(); i++){
    for(int j=0; j<=typo.size(); j++){
      print_med_direction(direction[i][j]);
    }
    printf("\n");
  }
}
void MED::print_med_direction(int direction_Value){
      if(direction_Value==INSERTION_RIGHT_ARROW) printf("IN ");
      else if(direction_Value==DELETION_DOWN_ARROW) printf("DW ");
      else if(direction_Value==SAME_CHARACTER_DIAGONAL_ARROW) printf("SM ");
      else if(direction_Value==SUBSTITUTION_DIAGONAL_ARROW) printf("ST ");
      else if(direction_Value==TRANSPOSITION_ARROW) printf("TP ");
      else if(direction_Value==NO_OPERATION) printf("NA ");
      else printf("Error! ");
}

void MED::test_function(){
  std::string correction = "Elephant";
  std::string typo = "Elephunt";

  MED med(correction, typo);
  med.domerau_levensthein_edit_distance();
  med.print_direction();
}

int main(){
  MED::test_function();
  return 0;
}
