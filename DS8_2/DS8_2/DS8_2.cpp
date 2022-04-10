// DS8_2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "arrayStack.h"

// 括号配对问题
void printMatchedPairs(string expr)
{
	arrayStack<int> s;
	int length = (int)expr.size();

	for (int i = 0;i < length;i++)
	{
		if (expr.at(i) == '(')
			s.push(i);
		else
			if (expr.at(i) == ')')
			{
				try
				{
					cout << s.top() << ' ' << i << endl;
					s.pop();
				}
				catch (stackEmpty)
				{
					cout << "No match for right parenthesis" << " at " << i << endl;
				}
			}
		
	}
	while (!s.empty())
	{
		cout << "No match for left parenthesis at " << s.top() << endl;
		s.pop();
	}
}
int test_above()
{
	string expr;
	cout << "Type an expression" << endl;
	cin >> expr;
	cout << "The pairs of matching parentheses in"
		<< endl << expr << endl << "are" << endl;

	printMatchedPairs(expr);

	return 0;
}
//----------------------------------------------------


// 汉诺塔问题递归解法
void towersOfHanoi(int n, int x, int y, int z)
{// Move the top n disks from tower x to tower y.
 // Use tower z for intermediate storage.
	if (n > 0)
	{
		towersOfHanoi(n - 1, x, z, y);
		cout << "Move top disk from tower " << x
			<< " to top of tower " << y << endl;
		towersOfHanoi(n - 1, z, y, x);
	}
}

int test_above1(void)
{
	cout << "Moves for a three disk problem are" << endl;
	towersOfHanoi(4, 1, 2, 3);
	return 0;
}
 //------------------------------------------------

//汉诺塔问题递归加栈显示解法

arrayStack<int> tower[4];

void moveAndShow(int n, int x, int y, int z)
{
	if (n > 0)
	{
		moveAndShow(n - 1, x, z, y);
		// 把当前第n个盘子从1移到2上
		int d = tower[x].top();
		tower[x].pop();
		tower[y].push(d);
		//----------------------
		cout << "Move disk " << d << " from tower "
			<< x << " to top of tower " << y << endl;

		moveAndShow(n - 1, z, y, x);
	}
}

void towerOfHanoi(int n)
{
	for (int i = n;i > 0;i--)
	{
		tower[1].push(i);
	}
	moveAndShow(n, 1, 2, 3);
}
int test_above2()
{
	cout << "Moves for a three disk problem are" << endl;
	towerOfHanoi(10);
	return 0;
}
//-----------------------------------------------

//列车重排问题
arrayStack<int> *track;
int numberOfCars;
int numberOfTracks;
int smallestCar;
int itsTrack;

void outputFromHoldingTrack();
bool putInHoldingTrack(int c);

bool railroad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks)
{
	numberOfCars = theNumberOfCars;
	numberOfTracks = theNumberOfTracks;
	track = new arrayStack<int>[numberOfTracks + 1];
	int nextCarToOutput = 1;
	smallestCar = numberOfCars + 1;//初始化smallestCar值为最大值

	for (int i = 1;i <= numberOfCars;i++)
	{
		if (inputOrder[i] == nextCarToOutput)//车厢号满足输出号码则输出该车厢
		{
			cout << "move car " << inputOrder[i] << " form input track to output track" << endl;
			nextCarToOutput++;

			while (smallestCar == nextCarToOutput)//检查缓冲栈中是否有满足输出号码的车厢，并循环检测直至全部输出完毕
			{
				outputFromHoldingTrack();
				nextCarToOutput++;
			}
		}
		else if (!putInHoldingTrack(inputOrder[i])) return false;//如果把车厢放入缓冲站失败，则说明无法完成重排
	}
	return true;
}

void outputFromHoldingTrack()
{
	//释放smallestCar号车厢
	track[itsTrack].pop();
	cout << "move car " << smallestCar << " from holding track " << itsTrack << " to output track" << endl;

	smallestCar = numberOfCars + 2;//把smallestCar置最大值
	//遍历所有缓冲栈，找到缓冲轨道中最小的车厢号及栈位置：
	for (int i = 1;i <= numberOfTracks;i++)
	{
		if (!track[i].empty() && track[i].top() < smallestCar)
		{
			smallestCar = track[i].top();
			itsTrack = i;
		}
	}
}

bool putInHoldingTrack(int c)
{
	//初始化目标栈位置、目标栈栈顶值
	int bestTrack = 0;
	int bestTop = numberOfCars + 1;

	for (int i = 1;i <= numberOfTracks;i++)
	{
		if (!track[i].empty())
		{
			int topCar = track[i].top();
			if (c < topCar && topCar < bestTop)//找到满足栈顶值既大于c又是所有栈顶值中最小的一个
			{
				bestTop = topCar;
				bestTrack = i;
			}
		}
		else//空栈是可能放入的栈，但空栈栈顶默认为最大值numberOfCar+1
			if (bestTrack == 0) bestTrack = i;//只在第一次遇到空栈时把它视作可能放入的栈，之后再遇到空栈不再考虑
	}
	if (bestTrack == 0) return false;

	track[bestTrack].push(c);
	cout << "move car " << c << " from input track to holding track " << bestTrack << endl;

	if (c < smallestCar)//如果c是最小车厢号，更新smallestCar值以及栈位置
	{
		smallestCar = c;
		itsTrack = bestTrack;
	}
	return true;
}

int test_above3()
{
	int p[] = {0, 5, 8, 1, 7, 4, 2, 9, 6, 3};
    cout << "Input permutation is 581742963" << endl;
	//int p[] = { 0, 3, 6, 9, 2, 4, 7, 1, 8, 5 };
	//cout << "Input permutation is 369247185" << endl;
	railroad(p, 9, 4);
	return 0;
}

//------------------------------------------------------

//开关盒布线问题
bool checkBox(int net[], int n)
{
	arrayStack<int>* s = new arrayStack<int>(n);
	for (int i = 0;i < n;i++)
	{
		if (!s->empty())
		{
			if (net[s->top()] == net[i])
				s->pop();
			else
				s->push(i);
		}
		else
			s->push(i);
	}
	if (s->empty())
	{
		cout << "switch box is routable" << endl;
		return true;
	}

	cout << "switch box is not routable" << endl;
	return false;
}
int test_above4()
{
	// input the number of pins and their net assignment
	cout << "Type number of pins in switch box" << endl;
	int n;
	cin >> n;

	// create net assignment array
	int* net = new int[n];

	// input the net assignments
	cout << "Type net numbers for pins 1 through " << n << endl;
	for (int i = 0; i < n; i++)
		cin >> net[i];

	// see if the switch box is routable
	checkBox(net, n);
	return 0;
}
//------------------------------------------------------------

int main()
{
	int n, r;
	cout << "Enter number of elements" << endl;
	cin >> n;
	if (n < 2)
	{
		cout << "T0o few elements" << endl;
		return 1;
	}
	cout << "Enter number of relation" << endl;
	cin >> r;
	if (r < 1)
	{
		cout << "Too few relations" << endl;
		return 2;
	}

	arrayStack<int>* list = new arrayStack<int>[n + 1];
	int a, b;
	for (int i = 0;i < r;i++)
	{
		cout << "Enter next relation/pair" << endl;
		cin >> a >> b;
		list[a].push(b);
		list[b].push(a);
	}
	arrayStack<int> unprocessedList;
	bool* out = new bool[n + 1];
	for (int i = 0;i < n;i++)
		out[i] = false;

	for (int i = 1;i <= n;i++)
	{
		if (!out[i])
		{
			cout << "Next class is " << i << " ";
			out[i] = true;
			unprocessedList.push(i);
			while (!unprocessedList.empty())
			{
				int j = unprocessedList.top();
				unprocessedList.pop();
				while (!list[j].empty())
				{
					int q = list[j].top();
					list[j].pop();
					if (!out[q])
					{
						cout << q << " ";
						out[q] = true;
						unprocessedList.push(q);
					}
				}
			}
		}
		cout << endl;
	}
	cout << "End of list of equivalence classes" << endl;
	return 0;
}