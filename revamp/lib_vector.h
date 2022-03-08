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

	void push(T data);
	void push(abj::Vector<T> new_data);

	void print();

	int getSize();
	T get(int index);
};
}
#endif
