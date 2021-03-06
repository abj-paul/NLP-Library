#include "lib_vector.h"

template<typename T>
abj::Vector<T>::Vector(){
	this->storage = (T*)calloc(this->initialization_size,sizeof(T));	
	this->capacity=this->initialization_size;
	this->current_size=0;
}
template<typename T>
abj::Vector<T>::Vector(int size){
	this->storage = (T*)calloc(size,sizeof(T));	
	this->capacity=size;
	this->current_size=0;
}
template<typename T>
abj::Vector<T>::Vector(abj::Vector<T>& initializer){
	this->storage = (T*)calloc(initializer.getSize(), sizeof(T));
	this->capacity=initializer.getSize();

	for(int i=0; i<initializer.getSize(); i++){
		this->storage[i]=initializer.get(i);
	}
	this->current_size=initializer.getSize();
}
template<typename T>
abj::Vector<T>::~Vector(){
	free(this->storage);
	this->capacity=0;
	this->current_size=0;
}

template<typename T>
void abj::Vector<T>::push(T data){
	this->current_size++;
	if(this->current_size>this->capacity){
		this->resize(this->capacity*2);
	}

	this->storage[this->current_size-1]=data;
}

template<typename T>
void abj::Vector<T>::push(abj::Vector<T> data){
	/*
	printf("---data size=%d\n",data.getSize());
	data.print();
	printf("Our data is fine!\n");
	*/
	if(data.getSize()+this->current_size>this->capacity)
		this->resize(data.getSize()+this->current_size);	
	int j=0;
	for(int i=this->current_size; i<this->capacity && j<data.getSize(); i++, j++){
		this->storage[i]=data.get(j);	
		//printf("%d) %s\n",i+1,this->storage[i]);
	}

	this->current_size = data.getSize()+this->current_size;
}

template<typename T>
T abj::Vector<T>::get(int index){
	return this->storage[index];
}

template<typename T>
void abj::Vector<T>::resize(int size){
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
void abj::Vector<T>::print(){
	printf("Printing vector:\n");
	for(int i=0; i<this->current_size; i++){
		std::cout<<this->storage[i]<<" ";
	}
	std::cout<<std::endl;
}

template<typename T>
int abj::Vector<T>::getSize(){
	return this->current_size;
}

int main(){
	abj::Vector<const char*> x;
	abj::Vector<const char*> y;

	char a[] = "Abhi";
	char b[] = "Jit";
	char c[] = "Paul";

	x.push(a);
	x.push(b);
	x.push(c);

	x.print();

	y.push(x);
	y.print();
	y.push("Empire!");

	abj::Vector<const char*> z(y);
	z.print();
return 0;
}
