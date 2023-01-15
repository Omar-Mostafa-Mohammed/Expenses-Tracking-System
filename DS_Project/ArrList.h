#pragma once
#include <assert.h>
template <class T>
class ArrList
{

	T* arr;
	int size, count;
public:
	ArrList();
	int Length();
	void Append(T);
	void Expand();
	T At(int);
	void delArrList();
};
template <class T>
ArrList<T>::ArrList()
{
	size = 50;
	arr = new T[size];
	count = 0;
}

template <class T>
int ArrList<T>::Length()
{
	return count;
}

template <class T>
void ArrList<T>::Append(T val)
{
	if (count == size)
		Expand();
	arr[count] = val;
	count++;
}

template <class T>
void ArrList<T>::Expand()
{
	size *= 2;
	T* tmp = new T[size];
	for (int i = 0; i<count; i++)
		tmp[i] = arr[i];
	delete arr; 
	arr = tmp;
}

template <class T>
T ArrList<T>::At(int pos)
{
	assert(pos<count);
	return arr[pos];
}
template <class T>
void ArrList<T>::delArrList()
{
	delete[] arr;
}