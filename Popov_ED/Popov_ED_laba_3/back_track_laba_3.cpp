#include <iostream>

using namespace std;

class Roads {

	bool** visited;

	int count_roads(bool** a, int n, bool** visited, int current, int end, int S = 0) {   //количество выходящих дорог из города
		if (current == end) {
			return ++S;
		}
		for (int i = 0; i < n; i++) {
			if (i != current && visited[current][i] != 1 && a[current][i] == 1) {
				visited[i][current] = 1;
				visited[current][i] = 1;
				S += count_roads(a, n, visited, i, end);
				visited[current][i] = 0;
				visited[i][current] = 0;
			}
		}
		return S;
	}


public:

	void init(int n, bool** a) { //инициализация посещенных дорог
		visited = new bool *[n];
		for (int i = 0; i < n; i++) {
			visited[i] = new bool[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				visited[i][j] = 0;
			}
		}
	}

	void output(int n, bool** a) {  //вывод графа
		for (int i = 1; i <= 2 * n; i++) {
			if (i % n == 1) {
				cout << "    ";
				if (i <= n) {
					cout << i;
				}
				else {
					cout << "-";
				}
			}
			else {
				if (i <= n) {
					cout << "  " << i;
					if (i == n) {
						cout << endl;
					}
				}
				else {
					cout << "---";
				}
			}
		}
		cout << endl;

		for (int i = 0; i < n; i++) {
			cout << i + 1 << "|  ";
			for (int j = 0; j < n; j++) {
				cout << a[i][j] << "  ";
			}
			if (i + 1 == n) {
				cout << endl;
			}
			else {
				cout << endl << " |" << endl;
			}
		}
		cout << endl;
	}

	void input(int n, bool** a, int &start, int &end) { //выбор дорог между городами которые будут удалены
		char c = ' ';
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				while (c != 'Y' && c != 'N') {
					cout << "Is there a road between cities " << i + 1 << " and " << j + 1 << "? (Y/N): ";
					cin >> c;
					if (c != 'Y' && c != 'N') {
						cout << "Wrong! Try again!" << endl;
					}
				}
				if (c == 'Y') {
					a[i][j] = 1;
					a[j][i] = 1;
				}
				else {
					a[i][j] = 0;
					a[j][i] = 0;
				}
				c = ' ';
			}
		}
		for (int i = 0; i < n; a[i][i] = 0, i++);
		cout << endl;

		output(n, a);

		while (start < 1 || start > n) {
			cout << "Enter the number of the initial city: ";
			cin >> start;
			if (start < 1 || start > n) {
				cout << "Wrong! Try again!" << endl;
			}
		}
		while (end < 1 || end > n) {
			cout << "Enter the number of the final city: ";
			cin >> end;
			if (end < 1 || end > n) {
				cout << "Wrong! Try again!" << endl;
			}
		}
		cout << endl;

	}

	int count_roads(bool** a, int n, int start, int end) {
		start -= 1;
		end -= 1;
		return count_roads(a, n, visited, start, end);
	}

	bool is_possible(int n, bool** a, int start, int end) { 
		int start_roads = 0, end_roads = 0;
		for (int i = 0; i < n; i++) {
			start_roads += a[i][start - 1];
			end_roads += a[i][end - 1];
		}
		return (start_roads <= 3 || end_roads <= 3 || count_roads(a, n, start, end) <= 3);
	}

};

int main() {

	Roads obj;

	int n = 0;
	while (n < 3) {
		cout << "Enter the number of cities: ";
		cin >> n;
		if (n < 3) {
			cout << "Wrong! Try again!" << endl;
		}
	}
	cout << endl;
	bool** a = new bool *[n];
	for (int i = 0; i < n; i++) {
		a[i] = new bool [n];
	}

	int start = 0, end = 0;
	obj.input(n, a, start, end);
	
	obj.init(n, a);
	
	if (!obj.is_possible(n, a, start, end)) {
		cout << "YES! If you close any 3 ways, you won't be able to get from city " << start << " to city " << end << endl;
	}
	else {
		cout << "NO! If you close any 3 ways, you will be able to get from city " << start << " to city " << end << endl;
	}
	
	system("pause");
	return 0;
}
