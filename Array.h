
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
	T* arr;
public:
	Array(int = 30, int = 30);
	void push_back(const T&);
	void erase(const int&);
	int size();
	void clear();
	T& operator[](const int&);
	void operator=(const Array<T>&);
	int begin();
	int end();
};
#endif
