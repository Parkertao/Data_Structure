// DS7_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "matrix.h"
//using std::cout;
//using std::cin;
//using std::endl;
using namespace std;

void irregularArray()
{
	int rownum = 5;
	int length[5] = { 6, 3, 4, 2, 7 };
	int** irregularArray = new int*[rownum];

	for (int i = 0; i < rownum; ++i)
	{
		irregularArray[i] = new int[length[i]];
	}

	irregularArray[2][3] = 5;
	irregularArray[4][6] = irregularArray[2][3] + 2;
	irregularArray[1][1] = 3;

	std::cout << irregularArray[2][3] << std::endl;
	std::cout << irregularArray[4][6] << std::endl;
	std::cout << irregularArray[1][1] << std::endl;
}

int main()
{
	try
	{
		matrix<int> x(3, 2), y, z;
		int i, j;
		for (i = 1; i <= 3; i++)
			for (j = 1; j <= 2; j++)
				x(i, j) = 2 * i + j;
		cout << "Initialized x(i,j) = 2*i + j" << endl;
		cout << "x(3,1) = " << x(3, 1) << endl;
		cout << "x is" << endl;;
		cout << x << endl;

		y = x;
		cout << "Assigned y = x" << endl;
		cout << "y is" << endl;
		cout << y << endl;

		x += 2;
		cout << "x incremented by 2 is" << endl;
		cout << x << endl;

		z = y + x;
		cout << "y + x is" << endl;
		cout << z << endl;

		cout << "-(y + x) is" << endl;
		cout << -z << endl;

		matrix<int> w(2, 3);
		for (i = 1; i <= 2; i++)
			for (j = 1; j <= 3; j++)
				w(i, j) = i + j;
		cout << "Initialized w(i,j) = i + j" << endl;
		cout << "w is" << endl;
		cout << w << endl;

		z = y * w;
		cout << "y * w is" << endl;
		cout << z << endl;
	}
	catch (...) {
		cerr << "An exception has occurred" << endl;
	}

	return 0;
}

//int main()
//{
//	int currVal = 0, val = 0;
//	if (cin >> currVal)
//	{
//		int cnt = 1;
//		while (cin >> val)
//		{
//			if (val == currVal)
//				cnt++;
//			else
//			{
//				cout << currVal << " occurs "
//					<< cnt << " times " << endl;
//				currVal = val;
//				cnt = 1;
//			}
//		}
//		//cout << currVal << " occurs "
//		//	<< cnt << " times " << endl;
//	}
//	return 0;
//}