#include <iostream>
#include <fstream>

using namespace std;

void initialization(bool *mark, int *num, int *time, int n, int d)
{	
	for (int i = 0; i < n; i++)
		mark[i] = false;
		
	for (int i = 0; i < n; i++)
		num[i] = -1;
		
	for (int i= 0; i < n; i++)
		time[i] = 10001;
	time[d] = 0;		
}

void dijkstra(int **bus, bool *mark, int *time, int *num, int n, int r)
{	
	int min;
	while (1)
	{
		min = -1;
		for (int i = 0; i < n; i++)
			if (mark[i] == false && time[i]!=10001)
				{
					if (min == -1)
						min = i;
					else
						if (time[i] < time[min])
							min = i;
				}
		if (min == -1) 
			break;
		for (int i = 0; i < r; i++)
			if(bus[i][0] == min)
			{
				if (mark[bus[i][2]] == false && bus[i][1]>=time[min] && time[bus[i][2]] > bus[i][3])
				{
					time[bus[i][2]] = bus[i][3];
					num[bus[i][2]] = min;
				} 
			}
		mark[min] = true;
	}
		
}

bool proverka(int *time, int v)
{
	bool t = false;
	if (time[v] == 10001)
		return t;
	else
	 	return (!t); 
}

void visit(int *res, int *num, int v)
{
	int t, n;
	t = v;
	n = 0;
	while(t >= 0)
	{
		res[n] = t + 1;
		t = num[t];
		n++;
	}
	cout << "Visited villages: ";
	for (int i = n-1; i >= 0; i--)
		cout << res[i] << ' ';
	cout << endl;
}


int main()
{
	ifstream fin ("input.txt");
  	if (!fin)
	{
		cerr << "Error opening file" << endl;
	}
	
	int n, d, v, r;
	bool f;
		
	fin >> n;
	fin >> d;
	fin >> v;
	fin >> r;
	d--;
	v--;
	
	int **bus = new int *[r];
	for (int i = 0; i < r; i++)
		bus[i] = new int [4];
		
	int *num = new int [n];	// Intermediate array for storing vertices with minimum distance
	int *time = new int [n]; // An array for calculating the minimum time
	int *res = new int [n]; // An array of vertices that make up the minimal path
	bool *mark = new bool [n]; // Array of visited vertices

	for (int i = 0; i < r; i++)
		{
			fin >> bus[i][0] >> bus[i][1] >> bus[i][2] >> bus[i][3];
			bus[i][0]--;
			bus[i][2]--;
		}
	
	initialization(mark, num, time, n, d);
	
	dijkstra(bus, mark, time, num, n, r);

	f = proverka(time, v);
	if (!f)
		cout << "-1"<< endl;
	else
	{
		cout << "The minimum time from d to v: " << time[v]<< endl;
		visit(res, num, v);
	}
	return 0;
}
