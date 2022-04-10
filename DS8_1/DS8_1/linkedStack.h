#pragma once
#include "stack.h"
#include "chainNode.h"
#include "myExceptions.h"
template <class T>
class linkedStack : public  stack<T>
{
public:
	linkedStack(int initialCapacity = 10) { stackTop = NULL;stackSize = 0; }
	~linkedStack();
	bool empty() const { return stackSize == 0; }
	int size() const { return stackSize; }
	T& top();
	void pop();
	void push(const T& theElement);
private:
	chainNode<T>* stackTop;
	int stackSize;
};

template<class T>
inline linkedStack<T>::~linkedStack()
{
	while (stackTop != NULL)
	{
		chainNode<T>* nextNode = stackTop->next;
		delete stackTop;
		stackTop = nextNode;
	}
}

template<class T>
inline T & linkedStack<T>::top()
{
	if (stackSize == 0)
		throw stackEmpty();
	return stackTop->element;
}

template<class T>
inline void linkedStack<T>::pop()
{
	if (stackSize == 0)
		throw stackEmpty();
	chainNode<T>* nextNode = stackTop->next;
	delete stackTop;
	stackTop = nextNode;
	stackSize--;
}

template<class T>
inline void linkedStack<T>::push(const T & theElement)
{
	stackTop = new chainNode<T>(theElement, stackTop);
	stackSize++;
}
