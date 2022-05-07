#include <iostream>
#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace abj{
template<typename T>
class Vector {
public:
  Vector();
  
  void push(const T &data);
  
  [[nodiscard]] int size() const;

  T& operator[](int pos) const;
  bool set(int index, T data);

  void reverse();

  ~Vector();
private:
  T *storage = nullptr;
  int capacity;
  int curr_size;
  const int initialization_size = 70000;
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
    if (curr_size < capacity-1) {
        *(storage + curr_size) = data;
        curr_size++;
    } else {
      printf("Resized to %d\n",capacity*3);
      storage = (T*)realloc(storage, sizeof(T) * this->capacity* 3);
      this->capacity*= 3;
	
      if (storage) {
	*(storage + curr_size) = data;
	curr_size++;
      }
    }
}


template<typename T>
T &Vector<T>::operator[](int pos) const{
    if (pos >= 0 &&  pos < curr_size)
        return *(this->storage + pos);
    throw std::out_of_range("Out of bounds element access");
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
bool Vector<T>::set(int index, T data){
  if(this->curr_size>index && index>=0){
    this->storage[index] = data;
    return true;
  }
  else{ 
    throw std::out_of_range("Out of bounds element access on Set method");
    return false;
  }
}
}
// abj::Vector<abj::String>& abj::Vector=(const abj::Vector<abj::String>&)

#endif
