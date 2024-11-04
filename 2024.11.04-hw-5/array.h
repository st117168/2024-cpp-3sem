#ifndef ARRAY_H
#define ARRAY_H

#include<iostream>

template <class T>
class Array
{
	static const size_t size = 5;
	T array[size]{ 0 };
public:
	Array() {};
	Array(T* b);
	void show();
	T& minimum(Array<T>& m);
};

template<class T>
inline Array<T>::Array(T* b)
{
	for (int i = 0; i < size; ++i)
	{
		array[i] = b[i];
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
	T& minEl = m.array[0];
	for (T& el : m.array)
	{
		minEl = (el < minEl ? el : minEl);
	}
	return minEl;
}

#endif