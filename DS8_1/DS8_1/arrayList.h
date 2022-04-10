#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "myExceptions.h"
#include <iterator>

//using namespace std;

template<class T>
class arrayList
{
public:
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>& theList);
	~arrayList(void);

	bool empty() const;
	int size() const;
	int indexOf(const T& intElement) const;
	T& get(int theIndex) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);

	void changeLength1D(T*& a, int oldLength, int newLength);
	void output(ostream& out) const;

	int capacity() const;

	friend ostream& operator<<(ostream& out, const arrayList<T>& x )
	{
		//copy(element, element + listSize, ostream_iterator<T>(out, " "));
		x.output(out);
		return out;
	}//友元函数

	class iterator
	{
	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		iterator(pointer thePosition = 0) {position = thePosition;}

		reference operator*() const {return *position;}
		pointer operator->() const {return &*position;}

		iterator& operator++() {++position; return *this;}
		iterator& operator++(int) {iterator old = *this; ++position; return old;}

		iterator& operator--() {--position; return *this;}
		iterator& operator--(int) {iterator old = *this; --position; return old;}

		bool operator!=(const iterator right) const {return position != right.position;}
		bool operator==(const iterator right) const {return position == right.position;}

	protected:
		pointer position;
	private:
	};

	iterator begin() {return iterator(element);}
	iterator end() {return iterator(element+listSize);}

protected:
	void checkIndex(int theIndex) const;
	T* element;
	int arrayLength;
	int listSize;
};




template<class T>
void arrayList<T>::output(ostream& out) const
{
	copy(element, element + listSize, ostream_iterator<T>(out, " "));

}



template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
	//复制构造函数
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	copy(theList.element, theList.element + listSize, element);
}

template<class T>
arrayList<T>::arrayList(int initialCapacity /*= 10*/)
{
	if(initialCapacity <1)
	{
		ostringstream s;
		s << "initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template<class T>
bool arrayList<T>::empty() const
{
	return listSize == 0;
}

template<class T>
int arrayList<T>::size() const
{
	return listSize;
}

template<class T>
int arrayList<T>::capacity() const
{
	return arrayLength;
}

template<class T>
T& arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return element[theIndex];
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{
	int theIndex = (int) (find(element, element + listSize, theElement) - element);
	if(theIndex == listSize) return -1;
	else return theIndex;
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{
	if(theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<class T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	copy(element + theIndex + 1, element + listSize, element + theIndex);
	element[--listSize].~T();
}


template<class T>
void arrayList<T>::changeLength1D(T*& a, int oldLength, int newLength)
{
	if(newLength < 0)
		throw illegalParameterValue("new length must be >= 0");

	T* temp = new T[newLength];
	int num = min(oldLength,newLength);
	copy(a, a + num, temp);
	delete []a;
	a = temp;
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
	if(theIndex < 0 || theIndex > listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	if (listSize == arrayLength)
	{
		changeLength1D(element, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}

	copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	element[theIndex] = theElement;
	listSize ++;
}


template<class T>
arrayList<T>::~arrayList(void)
{
	delete []element;
}

