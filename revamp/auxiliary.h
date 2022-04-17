#ifndef _AUXILIARY_H
#define _AUXILIARY_H
  #define INT_INITIALIZE_VALUE 1000

char capitalize(char c){
  int offset = 'a'-'A';
  if(c>='a' && c<='z') c = c - offset;
  return c;
}

#endif
