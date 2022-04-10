#pragma once
#include <iostream>
#include "queue.h"
#include "myExceptions.h"

//using std::cout;

template <class T>
class arrayQueue :
	public queue<T>
{
protected:
	T* queue;
	int arrayLength;
	int theBack;
	int theFront;

public:
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { delete[] queue; }
	bool empty()const { return theBack == theFront; }
	int size()const { return (theBack - theFront + arrayLength) % arrayLength; }
	T& back() { if (theBack == theFront) throw queueEmpty(); return queue[theBack]; }
	T& front() { if (theBack == theFront) throw queueEmpty(); return queue[(theFront + 1) % arrayLength]; }
	void pop();
	void push(const T& theElement);
};

template<class T>
inline arrayQueue<T>::arrayQueue(int initialCapacity)
{
	if (initialCapacity < 1)
		throw illegalParameterValue("initial capacity must be > 0");
	arrayLength = initialCapacity;
	queue = new T[arrayLength];
	theFront = 0;
	theBack = 0;
}

template<class T>
inline void arrayQueue<T>::pop()
{
	if (theBack == theFront)
		throw queueEmpty();
	theFront = (theFront + 1) % arrayLength;
	queue[theFront].~T();
}

template<class T>
inline void arrayQueue<T>::push(const T & theElement)
{
	if ((theBack + 1) % arrayLength == theFront)
	{
		T* newQueue = new T[2 * arrayLength];
		int start = (theFront + 1) % arrayLength;//start指向第一个元素位置，而不是第一个元素前一位
		if (start < 2)
			copy(queue + start, queue + start + arrayLength - 1, newQueue);//-1是为了避免start是1时导致的数组越界,start=0时则可以少复制队列中的空位
		else
		{
			copy(queue + start, queue + arrayLength, newQueue);
			copy(queue, queue + theBack + 1, newQueue + arrayLength - start);//+1是因为copy函数首尾是左闭右开
		}
		/*copy(queue + start, queue + arrayLength, newQueue);//这种写法更简洁，但是可读性差一点，并且多复制了空位，效率上差一点点
		if (start > 1)
			copy(queue, queue + theBack + 1, newQueue + arrayLength - start);*/
		theFront = 2 * arrayLength - 1;
		theBack = arrayLength - 2;
		arrayLength *= 2;
		delete[] queue;
		queue = newQueue;
	}
	theBack = (theBack + 1) % arrayLength;
	queue[theBack] = theElement;
}
