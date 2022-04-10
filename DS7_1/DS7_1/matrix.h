#pragma once

#include <ostream>
#include <iostream>
#include "myExceptions.h"
using namespace std;

template <class T>
class matrix
{
	
public:
	matrix(int theRows = 0, int theColumns = 0);
	matrix(const matrix<T>& m);
	~matrix() { delete[]element; }

	int rows() const { return theRows; }
	int columns() const { return theColumns; }
	T& operator()(int i, int j) const;
	matrix<T>& operator=(const matrix<T>& m);
	
	matrix<T> operator+(const matrix<T>& m) const;
	matrix<T> operator-() const;
	matrix<T> operator-(const matrix<T>& m) const;
	matrix<T> operator*(const matrix<T>& m) const;
	matrix<T>& operator+=(const T& theElement);
	void output(ostream& out, const matrix<T>& theMatrix) const;

	template <class T>
	friend ostream& operator<<(ostream& out, const matrix<T>& theMatrix);

private:
	int theRows, theColumns;
	T* element;

};

template <class T>
ostream& operator<<(ostream& out, const matrix<T>& theMatrix)
{
	// TODO: 在此处插入 return 语句
	for (int i = 1; i <= theMatrix.theRows; i++)
	{
		for (int j = 1; j <= theMatrix.theColumns; j++)
		{
			out << theMatrix(i,j) << " ";
		}
		out << endl;
	}
	//theMatrix.output(out);
	return out;
}

template<class T>
inline matrix<T>::matrix(int theRows, int theColumns)
{
	if (theRows < 0 || theColumns < 0)
		throw illegalParameterValue("Rows and columns must be >= 0");
	if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
		throw illegalParameterValue
		("Either both or neither rows and columns should be zero");
	this->theRows = theRows;
	this->theColumns = theColumns;
	element = new T[theRows*theColumns];
}

template<class T>
inline matrix<T>::matrix(const matrix<T>& m)
{
	theRows = m.theRows;
	theColumns = m.theColumns;
	element = new T[theRows * theColumns];

	copy(m.element, m.element + theRows * theColumns, element);
}

template<class T>
inline T & matrix<T>::operator()(int i, int j) const
{
	// TODO: 在此处插入 return 语句
	if (i<1 || j<1 || i>theRows || j>theColumns)
		throw matrixIndexOutOfBounds();
	int index = (i - 1)*theColumns + j - 1;
	return element[index];
}

template<class T>
inline matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
	// TODO: 在此处插入 return 语句
	if (this != &m)
	{
		delete[]element;
		theRows = m.theRows;
		theColumns = m.theColumns;
		element = new T[theRows*theColumns];

		copy(m.element, m.element + theRows * theColumns, element);
	}
	return *this;
}


template<class T>
inline matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{
	if (theRows != m.theRows || theColumns != m.theColumns)
		throw matrixSizeMismatch();

	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows*theColumns; i++)
		w.element[i] = this->element[i] + m.element[i];
	return w;
}

template<class T>
inline matrix<T> matrix<T>::operator-() const
{
	// create result matrix w
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
		w.element[i] = -element[i];
	return w;
}

template<class T>
inline matrix<T> matrix<T>::operator-(const matrix<T>& m) const
{
	if (theRows != m.theRows || theColumns != m.theColumns)
		throw matrixSizeMismatch();
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows*theColumns; i++)
		w.element[i] = this->element[i] - m.element[i];
	return matrix<T>(w);
}

template<class T>
inline matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{
	if (theColumns != m.theRows)
		throw matrixSizeMismatch();
	matrix<T> w(theRows, m.theColumns);
	int ct = 0, cm = 0, cw = 0;
	for (int i = 0; i < theRows; i++)
	{
		for (int j = 0; j < m.theColumns; j++)
		{
			T sum = element[ct] * m.element[cm];
			for (int k = 1;k < theColumns;k++)
			{
				ct++;
				cm += m.theColumns;
				sum += element[ct] * m.element[cm];
			}
			w.element[cw++] = sum;
			ct -= theColumns - 1;
			cm = j + 1;
		}
		ct += theColumns;
		cm = 0;
	}
	return matrix<T>(w);
}

template<class T>
inline matrix<T>& matrix<T>::operator+=(const T& theElement)
{
	for (int i = 0;i < theRows*theColumns;i++)
		element[i] += theElement;
	return *this;
}

template<class T>
inline void matrix<T>::output(ostream& out, const matrix<T>& theMatrix) const
{
	for (int i = 0; i < theMatrix.theRows; i++)
	{
		for (int j = 0; j < theMatrix.theColumns; j++)
		{
			out << theMatrix.element[i + j] << " ";
		}
		out << endl;
	}
}
