#pragma once
#include <iostream>
#include "linearlist.h"

template <class T>
class extendedLinearlist: linearlist<T>
{
public:
	virtual ~extendedLinearlist(){}
	virtual void clear() = 0;
	virtual void push_back(const T& theElement) = 0;
};