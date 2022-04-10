#pragma once
#include "stack.h"
#include "arrayList.h"
#include "myExceptions.h"
template <class T>
class derivedArrayStack :
	public stack<T>, private arrayList<T>
{
public:
	derivedArrayStack(int initialCapacity = 10) :arrayList<T>(initialCapacity) {}
	bool empty() const { return arrayList<T>::empty(); }
	int size() const { return arrayList<T>::size(); }
	T& top()
	{
		try { return get(arrayList<T>::size() - 1); }
		catch (illegalIndex) { throw stackEmpty(); }
	}
	void pop()
	{
		try { arrayList<T>::erase(arrayList<T>::size() - 1); }
		catch (illegalIndex) { throw stackEmpty(); }
	}
	void push(const T& theElement)
	{
		insert(arrayList<T>::size(), theElement);
	}
};

