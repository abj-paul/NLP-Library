#include "lib_vector.h"

abj::Vector::Vector(){
	this->storage = (T*)calloc(this->initialization_size,sizeof(T));	
	this->capacity=this->initialization_size;
	this->current_size=0;
}

abj::Vector::Vector(int size){
	this->storage = (T*)calloc(size,sizeof(T));	
	this->capacity=size;
	this->current_size=0;
}
abj::Vector::Vector(abj::Vector<T> initializer){
	this->storage = (T*)calloc(initializer.getSize(), sizeof(T));
	this->capacity=initializer.getSize();

	for(int i=0; i<initializer.getSize(); i++){
		T[i]=initializer[i];
	}
	this->current_size=initializer.getSize();
}
abj::Vector::~Vector(){
	free(this->storage);
	this->capacity=0;
	this->current_size=0;
}

void abj::Vector::push(T data){
	this->current_size++;
	if(this->current_size>this->capacity){
		this->resize(this->capacity*2);
	}

	this->storage[this->current_size-1]=data;
}

void abj::Vector::push(abj::Vector<T> data){
	if(data.getSize()+this->current_size>this->capacity){
		this->resize(data.getSize()+this->current_size)	
	}
	for(int i=this->current_size, j=0; i<this->capacity, j<data.getSize(); i++, j++){
		this->storage[i]=data[j];	
	}
}

void abj::Vector::resize(int size){
	T* temp = (T*)calloc(size,sizeof(T));
	this->capacity = size;

	for(int i=0; i<this->current_size; i++){
		temp[i]=this->storage[i];
	}
	
	free(this->storage);
	this->storage = temp;
	this->current_size = this->current_size;
	
}
