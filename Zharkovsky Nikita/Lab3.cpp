/*
Жарковский Никита 2к 61гр 
Лабараторная 3
11. По системе двусторонних дорог определить есть ли в ней город, 
из которого можно добраться в любого другого не более чем за 100 км. Разрешается построить дополнительно 3 дороги.
*/

#include <iostream>
#include <set>
using namespace std;

int n, MAX=100;
set<int> answer; //ответ(вершины, из которых можно добраться до остальных)
int **g; //граф
bool *used;
int root; //корневой эл-т для которого вызывается рекурсивная ф-ия и в последствии данная переменная используется для записи ответа

//рекурсивная функция
void back(int v, int sum = 0) 
{
	if(sum > MAX) return; //условие выхода
	used[v] = true;
	for(int i = 0; i < n; i++)
	{
		if(!used[i]) 
		{
			if(g[v][i] > 0 && sum + g[v][i] <= MAX)
			    back(i, sum + g[v][i]);
		}
	}
	//проверка на конечность работы алгоритма
	bool ans = 1;
	for(int i = 0; i < n && ans; i++)
		if(!used[i]) ans = 0;
	//если пройдены все вершины, заносим в ответ root
	if(ans) answer.insert(root);
}

//для каждой вершины рекурсивно проверяем достижимость всех дорог на расстоянии 100км
void solution()
{
	for(int i = 0; i < n; i++)
	{
		root = i;
		back(i); //вызов рекурсивной функции
		for (int j = 0; j < n; j++) //обнуление массива used
			used[j] = false;
	}
}

//ф-ия вставки записи в граф
void insert(int s,int to, int x)
{
	g[s-1][to-1] = g[to-1][s-1] = x;
}
int main()
{
	//считывание данных, выделение памяти
	int m;
	cout << "Enter the number of vertices and edges (n,m):";
	cin >> n >> m;
	g = new int *[n];
	used = new bool[n];
	for(int i = 0; i < n; i++)
	{
		g[i] = new int[n];
		for(int j = 0; j < n; j++) g[i][j] = 0;
		used[i] = 0;
	}
	cout << "Enter edges (from,to,distance):" << endl;
    for(int i = 0, a, b, c; i < m; i++)
    {
    	cin >> a >> b >> c;
    	insert(a, b, c);
	}
	
	// перебор всевозможных расстоновок трех дополнительных дорог в системе дорог
	// и вызов рекурсивной функции для каждой расстоновки
	// (данный способ эффективен тем, что не забивается рекурсия при различных комбинациях доп.дорог)
	
	// p.s. в решении подразумевается что доп.дороги можно строить между городами, 
	// которые либо соединены, либо нет, причем эти дороги могут быть min длины, т.е 1 
	for(int i1 = 0; i1 < n; i1++)
	{
		for(int j1 = 0; j1 < n; j1++)
		{
			for(int i2 = i1 + 1; i2 < n; i2++) 
			{
				for (int j2 = 0; j2 < n; j2++)
				{
					for (int i3 = i2 + 1; i3 < n; i3++)
					{
						for (int j3 = 0; j3 < n; j3++)
						{
							int temp1 = g[i1][j1], temp2 = g[i2][j2], temp3 = g[i3][j3];
							g[i1][j1] = g[j1][i1] = 1;
							g[i2][j2] = g[j2][i2] = 1;
							g[i3][j3] = g[j3][i3] = 1;
							solution(); 
							g[i1][j1] = g[j1][i1] = temp1;
							g[i2][j2] = g[j2][i2] = temp2;
							g[i3][j3] = g[j3][i3] = temp3;
						}
					}
				}
				
			}
		}
	}
	
	//вывод ответа
	if(answer.empty()) cout << "NO";
	else cout << "YES: ";
	for (set<int>::iterator it = answer.begin(); it != answer.end(); it++)
		cout << *it+1 << " ";
}
