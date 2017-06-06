// lab3.cpp
// 

#include "stdafx.h"
#include <iostream>


using namespace std;

void input(int n, bool** a, int &start, int &end);
void output(int n, bool** a);
int count_roads(bool** a, int n, bool** visited, int now, int end, int S = 0);
bool check(int n, bool** a, bool**visited, int start, int end);

int main() {
	int n;
	cout << "Enter count of cities: ";
	cin >> n;
	bool** a = new bool *[n];
	for (int i = 0; i < n; i++)
		a[i] = new bool[n];


	int start = 0, end = 0;
	input(n, a, start, end);
	output(n, a);

	bool **visited = new bool*[n];
	for (int i = 0; i < n; i++) {
		visited[i] = new bool[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = 0;
		}
	}

	if (check(n, a, visited, start, end))
		cout << "It is possible" << endl;
	else cout << "It isn't possible" << endl;
	cin >> n;
}


void input(int n, bool** a, int &start, int &end) {
	int x = -1;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			while (x != 1 && x != 0) {
				cout << "Is there a road between cities " << i + 1 << " and " << j + 1 << "? (1/0): ";
				cin >> x;
				if (x != 0 && x != 1) {
					cout << "Please, enter 1 or 0" << endl;
				}
			}
			a[i][j] = x;
			a[j][i] = x;
			x = -1;
		}
	}

	while (start < 1 || start > n) {
		cout << "Enter the number of the start city: ";
		cin >> start;
		if (start < 1 || start > n)
			cout << "Please, enter number from 1 to " << n << endl;
		}
		while (end < 1 || end > n) {
			cout << "Enter the number of the final city: ";
			cin >> end;
			if (end < 1 || end > n)
				cout << "Please, enter number from 1 to " << n << endl;
			}
		for (int i = 0; i < n; a[i][i] = 0, i++);
		cout << endl;
	}


	void output(int n, bool** a) {
		cout << " ";
		for (int i = 1; i <= n; i++)
			cout << " " << i;
		cout << endl;
		cout << endl;
		for (int i = 0; i < n; i++) {
			cout << i+1<<" ";
			for (int j = 0; j < n;j++)
				cout << a[i][j] << " ";
			cout << endl;
		}

	}

	int count_roads(bool** a, int n, bool** visited, int now, int end, int S) {
		if (now == end) {
			return ++S;
		}
		for (int i = 0; i < n; i++) {
			if (i != now && visited[now][i] != 1 && a[now][i] == 1) {
				visited[i][now] = 1;
				visited[now][i] = 1;
				S += count_roads(a, n, visited, i, end);
				visited[now][i] = 0;
				visited[i][now] = 0;
			}
		}
		return S;
	}



	bool check(int n, bool** a, bool**visited, int start, int end) {
		int start_roads = 0, end_roads = 0;
		for (int i = 0; i < n; i++) {
			start_roads += a[i][start - 1];
			end_roads += a[i][end - 1];
		}
		return (start_roads <= 3 || end_roads <= 3 || count_roads(a, n, visited, start-1, end-1, 0) <= 3);
	}
