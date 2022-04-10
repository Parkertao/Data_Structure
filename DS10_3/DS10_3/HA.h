#pragma once
#ifndef HA_
#define HA_

#include <iostream>
#include <string>
using namespace std;

template<class K> class HA;

template<>
class HA<string>
{
public:
	size_t operator()(const string theKey)const
	{
		unsigned long HAValue = 0;
		int length = (int)theKey.length();
		for (int i = 0;i < length;i++)
			HAValue = 5 * HAValue + theKey.at(i);
		return size_t(HAValue);
	}
};

template<>
class HA<int>
{
public:
	size_t operator()(const int theKey)const
	{
		return size_t(theKey);
	}
};

template<>
class HA<long>
{
public:
	size_t operator()(const long theKey)const
	{
		return size_t(theKey);
	}
};
#endif
