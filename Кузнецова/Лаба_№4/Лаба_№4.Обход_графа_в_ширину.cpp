#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

void Init_n(int *nodes, int N)
{
	for (int i = 0; i < N; i++)
		nodes[i] = 0;
}

bool BFS(queue<int> Queue, int *nodes, int **a, int N, int k)
{
	int node = Queue.front();

	if (nodes[node] < 2)
	{
		Queue.pop();
		nodes[node] = 2;
		k++;

		for (int j = 0; j < N; j++)
		{
			if (a[node][j] == 1 && nodes[j] == 0)
			{
				Queue.push(j);
				nodes[j] = 1;
			}
		}

		if (k == N - 1)
		{
			cout << "ДА" << endl << endl;
			return 1;
		}
	}

	else
	{
		cout << "НЕТ" << endl << endl;
		return 0;
	}

	if (!Queue.empty())
		BFS(Queue, nodes, a, N, k);

	else
	{
		cout << "НЕТ" << endl << endl;
		return 0;
	}
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	queue<int> Queue;
	bool result;

	ifstream fin("input.txt");
	int N;
	fin >> N;

	int **a = new int*[N];
	for (int i = 0; i < N; i++)
		a[i] = new int[N];
	int *nodes = new int[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			fin >> a[i][j];

	Init_n(nodes, N);
	Queue.push(0);

	cout << "Количество вершин в графе = " << N << endl;
	cout << endl << "Матрица смежности вершин:" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}

	cout << endl << "Является ли граф деревом?  ";
	result = BFS(Queue, nodes, a, N, 0);

	ofstream fout;
	fout.open("output.txt");

	if (result)
		fout << "ДА";

	else
		fout << "НЕТ";

	fin.close();
	fout.close();

	system("PAUSE");
	return 0;
}

