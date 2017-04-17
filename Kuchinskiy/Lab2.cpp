// Lab2.cpp: определ€ет точку входа дл€ консольного приложени€.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cstring>
#include <fstream>
#include <conio.h>


using namespace std;

struct node
{
	char s[50];
	node *next;
};

struct tablenode
{
	char *x;
	int count;                
};
int colCount1 = 0, colCount2 = 0, colCount3 = 0;
tablenode *T1;
tablenode *T2;
tablenode *T3;


void addelem(tablenode *T, char dat[], int &size, int step, int menu);

void Init(tablenode *T, int size)
/*
Initialization
*/
{
	for (int i = 0; i<size; i++)
	{
		T[i].count = 0;
		T[i].x = new char[20];
		T[i].x = "#";
	}
}



int hash1(char key[], int s)
{
	//cout << "HASH1 " << key << endl;
	int h = 0;
	for (int i = 0;key[i] != NULL;i++)
		h += key[i];
	//cout << "hash " << key << " " << h%s << endl;
	return h % s;
}
int hash2(char key[], int s)
{
	//cout << "HASH2 "<<key << endl;
	int h = 0;
	for (int i = 0;key[i] != NULL;i++)
		h = 31 * h + (unsigned char)key[i];
	return h % s;
}
int hash3(char key[], int s)
{
	srand(time(0));
	int r = rand() % 2;
	if (r == 0)
		return hash1(key, s);
	return hash2(key, s);
}



void print(tablenode *T, int size)
{
	int otv;
	cout << "¬ведите 1, если хотите вывод с 'пустыми'= п пол€ми или 2 - без них: ";
	cin >> otv;
	cout << "\n “аблица: ";
	switch (otv)
	{
	case 1:
	{
		for (int i = 0; i < size; i++)
			cout << T[i].x<<" ";
		break;}

	case 2:
	{
		for (int i = 0; i<size; i++)
			if (T[i].count>0)
				cout << T[i].x << " ";
		break;}
	}
	cout << endl;
}

void expand(tablenode *T, char dat[], int &size, int step, int menu)
/*
Table expanding
Increases table for 10 units.
*/

{
	int size0 = size + step;
	tablenode *Tmp = new tablenode[size0];
	Init(Tmp, size0);
	switch (menu)
	{
	case 1: {T1 = Tmp; break;}
	case 2: {T2 = Tmp; break;}
	case 3: {T3 = Tmp; break;}
	}

	for (int i = 0; i < size; i++)
		addelem(Tmp, T[i].x, size0, step, menu);
	size = size0;
	addelem(Tmp, dat, size0, step, menu);
}






void addelem(tablenode *T,char dat[], int &size, int step, int menu)
/*
Adding an element
*/
{
	int i;
	switch (menu)
	{
		case 1: {i = hash1(dat, size); break;}
		case 2: {i = hash2(dat, size); break;}
		case 3: {i = hash3(dat, size); break;}
		default:break;
	}
	//cout << dat<<" "<<i<<" ";
	int j;
	for (j=i;j<size;j++)
		if (T[j].count == 0)
		{
			T[j].count=1;
			T[j].x = dat;
			if (i!=j)
				switch (menu)
				{
					case 1: {colCount1++; break;}
					case 2: {colCount2++; break;}
					case 3: {colCount3++; break;}
					default:break;
				}
			//cout << j <<" fill "<< T[j].x<< endl;
			break;
		}
		else if (strcmp(T[j].x,dat)==0)
		{
			T[j].count=T[j].count+1;
			//cout << j <<" found "<< T[j].x <<endl;
			break;
		}
	//print(T,size);
	if (j == size)
	{
		if (i != j)
			switch (menu)
			{
				case 1: {colCount1 = 0; break;}
				case 2: {colCount2=0; break;}
				case 3: {colCount3=0; break;}
				default:break;
			}
		expand(T, dat, size, step, menu);
	}
	return;

}



int main()
{
	setlocale(LC_ALL, "Russian");
	int kol;
	int size1, size2, size3;
	size1=size2=size3 = 20;
	int step = 10;

	tablenode *Table1 = new tablenode[size1];
	tablenode *Table2 = new tablenode[size2];
	tablenode *Table3 = new tablenode[size3];
	Init(Table1, size1);
	Init(Table2, size2);
	Init(Table3, size3);
	T1 = Table1;
	T2 = Table2;
	T3 = Table3;
	char str[500]="";
	char str1[50];
	ifstream fin("input.txt");
	while (!fin.eof())
	{
		fin.getline(str1, 50);
		strcat(str, " ");
		strcat(str, str1);
	}
	char * pch = strtok(str, " ,.-:;!?()\\n");
	while (pch != NULL)
	{
		pch[0] = (char)tolower(pch[0]);
		addelem(T1, pch, size1, step, 1);
		addelem(T2, pch, size2, step, 2);
		addelem(T3, pch, size3, step, 3);
		pch = strtok(NULL, " ,.-:;!?()\n");
	}
	fin.close();

	print(T1, size1);
	print(T2, size2);
	print(T3, size3);
	cout << size1 << " " << size2 << " " << size3 << endl;
	cout << "Collision Count 1: " << colCount1 << "\nCollision Count 2: " << colCount2 << "\nCollision Count 3: " << colCount3 << "\nAverage Collision Count: " << (colCount1+colCount2+colCount3)/3 << endl;
	_getch();
	return 0;
}
