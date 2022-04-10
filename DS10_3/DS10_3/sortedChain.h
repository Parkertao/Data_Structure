#pragma once


#include<iostream>
//#include"Dictionary.h"
//#include"pairNode.h"

template<class K, class E>
struct pairNode
{
	pair<const K, E> element;
	pairNode<K, E>* next;

	pairNode(const pair<const K, E>& thePair) :element(thePair) {}
	pairNode(const pair<const K, E>& thePair, pairNode<K, E>* theNext) :element(thePair) { next = theNext; }
};

template<class K,class E>
class sortedChain
{
public:
	sortedChain() { firstNode = NULL;dSize = 0; }
	~sortedChain();

	bool empty()const { return dSize == 0; }
	int size()const { return dSize; }
	pair<const K, E>* find(const K& theKey)const;
	void erase(const K& theKey);
	void insert(const pair<const K, E>& thePair);
	void output(ostream& out)const;

protected:
	pairNode<K, E>* firstNode;
	int dSize;
};
template<class K,class E>
ostream& operator<<(ostream& out, const sortedChain<K, E>& x)
{
	x.output(out);
	return out;
}

template<class K, class E>
inline sortedChain<K, E>::~sortedChain()
{
	while (firstNode != NULL)
	{
		pairNode<K, E>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
	
}

template<class K, class E>
inline pair<const K, E>* sortedChain<K, E>::find(const K & theKey) const
{
	pairNode<K, E>* currentNode = firstNode;
	while (currentNode != NULL && currentNode->element.first != theKey)
		currentNode = currentNode->next;
	if (currentNode != NULL && currentNode->element.first == theKey)
		return &currentNode->element;
	return NULL;
}

template<class K, class E>
inline void sortedChain<K, E>::erase(const K & theKey)
{
	pairNode<K, E> *p = firstNode, *tp = NULL;
	while (p != NULL && p->element.first < theKey)
	{
		tp = p;
		p = p->next;
	}
	if (p != NULL && p->element.first == theKey)
	{
		if (tp == NULL)firstNode = p->next;
		else tp->next = p->next;

		delete p;
		dSize--;
	}
}

template<class K, class E>
inline void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{
	pairNode<K, E> *p = firstNode, *tp = NULL;

	while (p != NULL && p->element.first < thePair.first)
	{
		tp = p;
		p = p->next;
	}
	if (p != NULL && p->element.first == thePair.first)
	{
		p->element.second = thePair.second;
		return;
	}
	pairNode<K, E>* newNode = new pairNode<K, E>(thePair, p);
	if (tp == NULL)firstNode = newNode;
	else tp->next = newNode;

	dSize++;
	return;
}

template<class K, class E>
inline void sortedChain<K, E>::output(ostream & out) const
{
	for (pairNode<K, E>* currentNode = firstNode;currentNode != NULL;currentNode = currentNode->next)
		out << currentNode->element.first << " " << currentNode->element.second << " ";
}
