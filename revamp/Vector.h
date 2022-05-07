#include <iostream>
#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace abj{
template<typename T>
class Vector {
public:
  Vector();
  
  void push(const T &data);
  void pop();
  
  [[nodiscard]] bool empty() const;
  [[nodiscard]] int size() const;
  [[nodiscard]] int getCapacity() const;

  T& operator[](int pos) const;
  bool set(int index, T data);
  T& get(int index) const;

  void reverse();
  void print() const;

  ~Vector();
  Vector(const abj::Vector<T>& data);
  [[nodiscard]] abj::Vector<T>& operator=(const abj::Vector<T>& data);
  void swap(abj::Vector<T>& data);

  [[nodiscard]] T* getStorage() const;
  void setStorage(T* newStorage);
  void setSize(int size);
private:
  T *storage = nullptr;
  int capacity;
  int curr_size;
  const int initialization_size = 20;
};

template<typename T>
Vector<T>::Vector() {
    capacity = this->initialization_size;
    storage = (T*)malloc(sizeof(T) * this->initialization_size);
    curr_size = 0;
  };

template<typename T>
Vector<T>::~Vector() {
    free(storage);
}
template<typename T>
void Vector<T>::push(const T &data) {
    if (curr_size < capacity) {
        *(storage + curr_size) = data;
        curr_size++;
    } else {
        storage = (T*)realloc(storage, sizeof(T) * capacity* 2);
        capacity*= 2;
	
        if (storage) {
	  *(storage + curr_size) = data;
	  curr_size++;
        }
    }
}

template<typename T>
void Vector<T>::pop() {
    if (empty())
        return;
    curr_size--;
}

template<typename T>
T &Vector<T>::operator[](int pos) const{
    if (pos >= 0 &&  pos < curr_size)
        return *(this->storage + pos);
    throw std::out_of_range("Out of bounds element access");
}
  
template<typename T>
T& Vector<T>::get(int pos) const{
  if (pos >= 0 &&  pos < curr_size)
    return *(this->storage + pos);
  throw std::out_of_range("Out of bounds element access");
}
template<typename T>
int Vector<T>::getCapacity() const {
  return capacity;
}

template<typename T>
bool Vector<T>::empty() const {
    return curr_size == 0;
}

template<typename T>
int Vector<T>::size() const {
    return curr_size;
}
template<typename T>
void Vector<T>::reverse(){
  int start = 0;
  int end = this->curr_size-1;
  while (start < end){
        T temp = this->storage[start];
        storage[start] = storage[end];
        storage[end] = temp;
        start++;
        end--;
    } 
}

template<typename T>
void abj::Vector<T>::print() const{
  printf("Printing vector:\n");
  for(int i=0; i<this->curr_size; i++){
    std::cout<<this->storage[i]<<" ";
  }
  std::cout<<std::endl;
}

template<typename T>
bool Vector<T>::set(int index, T data){
  if(this->curr_size>index && index>=0)
    this->storage[index] = data;
  else 
    throw std::out_of_range("Out of bounds element access on Set method");
}
template<typename T>
T* Vector<T>::getStorage() const{
  return this->storage;
}
  
template<typename T>
void Vector<T>::setStorage(T* newStorage){
  this->storage = newStorage;
}
template<typename T>
void Vector<T>::setSize(int size){
  this->curr_size = size;
}
  
template<typename T>
Vector<T>::Vector(const abj::Vector<T>& data){
  capacity = data.size();
  storage = (T*)malloc(sizeof(T) * this->capacity);
  for(int i=0; i<data.size(); i++) this->storage[i] = data[i];
  this->curr_size = data.size();
}
template<typename T>
abj::Vector<T>& Vector<T>::operator=(const abj::Vector<T>& data){
  if(this!=&data){
    abj::Vector<T> temp(data);
    this->swap(temp);
  }
  return *this;

}
template<typename T>
void Vector<T>::swap(abj::Vector<T>& data){
  T* temp_storage = data.getStorage();
  data.setStorage(this->storage);
  this->storage = temp_storage;
  
  int temp_size = data.size();
  data.setSize(this->size());
  this->curr_size = temp_size;
}

}


#endif
