#pragma once

#include <iostream>
#include <sstream>
#include "extendedLinearlist.h"
#include "chain.h"
#include "myExceptions.h"

template <class T>
class extendedChain: public extendedLinearlist<T>, public chain<T>
{
public:
	extendedChain(int initialCapacity = 10): chain<T>(initialCapacity){}
	extendedChain(const extendedChain<T>& theList): chain<T>(theList){}

	bool empty() const {return this->listSize == 0;}
	int size() const {return this->listSize;}
	T& get(int theIndex) const {return chain<T>::get(theIndex);}
	int indexOf(const T& theElement) const {return chain<T>::indexOf(theElement);}
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void clear();
	void push_back(const T& theElement);
	void output(ostream& out)const {return chain<T>::output(out);}
	void zero(){ this->firstNode = NULL; this->listSize = 0;}

protected:
	chainNode<T>* lastNode;
};

template <class T>
void extendedChain<T>::push_back(const T& theElement)
{
	chainNode<T>* p = new chainNode<T>(theElement, NULL);
	if(this->firstNode == NULL)
		this->firstNode = lastNode = p;
	else
	{
		lastNode->next = p;
		lastNode = p;
	}
	this->listSize++;
}

template <class T>
void extendedChain<T>::clear()
{
	while(this->firstNode != NULL)
	{
		chainNode<T>* nextNode = this->firstNode->next;
		delete this->firstNode;
		this->firstNode = nextNode;
	}
	zero();
}

template <class T>
void extendedChain<T>::insert(int theIndex, const T& theElement)
{
	this->checkIndex(theIndex, 1);
	if(theIndex == 0)
	{
		this->firstNode = new chainNode<T>(theElement, this->firstNode);
		if(this->listSize == 0) lastNode = this->firstNode;
	}
	else
	{
		chainNode<T>* p = this->firstNode;
		for(int i=0; i<theIndex-1; ++i)
			p = p->next;
		p->next = new chainNode<T>(theElement, p->next);
		if(this->listSize == theIndex)
			lastNode = p->next;
	}
	this->listSize++;
}

template <class T>
void extendedChain<T>::erase(int theIndex)
{
	this->checkIndex(theIndex);

	chainNode<T>* deleteNode;
	if(theIndex == 0)
	{
		deleteNode = this->firstNode;
		this->firstNode = this->firstNode->next;

	}
	else
	{
		chainNode<T>* p = this->firstNode;
		for(int i=0; i<theIndex-1; ++i)
			p = p->next;
		deleteNode = p->next;
		p->next = p->next->next;

		if(deleteNode == lastNode)
			lastNode = p;

	}
	this->listSize--;
	delete deleteNode;
}
