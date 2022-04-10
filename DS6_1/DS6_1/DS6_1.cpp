// DS6_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <numeric>     // has accumulate

#include "linearlist.h"
#include "chain.h"
#include "extendedLinearlist.h"
#include "extendedChain.h"

using namespace std;

int main_t()
{
	// test constructor
	linearlist<double> *x = new chain<double>();
	//chain<double>* x = new chain<double>(10);
	//chain<double> x;
	chain<int> y, z;

	// test size
	cout << "Initial size of x, y, and z = "
		<< x->size() << ", "
		<< y.size() << ", "
		<< z.size() << endl;

	// test empty
	if (x->empty()) cout << "x is empty" << endl;
	else cout << "x is not empty" << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;

	// test insert
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << "Size of y = " << y.size() << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;
	y.output(cout);
	cout << endl << "Testing overloaded <<" << endl;
	cout << y << endl;

	// test indexOf
	int index = y.indexOf(4);
	if (index < 0) cout << "4 not found" << endl;
	else cout << "The index of 4 is " << index << endl;

	index = y.indexOf(7);
	if (index < 0) cout << "7 not found" << endl;
	else cout << "The index of 7 is " << index << endl;

	// test get
	cout << "Element with index 0 is " << y.get(0) << endl;
	cout << "Element with index 3 is " << y.get(3) << endl;

	// test erase
	y.erase(1);
	cout << "Element 1 erased" << endl;
	cout << "The list is " << y << endl;
	y.erase(2);
	cout << "Element 2 erased" << endl;
	cout << "The list is " << y << endl;
	y.erase(0);
	cout << "Element 0 erased" << endl;
	cout << "The list is " << y << endl;

	cout << "Size of y = " << y.size() << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;

	try { y.insert(-3, 0); }
	catch (illegalIndex e)
	{
		cout << "Illegal index exception" << endl;
		cout << "Insert index must be between 0 and list size" << endl;
		e.outputMessage();
	}

	// test copy constructor
	chain<int> w(y);
	y.erase(0);
	y.erase(0);
	cout << "w should be old y, new y has first 2 elements removed" << endl;
	cout << "w is " << w << endl;
	cout << "y is " << y << endl;

	// a few more inserts, just for fun
	y.insert(0, 4);
	y.insert(0, 5);
	y.insert(0, 6);
	y.insert(0, 7);
	cout << "y is " << y << endl;

	return 0;
}

int main()
{
	// create an extended chain
	extendedChain<int> y;
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << "Size of y = " << y.size() << endl;

	// test iterator
	cout << "Ouput using forward iterators pre and post ++" << endl;
	for (extendedChain<int>::iterator i = y.begin();
		i != y.end(); i++)
		cout << *i << "  ";
	cout << endl;
	for (extendedChain<int>::iterator i = y.begin();
		i != y.end(); ++i)
	{
		cout << *i << "  ";
		*i += 1;
	}
	cout << endl;

	cout << "Incremented by 1 list is " << y << endl;

	// try out an STL algorithm
	int sum = accumulate(y.begin(), y.end(), 0);
	cout << "The sum of the elements is " << sum << endl;

	// clear the chain and do a few appends
	y.clear();
	y.push_back(1);
	y.push_back(2);
	y.push_back(3);
	cout << "Appended 3 integers, list y should be 1 2 3" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;

	y.insert(3, 4);
	y.insert(0, 0);
	cout << "List y should be 0 1 2 3 4" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;

	y.erase(4);
	y.erase(0);
	y.push_back(6);
	cout << "List y should be 1 2 3 6" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;

	return 0;
}

