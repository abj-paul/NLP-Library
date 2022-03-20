
#include<iostream>
#include "lib_vector.h"
#include "lib_string.h"


int main(){
  abj::String a("Abhi");
  abj::String b("Jit");
  abj::String c("Paul");

  abj::Vector<abj::String> v0;
  v0.push(a);
  v0.push(b);
  v0.push(c);

  //for(int i=0; i<v.size(); i++) v.get(i).print();

  abj::Vector<abj::String> v1;
  v1.push(a);
  v1.push(b);
  v1.push(c);


  printf("Started pushing to storehouse!\n");
  abj::Vector<abj::Vector<abj::String>> storehouse;
  storehouse.push(v0);
  storehouse.push(v1);

  printf("Printing storehouse:\n");
  for(int i=0; i<storehouse.size(); i++){
    for(int j=0; j<storehouse.get(i).size(); j++){
      storehouse.get(i).get(j).print();
    }
  }

  return 0;
}
