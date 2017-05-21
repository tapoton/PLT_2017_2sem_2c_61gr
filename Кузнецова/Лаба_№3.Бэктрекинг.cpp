#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#define SIZE 6

using namespace std;

int Init_matr(int **a)
{
	int sum = 0;
	int dis;
	for (int i = 0; i < SIZE; i++)
	{
		a[i][i] = 0;
		for (int j = i + 1; j < SIZE; j++)
		{
			cout << "Enter the distanse " << (i + 1) << " - " << (j + 1) << ": ";
			cin >> dis;
			sum += dis;
			a[i][j] = dis;
			a[j][i] = dis;
		}
	}
	return sum;
}


void Print(int **a)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf("%5d ", a[i][j]);
		printf("\n");
	}
}


void Init_dv(int *d, bool *v, int max, int k)
{
	for (int i = 0; i < SIZE; i++)
	{
		d[i] = max;
		v[i] = 0;
	}
	d[k] = 0;
}



void Deikstra(int max, bool *v, int *d, int **a, int k, int &s, int smin)
{
	int minind = SIZE + 1;
	int min1 = max;
	int weight;
	int i = k;
	do
	{
		if (!v[i] && d[i] < min1)
		{
			min1 = d[i];
			minind = i;
		}
		i++;
		if (i >= SIZE)
			i = 0;
	} while (i != k);

	if (minind != SIZE + 1)
	{
		int i = k;
		do
		{
			if (a[minind][i] > 0)
			{
				weight = min1 + a[minind][i];
				if (weight < d[i])
					d[i] = weight;
			}
			i++;
			if (i >= SIZE)
				i = 0;
		} while (i != k);
		v[minind] = 1;
		s = s + d[minind];
		if (s > smin)
			return;
		else
			Deikstra(max, v, d, a, k, s, smin);
	}
	else
		return;
}



int main()
{
	setlocale(LC_ALL, "Russian");

	int **a;
	a = new int*[SIZE];
	for (int i = 0; i < SIZE; i++)
		a[i] = new int[SIZE];


	int max;
	max = Init_matr(a) * SIZE;

	Print(a);

	int *d = new int[SIZE];
	bool *v = new bool[SIZE];
	int smin = max;
	int minind;

	for (int ind = 0; ind < SIZE; ind++)
	{
		Init_dv(d, v, max, ind);
		int sum = 0;
		Deikstra(max, v, d, a, ind, sum, smin);
		if (sum < smin)
		{
			smin = sum;
			minind = ind;
		}
	}

	cout << "City " << minind + 1 << " has the smalest sum distanse = " << smin << endl;

	system("PAUSE");
	return 0;
}


