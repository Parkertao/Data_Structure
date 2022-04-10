// DS9_railroad_with_no_queue.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using std::cout;
using std::fill;
using std::endl;

int* which_track;
int* last_car;
int num_cars;
int num_tracks;

void output(int c)
{
	cout << "Move car " << c << " from holding track " << which_track[c] << " to output track" << endl;
	if (c == last_car[which_track[c]]) last_car[which_track[c]] = 0;
}

bool putin(int c)
{
	int best_track = 0, best_last = 0;
	for (int i = 1;i <= num_tracks;i++)
	{
		if (last_car[i] != 0)
		{
			if (c > last_car[i] && last_car[i] > best_last)
			{
				best_last = last_car[i];
				best_track = i;
			}
		}
		else
		{
			if (best_track == 0) best_track = i;
		}
	}
	if (best_track == 0) return false;

	which_track[c] = best_track;
	last_car[best_track] = c;
	cout << "Move car " << c << " from input track "
		<< which_track[c] << " to holding track" << endl;
	return true;
}

bool railroad(int* input, int cars, int tracks)
{
	num_cars = cars;
	num_tracks = tracks - 1;
	last_car = new int[num_tracks + 1];
	which_track = new int[num_cars + 1];
	fill(last_car + 1, last_car + num_tracks + 1, 0);
	fill(which_track + 1, which_track + num_cars + 1, 0);
	int next = 1;

	for (int i = 1;i <= num_cars;i++)
	{
		if (input[i] == next)
		{
			cout << "Move car " << input[i] << " from track " 
				<< tracks << " to output track" << endl;
			next++;
			while (next <= num_cars && which_track[next] != 0)
			{
				output(next);
				next++;
			}
		}
		else
		{
			if (!putin(input[i])) return false;
		}
	}
	return true;
}
int main()
{
	int p[] = { 0,5,8,1,7,4,2,9,6,3 };
	cout << "Input is 581742963" << endl;
	//int p[] = { 0, 3, 6, 9, 2, 4, 7, 1, 8, 5 };
	//cout << "Input permutation is 369247185" << endl;
	bool ans = railroad(p, 9, 3);
	if (!ans) cout << "can not assign railroad" << endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
