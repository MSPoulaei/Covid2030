
#ifndef _ARRAY_
#define _ARRAY_
//#ifndef _UTILITIES_
#include "Utilities.h"
//#endif
template<typename T>
class Array {
private:
	int max_size;
	int add_size;
	int size_num;
	T* arr = new T[max_size];
public:
	Array(int max_siz = 30, int add_siz = 30) :max_size(max_siz), add_size(add_siz), size_num(0) {}
	//~Array() { delete[] arr; }
	void push_back(const T& v) {
		if (size_num == max_size) {
			max_size += add_size;
			T* arra = new T[max_size];
			for (int i = 0; i < size_num; i++)
				arra[i] = arr[i];
			arr = arra;
		}
		arr[size_num++] = T(v);// copy constructor
	}
	void erase(const int& index) {
		for (int i = index; i < size_num - 1; i++)
			arr[i] = arr[i + 1];
		size_num--;
	}
	int size() {
		return size_num;
	}
	void clear() {
		size_num = 0;
	}
	T& operator[](const int& index) {
		return arr[index];
	}
	void operator=(const Array<T>& v) {
		this->size_num = v.size_num;
		this->arr = v.arr;
	}
	int begin() { return 0; }
	int end() { return size_num - 1; }
};
#endif
