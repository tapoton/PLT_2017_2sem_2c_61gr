#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <string.h>

using namespace std;

int maximum = 0;

int i;

int MaximumFlow(int **Matrix, int number, int last, int start, int end, int minimum)
{
	
	if (start != 0&&minimum > Matrix[last][start]) minimum = Matrix[last][start];

	if (start == 0)
	{
		i = 0;
		while (i<number)
		{
			while (Matrix[start][i])
			{
				int index = i;
				minimum = MaximumFlow(Matrix, number, start, i, end, INT_MAX);
				maximum += minimum;
				i = index;
			}
			i++;
		}

	}
	if (start != end)
	{
		i = 0;
		while (Matrix[start][i] == 0 && i < number)
		{
			i++;
			if (i == number)
			{
				Matrix[last][start] = 0;
				return 0;
			}
		}

		minimum = MaximumFlow(Matrix, number, start, i, end, minimum);
	}
	Matrix[last][start] -= minimum;
	return minimum;
}


int main()
{
	ifstream input("input.txt");
	int number, edge;
	input >> number;
	input >> edge;

	int **Matrix = new int*[number];
	for (int i = 0; i < number; i++)
		Matrix[i] = new int[number];

	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++)
			Matrix[i][j] = 0;

	int firstindex, secondindex, value;
	for (int i = 0; i < edge; i++)
	{
		input >> firstindex; firstindex--;
		input >> secondindex; secondindex--;
		input >> value;
		Matrix[firstindex][secondindex] = value;
	}

	int start = 0, end = number - 1;
	int flow = MaximumFlow(Matrix, number, 0, start, end, INT_MAX);
	cout << maximum<<endl;
	system("pause");
	return 0;
	
}