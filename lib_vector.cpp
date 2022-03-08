#include "lib_vector.h"
template<typename T>
abj::VecTor::VecTor(){
	this->storage = (T*)calloc(this->initialization_size,sizeof(T));	
	this->capacity=this->initialization_size;
	this->current_size=0;
}
/*
template<typename T>
abj::VecTor::VecTor(int size){
	this->storage = (T*)calloc(size,sizeof(T));	
	this->capacity=size;
	this->current_size=0;
}
template<typename T>
abj::VecTor::VecTor(abj::VecTor<T> initializer){
	this->storage = (T*)calloc(initializer.getSize(), sizeof(T));
	this->capacity=initializer.getSize();

	for(int i=0; i<initializer.getSize(); i++){
		T[i]=initializer[i];
	}
	this->current_size=initializer.getSize();
}
template<typename T>
abj::VecTor::~VecTor(){
	free(this->storage);
	this->capacity=0;
	this->current_size=0;
}

template<typename T>
void abj::VecTor::push(T data){
	this->current_size++;
	if(this->current_size>this->capacity){
		this->resize(this->capacity*2);
	}

	this->storage[this->current_size-1]=data;
}

template<typename T>
void abj::VecTor::push(abj::VecTor<T> data){
	if(data.getSize()+this->current_size>this->capacity){
		this->resize(data.getSize()+this->current_size)	
	}
	for(int i=this->current_size, j=0; i<this->capacity, j<data.getSize(); i++, j++){
		this->storage[i]=data[j];	
	}
}

template<typename T>
void abj::VecTor::resize(int size){
	T* temp = (T*)calloc(size,sizeof(T));
	this->capacity = size;

	for(int i=0; i<this->current_size; i++){
		temp[i]=this->storage[i];
	}
	
	free(this->storage);
	this->storage = temp;
	this->current_size = this->current_size;
	
}

template<typename T>
void abj::VecTor::print(){
  for(int i=0; i<this->current_size; i++) printf("%d,",this->storage[i]);
  printf("\n");
}*/

void test_function(){
  abj::VecTor<int>* v = new abj::VecTor();
  //v->print();
}

int main(){
  return 0;
}
