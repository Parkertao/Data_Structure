#pragma once
//#include "Dictionary.h"
#include "myExceptions.h"
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>

template <class K,class E>
struct skipNode
{
	typedef pair<const K, E> pairType;

	pairType element;
	skipNode<K, E> **next;
	skipNode(const pairType& thePair, int size) :element(thePair) { next = new skipNode<K, E>*[size]; }
};

template <class K,class E>
class skipList 
{
protected:
	float cutOff;
	int levels;
	int dSize;
	int maxLevel;
	K tailKey;
	skipNode<K, E>* headerNode;
	skipNode<K, E>* tailNode;
	skipNode<K, E>** last;

public:
	skipList(K largeKey, int maxPairs = 10000, float prob = 0.5);
	~skipList();
	bool empty()const { return dSize == 0; }
	int size()const { return dSize; }
	pair<const K, E>* find(const K& theKey)const;
	int level()const;
	skipNode<K, E>* search(const K& theKey)const;
	void insert(const pair<const K, E>& thePair);
	void erase(const K& theKey);
	void output(ostream& out)const;
};

template<class K, class E>
inline skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{
	cutOff = prob * RAND_MAX;
	maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;
	levels = 0;
	dSize = 0;
	tailKey = largeKey;

	pair<K, E> tailPair;
	tailPair.first = tailKey;
	headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);
	tailNode = new skipNode<K, E>(tailPair, 0);
	last = new skipNode<K, E> *[maxLevel + 1];

	for (int i = 0;i <= maxLevel;i++)
		headerNode->next[i] = tailNode;//初始化所有头节点指向尾结点
}

template<class K, class E>
inline skipList<K, E>::~skipList()
{
	skipNode<K, E>* nextNode;

	while (headerNode != tailNode)
	{
		nextNode = headerNode->next[0];
		delete headerNode;
		headerNode = nextNode;
	}
	delete tailNode;
	delete[] last;
}

template<class K, class E>
inline pair<const K, E>* skipList<K, E>::find(const K & theKey) const
{
	if(theKey >= tailKey)
		return NULL;
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels;i >= 0;i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
	}
	if (beforeNode->next[0]->element.first == theKey)
		return &beforeNode->next[0]->element;
	return NULL;
}

template<class K, class E>
inline int skipList<K, E>::level() const
{
	int lev = 0;
	while (rand() <= cutOff)
		lev++;
	return (lev <= maxLevel) ? lev : maxLevel;
}

template<class K, class E>
inline skipNode<K, E>* skipList<K, E>::search(const K & theKey) const
{
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels;i >= 0;i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
		last[i] = beforeNode;
	}
	return beforeNode->next[0];
}

template<class K, class E>
inline void skipList<K, E>::insert(const pair<const K, E>& thePair)
{
	if (thePair.first >= tailKey)
	{
		ostringstream s;
		s << "Key = " << thePair.first << "Must be < " << tailKey;
		throw illegalParameterValue(s.str());
	}
	//如果已有重复的，则覆盖之前的值
	skipNode<K, E>* theNode = search(thePair.first);
	if (theNode->element.first == thePair.first)
	{
		theNode->element.second = thePair.second;
		return;
	}

	int theLevel = level();
	if (theLevel > levels)
	{
		theLevel = ++levels;
		last[theLevel] = headerNode;
	}
	skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
	for (int i = 0;i <= theLevel;i++)
	{
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}
	dSize++;
	return;
}

template<class K, class E>
inline void skipList<K, E>::erase(const K & theKey)
{
	if (theKey >= tailKey) return;
	skipNode<K, E>* theNode = search(theKey);
	if (theNode->element.first != theKey) return;

	for (int i = 0;i <= levels && last[i]->next[i] == theNode;i++)
		last[i]->next[i] = theNode->next[i];//这块没看明白
	while (levels > 0 && headerNode->next[levels] == tailNode)
		levels--;
	delete theNode;
	dSize--;
}

template<class K, class E>
inline void skipList<K, E>::output(ostream & out) const
{
	for (skipNode<K, E>* currentNode = headerNode->next[0];currentNode != tailNode;currentNode = currentNode->next[0])
		out << currentNode->element.first << " " << currentNode->element.second << " ";
}
