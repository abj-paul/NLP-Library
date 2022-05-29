#include<iostream>

namespace abj{
template<typename T> class VecTor{
 private:
  T* storage;
  int current_size;
  int capacity;

  void resize(int size);
 public:
  VecTor();
  VecTor(int size);
  VecTor(abj::VecTor<T>& initializer);

  ~VecTor();

  void push(T data);
  void push(abj::VecTor<T> data);

  void print();
 };
}
