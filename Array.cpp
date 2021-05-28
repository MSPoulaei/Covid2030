#pragma once
#include "Array.h"
template<typename T>
Array<T>::Array(int max_siz , int add_siz) : max_size(max_siz), add_size(add_siz), size_num(0) {
	arr = new T[max_size];
}
template<typename T>
void Array<T>::push_back(const T& v) {
	if (size_num == max_size) {
		max_size += add_size;
		T* arra = new T[max_size];
		for (int i = 0; i < size_num; i++)
			arra[i] = arr[i];
		arr = arra;
	}
	arr[size_num++] = T(v);// copy constructor
}

template<typename T>
void Array<T>::erase(const int& index) {
	for (int i = index; i < size_num - 1; i++)
		arr[i] = arr[i + 1];
	size_num--;
}
template<typename T>
int Array<T>::size() {
	return size_num;
}
template<typename T>
void Array<T>::clear() {
	size_num = 0;
}
template<typename T>
void Array<T>::operator=(const Array<T>& v) {
	this->size_num = v.size_num;
	this->arr = v.arr;
}
template<typename T>
T& Array<T>::operator[](const int& index) {
	return arr[index];
}
template<typename T>
int Array<T>::begin() { return 0; }
template<typename T>
int Array<T>::end() { return size_num - 1; }