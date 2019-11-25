#pragma once

template <class T>
class Queue
{
	T* Array;
	int Count, Size;
	int Front, Back;

public:
	Queue();

	void Enqueue(T);
	void Dequeue();
	void Expand();

	T FrontElement();
	int Length();
	bool IsEmpty();

	void Sort();     // This Aded Function That Automaticaly Sort The Queue
	void Shuffle();  // This The Added Function That Automaticaly Randomize The Queue 
	void Clear();

	~Queue();
};

