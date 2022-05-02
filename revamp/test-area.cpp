#include<iostream>

int main(){
  char str[] = "I am only human!";
  std::string s =  "I am only human!";

  int size = 0;
  while(str[size++]!='\0') size++;
  std::cout<<size<<" "<<s.size()<<std::endl;
  for(int i=0; i<s.size(); i++){
    if(str[i]=='\0') printf("NULL");
    else printf("%c",str[i]);
  }
  printf("\n");
  return 0;
}
