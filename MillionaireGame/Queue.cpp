#include "Queue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <cstdlib>
#include <ctime>

template <class T>
Queue<T>::Queue()
{
	Size = 5;
	Count = 0;
	Front = Back = -1;
	Array = new T[Size];
}

template <class T>
void Queue<T>::Enqueue(T Value)
{
	if (Count == Size)
		Expand();

	if (Count == 0)
		Front = 0;

	Back = (Back + 1) % Size;
	Array[Back] = Value;
	
	Count++;
}

template <class T>
void Queue<T>::Dequeue()
{
	assert(!IsEmpty());

	if (Count == 1)
		Front = Back = -1;
	else
		Front = (Front + 1) % Size;
	Count--;
}

template<class T>
void Queue<T>::Expand()
{
	int TemporaryCount = Count;
	T*TemporaryArray = new T[Size * 2];

	for (int i = 0; i < Size; i++)
	{
		TemporaryArray[i] = Array[Front];
		Dequeue();
	}

	Front = 0;
	Back = Size - 1;
	Size *= 2;

	delete[] Array;
	Array = TemporaryArray;
	Count = TemporaryCount;
}

template <class T>
T Queue<T>::FrontElement()
{
	assert(!IsEmpty());
	return Array[Front];
}

template <class T>
int Queue<T>::Length()
{
	return Count;
}

template <class T>
bool Queue<T>::IsEmpty()
{
	return (Count == 0);
}

template <class T>
void Queue<T>::Sort()
{
	for (int IndexOne = 0; IndexOne < Count; IndexOne++) {
		for (int IndexTow = 0; IndexTow < Count - 1; IndexTow++)
		{
			if (Array[IndexTow] < Array[IndexTow + 1])
			{
				T Temporary = Array[IndexTow];
				Array[IndexTow] = Array[IndexTow + 1];
				Array[IndexTow + 1] = Array[IndexTow];
			}
		}
	}
}

template <class T>
void Queue<T>::Shuffle()
{
	srand((int)time(0));

	for (int IndexOne = 0 ; IndexOne < Count-1; IndexOne++) 
	{
		int IndexTwo = IndexOne + rand() % (Count - IndexOne);
		
		T Temporary     = Array[IndexTwo];
		Array[IndexTwo] = Array[IndexOne];
		Array[IndexOne] = Temporary;
	}

}

template <class T>
void Queue<T>::Clear()
{
	if (Count == 0)
		return;

	delete[] Array;

	Size = 5;
	Count = 0;
	Front = Back = -1;
	Array = new T[Size];
}

template <class T>
Queue<T>::~Queue()
{
	delete[] Array;
}
