#ifndef ARRAY_H
#define ARRAY_H

#include<iostream>

template <class T>
class Array
{
	static const size_t kSize = 5;
	T array[kSize]{ 0 };
public:
	Array() {};
	Array(T* b, size_t size);
	void show();
	T& minimum(Array<T>& m);
};

template<class T>
inline Array<T>::Array(T* b, size_t size)
{
	size_t i = 0;
	while (i < size && i < kSize)
	{
		array[i] = b[i];
		++i;
	}
}

template<class T>
void Array<T>::show()
{
	for (T& el : array)
	{
		std::cout << el << " ";
	}
	std::cout << '\n';
}

template<class T>
T& Array<T>::minimum(Array<T>& m)
{
	T& min_elem = m.array[0];
	for (T& el : m.array)
	{
		min_elem = (el < min_elem ? el : min_elem);
	}
	return min_elem;
}

#endif