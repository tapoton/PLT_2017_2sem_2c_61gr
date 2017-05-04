// Lab2.cpp: Count of collisions
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
	tablenode *next;
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
		T[i].next =NULL;
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
	int h = 0;
	for (int i = 0;key[i] != NULL;i++)
		h = 13 * h + (unsigned char)key[i];
	return h % s;
}



void print(tablenode *T, int size)
{
	int otv;
	cout << "Введите 1, чтобы вывести с пустыми ячейками, 2, чтобы вывести без них: ";
	cin >> otv;
	cout << endl;
	switch (otv)
	{
	case 1:
	{
		for (int i = 0; i < size; i++)
		{
			cout << T[i].x << " ";
			tablenode *tmp = T[i].next;
			while (tmp != NULL)
			{
				cout << tmp->x << " ";
				tmp = tmp->next;
			}
		}
		break;}

	case 2:
	{
		for (int i = 0; i < size; i++)
		{
			if (T[i].count>0)
			cout << T[i].x << " ";
			tablenode *tmp = T[i].next;
			while (tmp)
				if (T[i].count>0)
					cout << tmp->x << " ";
		}
		break;}
	}
	cout << endl;
}



int Hash(int menu, char dat[], int size)
{
	int i;
	switch (menu)
	{
	case 1: {i = hash1(dat, size); break;}
	case 2: {i = hash2(dat, size); break;}
	case 3: {i = hash3(dat, size); break;}
	default:break;
	}
	return i;
}

void Collision(int menu)
{
	switch (menu)
	{
	case 1: {colCount1++; break;}
	case 2: {colCount2++; break;}
	case 3: {colCount3++; break;}
	default:break;
	}
}

void addelem(tablenode *T, char dat[], int &size, int step, int menu)
/*
Adding an element
*/
{
	int i= Hash(menu, dat, size);
	
	//cout << dat<<" "<<i<<" ";
	if ((strcmp(T[i].x, dat) == 0) || T[i].count==0)
	{
		T[i].count++;
		T[i].x = dat;
	}
	else
	{
		if (T[i].next == NULL)
		{
			T[i].next = new tablenode;
			T[i].next->x = dat;
			T[i].next->count = 1;
			T[i].next->next = NULL;
			Collision(menu);
		}
		else
		{
			tablenode *tmp = T[i].next;
			while ((strcmp(tmp->x, dat) != 0) && tmp->next)
			{
				tmp = tmp->next;
			}
			if (strcmp(tmp->x, dat) != 0)
			{
				Collision(menu);
				tmp->next = new tablenode;
				tmp = tmp->next;
				tmp->next = NULL;
				tmp->count = 1;
				tmp->x = dat;
			}
			else tmp->count++;
		}
	}
			
}



int main()
{
	setlocale(LC_ALL, "Russian");
	int kol;
	int size1, size2, size3;
	size1 = size2 = size3 = 20;
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
	char str[500] = "";
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
	cout << "Collision Count 1: " << colCount1 << "\nCollision Count 2: " << colCount2 << "\nCollision Count 3: " << colCount3 << "\nAverage Collision Count: " << (colCount1 + colCount2 + colCount3) / 3 << endl;
	_getch();
	return 0;
}
