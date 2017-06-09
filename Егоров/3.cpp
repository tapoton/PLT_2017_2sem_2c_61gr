#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <string.h>

using namespace std;

int check = 0;

void init(int **cities, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cities[i][j] = 0;
	return;
}

void input(int n,  int** cities)
{
	int way = 0;
	for (int i = 0; i < n ; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				cout << "Is there a road between cities " << i + 1 << " and " << j + 1 << "? (1/0): ";
				cin >> way;
				cities[i][j] = way;
			}
			else cities[i][j] == 0;
		}
	}
}

string findpath(int** cities, int start, int end, string path, int n)
{
	if (start != end)
	{
		for (int i = 0; i < n; i++)
		{
			if (cities[start][i])
			{
				cities[start][i] = 0;
				start = i;

				string number = to_string(i+1);
				path += "->" + number;
				path = (findpath(cities, start, end, path, n));
			}
		}
	}
	else 
	{
		cout << "Path is: " << path<<endl; check++;
	}
	return path;
}


int main()
{
	int n;
	string path="";
	cout << "Enter the number of cities: ";
	cin >> n;

	int** cities = new int *[n];
	for (int i = 0; i < n; i++)
		cities[i] = new int[n];

	init(cities, n);
	input(n, cities);

	cout << "\nEnter the start of the path (1-n): ";
	int start;
	cin >> start;
	cout << "\nEnter the end of the path (1-n): ";
	int end;
	cin >> end;
	start--; end--;

	cout << "Enter the number of cities which you don't want to visit: ";
	int bn;
	cin >> bn;
	int bcity;

	if (bn)
	{
		cout << "Enter the numbers of this cities ";
		for (int i = 0; i < bn; i++)
		{
			cin >> bcity;
			bcity--;
			for (int j = 0;  j< n; j++)
				cities[bcity][j] = cities[j][bcity] = 0;
		}
	}
		
	path=findpath(cities, start, end, path, n);

	if (!check) cout << "There's no way to reach " << end + 1 << "  from " << start + 1;

	system("PAUSE");
	return 0;
}