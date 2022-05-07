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
    const int initialization_size = 2;
    void resize(int size);
  public:
    Vector();
    Vector(int size);
    Vector(const abj::Vector<T>& initialize_data);

    ~Vector();

    void push(T& data);
    void push(T&& data);
    void push(abj::Vector<T>& new_data);

    void reverse();
    void print() const;

    abj::Vector<T>& operator= (const abj::Vector<T>& data);
    T operator[](int index) const;
    void swap(const abj::Vector<T>& data);

    int size() const;
    T get(int index) const;
    bool set(int index, T data);

    T* getStorage() const;
    void setStorage(T* newStorage);
    void setSize(int size);

    friend void test_function();
  };
}

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
abj::Vector<T>::Vector(const abj::Vector<T>& initializer){ // copy constructor, deep copy
	this->storage = (T*)calloc(initializer.size(), sizeof(T));
	this->capacity=initializer.size();

	for(int i=0; i<initializer.size(); i++){
		this->storage[i]=initializer.get(i);
	}
	this->current_size=initializer.size();
}
template<typename T>
abj::Vector<T>::~Vector(){
  printf("Calling vector destructor. Did you destroy its elements before? :)\n");
  if(this->storage!=NULL && this->current_size!=0)
    {
      // for(int i=0; i<this->current_size; i++) free(storage[i]);
      free(this->storage);
      this->storage = NULL;
    }
  this->capacity=0;
  this->current_size=0;
}

template<typename T>
void abj::Vector<T>::push(T& data){
    if(this->current_size+1>=this->capacity){
        T* newStorage = (T*)calloc(this->capacity*2, sizeof(T));
        this->capacity*=2;

        for(int i=0; i<this->current_size; i++) newStorage[i]=this->storage[i];
        free(this->storage);
        this->storage=newStorage;
    }
    this->storage[this->current_size] = data;
    this->current_size++;
}
template<typename T>
void abj::Vector<T>::push(T&& data){
    if(this->current_size+1>=this->capacity){
        T* temp = (T*)calloc(this->capacity*2, sizeof(T));
        this->capacity*=2;

        for(int i=0; i<this->current_size; i++) temp[i]=this->storage[i];
        free(this->storage);
        this->storage=temp;
    }
    this->storage[this->current_size] = data;
    this->current_size++;
}


// template<typename T>
// void abj::Vector<T>::push(T data){
// 	if(this->current_size+1>this->capacity){
// 		this->resize(this->capacity*2);
// 	}
// 	this->storage[this->current_size++]=data; // usual
// }


template<typename T>
void abj::Vector<T>::push(abj::Vector<T>& data){
	/*
	printf("---data size=%d\n",data.size());
	data.print();
	printf("Our data is fine!\n");
	*/
	if(data.size()+this->current_size>=this->capacity)
		this->resize(data.size()+this->current_size);	
	int j=0;
	for(int i=this->current_size; i<this->capacity && j<data.size(); i++, j++){
		this->storage[i]=data.get(j);	
		//printf("%d) %s\n",i+1,this->storage[i]);
	}

	this->current_size = data.size()+this->current_size;
}

template<typename T>
T abj::Vector<T>::get(int index) const{
  if(this->current_size==0) {
    printf("Vector does not exist so can not access index %d!Exiting...\n",index);
    exit(1);//return NULL;
  }
  if(index<0 || index>=this->current_size) {
    printf("Vector index %d out of bound as vector size is %d!Exiting....\n",index, this->current_size);
    exit(1);
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
void abj::Vector<T>::print() const{
  printf("Printing vector:\n");
  for(int i=0; i<this->current_size; i++){
    std::cout<<this->storage[i]<<" ";
  }
  std::cout<<std::endl;
}

template<typename T>
int abj::Vector<T>::size() const{
  return this->current_size;
}


template<typename T>
bool abj::Vector<T>::set(int index, T data){
  if(index>=this->current_size){
    printf("Vector Error! Can not set data to index %d as Current size is %d.\n",index,this->current_size);
    return false;
  }
  this->storage[index]=data;
  return true;
}
template<typename T>
// A = B, Create new A and B
abj::Vector<T>& abj::Vector<T>::operator=(const abj::Vector<T>& data){
  // printf("The operator function is being used!\n");
  if(this==&data) return *this;

  abj::Vector<T> temp(data);
  this->swap(temp);
  return *this;
//   this->~Vector();

//   this->storage = (T*)calloc(data.size(), sizeof(T));
//   for(int i=0; i<data.size(); i++) {
//     T ref = data.get(i);
//     this->storage[i]=ref;
//   }
//   this->current_size = data.size();
}

template<typename T>
void abj::Vector<T>::swap(const abj::Vector<T>& data){
  T* temp_storage = data.getStorage();
  data.setStorage(this->storage);
  this->storage = temp_storage;

  int temp_size = data.size();
  data.setSize(this->size());
  this->curr_size = temp_size;
}
// template<typename T>
// void abj::Vector<T>::operator = (T& data){
//   if(current_size+1>=this->capacity) resize(this->capacity*2);
//   this->storage[this->current_size]=data;
//   this->current_size++;
// }

// template<typename T>
// void abj::Vector<T>::operator=(abj::Vector<T>&& data){
//   // printf("The operator function is being used!\n");
//   if(this==&data) return ;
//   this->~Vector();
//   //this->resize(data.size());
//   this->storage = (T*)calloc(data.size(), sizeof(T));
//   for(int i=0; i<data.size(); i++) {
//     T ref = data.get(i);
//     this->storage[i]=ref;
//   }
//   this->current_size = data.size();
// }

// template<typename T>
// void abj::Vector<T>::operator = (T&& data){
//   if(current_size+1>=this->capacity) resize(this->capacity*2);
//   this->storage[this->current_size]=data;
//   this->current_size++;
// }


template<typename T>
T abj::Vector<T>::operator[](int index) const{
  if(index<0 || index>=this->current_size) {
    printf("\n[] : Vector Out of index!\n");
    // return 0;
    exit(1);
  }
  return this->storage[index];
}

template<typename T>
T* abj::Vector<T>::getStorage() const{
  return this->storage;
}
template<typename T>
void abj::Vector<T>::setStorage(T* newStorage){
  free(this->storage);
  this->storage = newStorage;
}

template<typename T>
void abj::Vector<T>::setSize(int size){
  this->current_size = size;
}


template<typename T>
void abj::Vector<T>::reverse(){
  T* new_storage = (T*)calloc(this->capacity, sizeof(T));

  int j=0;
  for(int i=this->current_size-1; i>=0; i--, j++){
    new_storage[j]=this->storage[i];
  }
  free(this->storage);
  this->storage = new_storage;
}


#endif
