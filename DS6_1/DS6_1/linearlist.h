#pragma once
#include <iostream>


using namespace std;

template <class T>
class linearlist
{
public:


	virtual ~linearlist(){};

	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int theIndex) const = 0;
	virtual int indexOf(const T& theElement) const = 0;
	virtual void erase(int theIndex) = 0;
	virtual void insert(int theIndex, const T& theElement) = 0;
	virtual void output(ostream& out) const = 0;
};
