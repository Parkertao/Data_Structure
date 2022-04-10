#pragma once
#include "stack.h"
#include "myExceptions.h"
#include "changeLength1D.h"
template <class T>
class arrayStack :
	public stack<T>
{
public:
	arrayStack(int initialCapacity = 10)
	{
		if (initialCapacity < 1)
			cout << "Initial capacity must be > 0" << endl;
		arrayLength = initialCapacity;
		stack = new T[arrayLength];
		stackTop = -1;
	}
	~arrayStack() { delete[]stack; }
	bool empty() const { return stackTop == -1; }
	int size() const { return stackTop + 1; }
	T& top()
	{
		if (stackTop == -1)
			throw stackEmpty();
		return stack[stackTop];
	}
	void pop()
	{
		if (stackTop == -1)
			throw stackEmpty();
		stack[stackTop--].~T();
	}
	void push(const T& theElement)
	{
		if (stackTop == arrayLength - 1)
		{
			changeLength1D(stack, arrayLength, 2 * arrayLength);
			arrayLength *= 2;
		}
		stack[++stackTop] = theElement;
	}
protected:
	int stackTop;
	int arrayLength;
	T* stack;
};

