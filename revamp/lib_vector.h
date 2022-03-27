#include<iostream>

#ifndef _LIB_VECTOR_H
#define _LIB_VECTOR_H

namespace abj{
  template<typename T>
class Vector{
	private:
		int current_size;
		int capacity;
		T* storage;
		const int initialization_size = 45;
		void resize(int size);
	public:
	Vector();
	Vector(int size);
	Vector(abj::Vector<T>& initialize_data);

	~Vector();

	void push(T& data);
	// void push(T data);
	void push(abj::Vector<T> new_data);

	void print();

    void operator = (abj::Vector<T>& x);
    void operator = (abj::Vector<T>&& x);
    void operator =(T& data);
    void operator =(T&& data);
    T operator[](int index);

	int size();
	T get(int index);
  bool set(int index, T data);

	static void test_function();
};
}

template<typename T>
abj::Vector<T>::Vector(){
	this->storage = (T*)calloc(this->initialization_size,sizeof(T));	
	this->capacity=this->initialization_size;
	this->current_size=0;
}
template<typename T>
abj::Vector<T>::Vector(int size_){
	this->storage = (T*)calloc(size_,sizeof(T));	
	this->capacity=size_;
	this->current_size=0;
}
template<typename T>
abj::Vector<T>::Vector(abj::Vector<T>& initializer){
	this->storage = (T*)calloc(initializer.size(), sizeof(T));
	this->capacity=initializer.size();

	for(int i=0; i<initializer.size(); i++){
		this->storage[i]=initializer.get(i);
	}
	this->current_size=initializer.size();
}
template<typename T>
abj::Vector<T>::~Vector(){
  if(this->storage!=NULL && this->current_size!=0)free(this->storage);
	this->capacity=0;
	this->current_size=0;
}

template<typename T>
void abj::Vector<T>::push(T& data){
	// if(this->current_size+1>this->capacity){
		// this->resize(this->capacity*2);
	// }
	// this->storage[this->current_size++]=data; // usual
    if(this->current_size+1>=this->capacity){
        T* temp = (T*)calloc(this->capacity*2, sizeof(T));
        this->capacity*=2;

        for(int i=0; i<this->current_size; i++) temp[i]=this->storage[i];
        free(this->storage);
        this->storage=temp;
    }
    this->storage[this->current_size++] = data;

}

// template<typename T>
// void abj::Vector<T>::push(T data){
// 	if(this->current_size+1>this->capacity){
// 		this->resize(this->capacity*2);
// 	}
// 	this->storage[this->current_size++]=data; // usual
// }


// template<typename T>
// void abj::Vector<T>::push(abj::Vector<T> data){
// 	/*
// 	printf("---data size=%d\n",data.size());
// 	data.print();
// 	printf("Our data is fine!\n");
// 	*/
// 	if(data.size()+this->current_size>this->capacity)
// 		this->resize(data.size()+this->current_size);	
// 	int j=0;
// 	for(int i=this->current_size; i<this->capacity && j<data.size(); i++, j++){
// 		this->storage[i]=data.get(j);	
// 		//printf("%d) %s\n",i+1,this->storage[i]);
// 	}

// 	this->current_size = data.size()+this->current_size;
// }

template<typename T>
T abj::Vector<T>::get(int index){
  if(this->current_size==0) return NULL;
  if(index<0 || index>=this->current_size) {
    printf("Vector index out of bound!\n");
    return 0;
  }
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
int abj::Vector<T>::size(){
	return this->current_size;
}


template<typename T>
bool abj::Vector<T>::set(int index, T data){
  if(index>=this->current_size){
    printf("Vector Error! Can not set(%d)! Current size is %d.\n",index,this->current_size);
    return false;
  }
  this->storage[index]=data;
  return true;
}
template<typename T>
// A = B, Create new A and B
void abj::Vector<T>::operator=(abj::Vector<T>& data){
  // printf("The operator function is being used!\n");
  if(this==&data) return ;
  //this->~Vector();
  //this->resize(data.size());
  //free(this->storage);
  this->storage = (T*)calloc(data.size(), sizeof(T));
  for(int i=0; i<data.size(); i++) {
    T ref = data.get(i);
    this->storage[i]=ref;
  }
  this->current_size = data.size();
}

template<typename T>
void abj::Vector<T>::operator = (T& data){
  if(current_size+1>=this->capacity) resize(this->capacity*2);
  this->storage[this->current_size]=data;
  this->current_size++;
}

template<typename T>
void abj::Vector<T>::operator=(abj::Vector<T>&& data){
  // printf("The operator function is being used!\n");
  if(this==&data) return ;
  this->~Vector();
  //this->resize(data.size());
  this->storage = (T*)calloc(data.size(), sizeof(T));
  for(int i=0; i<data.size(); i++) {
    T ref = data.get(i);
    this->storage[i]=ref;
  }
  this->current_size = data.size();
}

template<typename T>
void abj::Vector<T>::operator = (T&& data){
  if(current_size+1>=this->capacity) resize(this->capacity*2);
  this->storage[this->current_size]=data;
  this->current_size++;
}


template<typename T>
T abj::Vector<T>::operator[](int index){
  if(index<0 || index>=this->current_size) {
    printf("Vector Out of index!\n");
    return NULL;
  }
  return this->storage[index];
}


template<typename T>
void abj::Vector<T>::test_function(){
printf("Testing Vector----------------------\n");
	abj::Vector<char*> x;
	abj::Vector<char*> y;

	char* a = "Abhi";
	char* b = "Jit";
	char* c = "Paul";

	x.push(a);
	x.push(b);
	x.push(c);

	x.print();

	// y.push(x);
	// y.print();
	// y.push("Empire!");

	abj::Vector<const char*> z(x);
	z.print();
}



#endif
