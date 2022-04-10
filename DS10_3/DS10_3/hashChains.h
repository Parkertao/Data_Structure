#pragma once
#ifndef hashChains_
#define hashChains_

#include <iostream>
#include "HA.h"
//#include "Dictionary.h"
#include "sortedChain.h"
template <class K,class E>
class hashChains
{
public:
	hashChains(int theDivisor = 11)
	{
		divisor = theDivisor;
		dSize = 0;
		table = new sortedChain<K, E>[divisor];
	}
	~hashChains() { delete[] table; }

	bool empty()const { return dSize == 0; }
	int size()const { return dSize; }
	pair<const K, E>* find(const K& theKey)const
	{
		return table[HA(theKey) % divisor].find(theKey);
	}
	void insert(const pair<const K, E>& thePair)
	{
		int homeBucket = (int)HA(thePair.first) % divisor;
		int homeSize = table[homeBucket].size();
		table[homeBucket].insert(thePair);
		if (table[homeBucket].size() > homeSize) dSize++;
	}
	void erase(const K& theKey)
	{
		table[HA(theKey)&divisor].erase(theKey);
	}
	void output(ostream& out) const
	{
		for (int i = 0l;i < divisor;i++)
		{
			if (table[i].size() == 0)
				cout << "NULL" << endl;
			else
				cout << table[i] << endl;
		}
	}
protected:
	sortedChain<K, E>* table;
	HA<K> HA;
	int dSize;
	int divisor;
};

template <class K,class E>
ostream& operator<<(ostream& out, const hashChains<K, E>& x)
{
	x.output(out);
	return out;
}

#endif
