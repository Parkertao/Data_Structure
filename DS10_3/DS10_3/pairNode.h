#pragma once

using namespace std;

template<class K,class E>
struct pairNode
{
public:
	pair<const K, E> element;
	pairNode<K, E>* next;

	pairNode(const pair<const K, E>& thePair) :element(thePair) {}
	pairNode(const pair<const K, E>& thePair, pairNode<K, E>* theNext) :element(thePair) { next = theNext; }
};
