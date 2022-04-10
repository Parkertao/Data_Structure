#pragma once
#include <iostream>
#include<sstream>
#include<string>
#include "linearlist.h"
#include "myExceptions.h"

using namespace std;

template <class T>
struct chainNode
{
	T element;
	chainNode* next;

	chainNode(){}

	chainNode(const T& theElement) 
	{this->element = theElement;}

	chainNode(const T& theElement, chainNode<T>* theNext) 
	{element = theElement; next = theNext;}
};



template <class T>
class chain : public linearlist<T>
{
public:

	/*friend linkedDigraph;
	friend linkedWDigraph<int>;
	friend linkedWDigraph<float>;
	friend linkedWDigraph<double>;*/

	chain(int initialCapacity = 10);
	chain(const chain<T>& theList);
	~chain();

	bool empty() const {return listSize == 0;}
	int size() const {return listSize;}
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void insert(int theIndex, const T& theElement);
	void erase(int theIndex);
	void output(ostream& out) const;


	//iterator
	class iterator
	{
	public:

		typedef forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		iterator(chainNode<T>* theNode = NULL){node = theNode;}

		T& operator*() const {return node->element;}
		T* operator->() const {return &node->element;}

		iterator& operator++()
		{
			node = node->next;
			return *this;
		}
		iterator& operator++(int)
		{
			iterator old = *this;
			node = node->next;
			return old;
		}
		bool operator==(const iterator right) const
		{
			return node == right.node;
		}
		bool operator!=(const iterator right) const
		{
			return node != right.node;
		}
	protected:
		chainNode<T>* node;

	};

	iterator begin()
	{
		return iterator(firstNode);
	}
	iterator end()
	{
		return iterator(NULL);
	}

protected:
	//void checkIndex(int theIndex) const;
	void checkIndex(int theIndex, int flag = 0) const;
	chainNode<T>* firstNode;
	int listSize;
};




template <class T>
ostream& operator<<(ostream& out, const chain<T>& x)
{
	x.output(out);
	return out;
}



template <class T>
chain<T>::chain(const chain<T>& theList)
{
	listSize = theList.listSize;

	if(listSize == 0)
	{
		firstNode = NULL;
		return;
	}

	chainNode<T>* sourceNode = theList.firstNode;
	firstNode = new chainNode<T>(sourceNode->element);
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;

	while(sourceNode != NULL)
	{
		targetNode->next = new chainNode<T>(sourceNode->element);
		sourceNode = sourceNode->next;
		targetNode = targetNode->next;
	}
	targetNode->next = NULL;
}

template <class T>
chain<T>::chain(int initialCapacity /*= 10*/)
{
	if(initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " must be > 0";
		throw illegalParameterValue(s.str());

	}
	firstNode = NULL;
	listSize = 0;
}

template <class T>
chain<T>::~chain()
{
	while(firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template <class T>
void chain<T>::output(ostream& out) const
{
	for(chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
		out << currentNode->element << " ";
}

template <class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
	if(theIndex < 0 || theIndex > listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
	if(theIndex == 0)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else
	{
		chainNode<T>* p = firstNode;
		for(int i=0; i<theIndex-1; ++i)
			p = p->next;
		p->next = new chainNode<T>(theElement,p->next);
	}

	listSize++;
}

template <class T>
void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	chainNode<T>* deleteNode;
	if(theIndex == 0)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		chainNode<T>* p = firstNode;
		for(int i=0; i<theIndex-1; ++i)
			p = p->next;
		deleteNode = p->next;
		p->next = p->next->next;
	}
	listSize--;
	delete deleteNode;
}

template <class T>
int chain<T>::indexOf(const T& theElement) const
{
	chainNode<T>* currentNode = firstNode;
	int index = 0;
	while(currentNode != NULL && currentNode->element == theElement)
	{
		currentNode = currentNode->next;
		index ++;
	}
	if(currentNode == NULL) return -1;
	else return index;
}

template <class T>
void chain<T>::checkIndex(int theIndex, int flag) const
{
	if(theIndex < 0 || theIndex > listSize +flag - 1)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

//template <class T>
//void chain<T>::checkIndex(int theIndex, int flag) const
//{
//	if(flag == 1)
//	{
//		if(theIndex < 0 || theIndex > listSize)
//		{
//			ostringstream s;
//			s << "the index = " << theIndex << " the list size = " << listSize;
//			throw illegalIndex(s.str());
//		}
//	}
//}



template <class T>
T& chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	chainNode<T>* currentNode = firstNode;
	for(int i=0; i<theIndex; ++i)
	{
		currentNode = currentNode->next;
	}
	return currentNode->element;
}