#pragma once
#ifndef hashTable_
#define hashTable_
#include<iostream>
#include"HA.h"
#include"myExceptions.h"


template <class K, class E>
class hashTable
{
public:
	hashTable(int theDivisor = 11);
	~hashTable() { delete[] table; }
	
	bool empty()const { return dSize == 0; }
	int size()const { return dSize; }
	pair<const K, E>* find(const K&)const;
	void insert(const pair<const K, E>&);
	void output(ostream& out)const;

protected:
	int search(const K&)const;
	pair<const K, E>** table;
	HA<K> HA;
	int dSize;
	int divisor;
};

template <class K, class E>
ostream& operator << (ostream& out,const hashTable<K,E>& x)
{
	x.output(out);
	return out;
}

template<class K, class E>
inline hashTable<K, E>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;
	table = new pair<const K, E>*[divisor];
	for (int i = 0;i < divisor;i++)
		table[i] = NULL;
}
template<class K, class E>
inline pair<const K, E>* hashTable<K, E>::find(const K& theKey) const
{
	int b = search(theKey);
	if (table[b] == NULL || table[b]->first != theKey)
		return NULL;
	return table[b];
}
template<class K, class E>
inline void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
	int b = search(thePair.first);
	if (table[b] == NULL)
	{
		table[b] = new pair<const K, E>(thePair);
		dSize++;
	}
	else
	{
		if (table[b]->first == thePair.first)
		{
			table[b]->second = thePair.second;
		}
		else
			throw hashTableFull();
	}
}
template<class K, class E>
inline void hashTable<K, E>::output(ostream & out) const
{
	for (int i = 0;i < divisor;i++)
	{
		if (table[i] == NULL)
			cout << "NULL" << endl;
		else
			cout << table[i]->first << " " << table[i]->second << endl;
	}
}
template<class K, class E>
inline int hashTable<K, E>::search(const K& theKey) const
{
	int i = (int)HA(theKey) % divisor;
	int j = i;
	do {
		if (table[j] == NULL || table[j]->first == theKey)
			return j;
		j = (j + 1) % divisor;
	} while (j != i);
	return j;
}
#endif