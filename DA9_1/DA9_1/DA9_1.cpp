// DA9_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#include "arrayQueue.h"
#include "myExceptions.h"

//基本测试
int test(void)
{
	arrayQueue<int> q(4);

	// add a few elements
	q.push(1);
	cout << "Queue rear is " << q.back() << endl;
	q.push(2);
	cout << "Queue rear is " << q.back() << endl;
	q.push(3);
	cout << "Queue rear is " << q.back() << endl;
	q.push(4);
	cout << "Queue rear is " << q.back() << endl;

	cout << "Queue should be 1234, front to rear" << endl;

	// test empty and size
	if (q.empty())
		cout << "The queue is empty" << endl;
	else
		cout << "The queue is not empty" << endl;

	cout << "The queue size is " << q.size() << endl;

	while (!q.empty())
	{
		cout << "Queue front is " << q.front() << endl;
		q.pop();
		cout << "Popped front element" << endl;
	}

	try { q.pop(); }
	catch (queueEmpty message)
	{
		cout << "Last pop failed " << endl;
		message.outputMessage();
	}

	// create a wraparound queue and do array doubling
	arrayQueue<int> r(4);
	r.push(1);
	r.push(2);
	r.push(3);
	r.pop();
	r.pop();
	r.push(4);
	r.push(5);
	r.push(6);
	r.push(7);

	cout << "Queue should be 34567, front to rear" << endl;

	// test empty and size
	if (r.empty())
		cout << "The queue is empty" << endl;
	else
		cout << "The queue is not empty" << endl;

	cout << "The queue size is " << r.size() << endl;

	while (!r.empty())
	{
		cout << "Queue front is " << r.front() << endl;
		r.pop();
		cout << "Popped front element" << endl;
	}

	return 0;
}
//-----------------------------------------------------------

//列车重排-----------------------------------------------------
int itsTrack, smallestCar, numberOfTracks, numberOfCars;
arrayQueue<int>* track;
void outputFromHoldingTrack();
bool putInHoldingTrack(int c);

bool railroad(int* input, int Cars, int Tracks)
{
	numberOfCars = Cars;
	numberOfTracks = Tracks - 1;
	track = new arrayQueue<int>[numberOfTracks + 1];
	smallestCar = numberOfCars + 1;
	int next = 1;

	for (int i = 1;i <= numberOfCars;i++)
	{
		if (input[i] == next)
		{
			cout << "Move car " << input[i] << " from track " << Tracks << " to output track" << endl;
			next++;
			while (smallestCar == next)
			{
				outputFromHoldingTrack();
				next++;
			}
		}
		else
		{
			if (!putInHoldingTrack(input[i])) return false;
		}
	}
	return true;
}

void outputFromHoldingTrack()
{
	track[itsTrack].pop();
	cout << "Move car " << smallestCar << " from holding track " << itsTrack << " to output track" << endl;
	
	smallestCar = numberOfCars + 2;
	for (int i = 1;i <= numberOfTracks;i++)
	{
		if (!track[i].empty() && track[i].front() < smallestCar)
		{
			smallestCar = track[i].front();
			itsTrack = i;
		}
	}
}
bool putInHoldingTrack(int c)
{
	int bestTrack = 0, bestLast = 0;

	for (int i = 1;i <= numberOfTracks;i++)
	{
		if (!track[i].empty())
		{
			int lastCar = track[i].back();
			if (lastCar < c && lastCar > bestLast)
			{
				bestLast = lastCar;
				bestTrack = i;
			}
				
		}
		else
		{
			if (bestTrack == 0)
			{
				bestTrack = i;
			}
		}
	}
	if (bestTrack == 0) return false;
	track[bestTrack].push(c);
	cout << "Move car " << c << " into holding track " << bestTrack << endl;

	if (c < smallestCar)
	{
		smallestCar = c;
		itsTrack = bestTrack;
	}

	return true;
}
int test_above()
{
	//int p[] = {0, 5, 8, 1, 7, 4, 2, 9, 6, 3};
    //cout << "Input permutation is 581742963" << endl;
	int p[] = { 0, 3, 6, 9, 2, 4, 7, 1, 8, 5 };
	cout << "Input permutation is 369247185" << endl;
	bool ans = railroad(p, 9, 3);
	cout << ans << endl;
	return 0;
}
//----------------------------------------------------------------------

//电路布线