#pragma once
#include <iostream>

template <class T>
class diagonalMatrix
{
public:
	diagonalMatrix(int theN = 10);
	~diagonalMatrix() { delete[]element; }
	T get(int i, int j) const;
	void set(int i, int j, const T& theElement);
private:
	int n;
	T* element;
};

template<class T>
inline diagonalMatrix<T>::diagonalMatrix(int theN)
{
	if (theN < 1)
		//throw illegalParameterValue("Matrix size must be >= 0");
		std::cout << "Matrix size must be >= 0" << std::endl;
	n = theN;
	element = new T[n];
}

template<class T>
inline T diagonalMatrix<T>::get(int i, int j) const
{
	// check bounds
	if (i == j)
		return element[i - 1];
	else
		return 0;
}

template<class T>
inline void diagonalMatrix<T>::set(int i, int j, const T & theElement)
{
	//check bounds
	if (i == j)
		element[i - 1] = theElement;
	else
		if (theElement != 0)
			std::cout << "nondiagonal element must be zero" << std::endl;
}
