#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

struct position
{
	int pos;
	int sqr;
};

int SQR(int *a, int n)
{
	int sqr = 1;
	for (int i = 0; i < n; i++)
		sqr *= a[i];
	return sqr;
}

void SimpMergSort(position *mas, int kol)
{
	fstream f;
	f.open("f.txt", ios::out);
	for (int i = 0; i < kol; i++)
	{
		f << mas[i].sqr << ' ' << mas[i].pos << ' ';
	}
	f.close();
	position a1, a2;
	int k = 1;
	while (k < kol)
	{
		fstream f1;
		fstream f2;
		f.open("f.txt", ios::in);
		f1.open("f1.txt", ios::out);
		f2.open("f2.txt", ios::out);
		if (!f.eof())
		{
			f >> a1.sqr >> a1.pos;
		}
		while (!f.eof())
		{                           
			for (int i = 0; i < k && !f.eof(); i++)
			{
				f1 << a1.sqr << ' ' << a1.pos << ' ';
				f >> a1.sqr >> a1.pos;
			}
			for (int j = 0; j < k && !f.eof(); j++)
			{
				f2 << a1.sqr << ' ' << a1.pos << ' ';
				f >> a1.sqr >> a1.pos;
			}
		}
		f.close();
		f1.close();
		f2.close();
		f.open("f.txt", ios::out);
		f1.open("f1.txt", ios::in);
		f2.open("f2.txt", ios::in);
		if (!f1.eof())
		{
			f1 >> a1.sqr >> a1.pos;
		}
		if (!f2.eof())
		{
			f2 >> a2.sqr >> a2.pos;
		}
		while (!f1.eof() && !f2.eof())
		{                                        
			int i = 0, j = 0;
			while (i < k && j < k && !f1.eof() && !f2.eof())
			{
				if (a1.sqr < a2.sqr)
				{
					f << a1.sqr << ' ' << a1.pos << ' ';
					f1 >> a1.sqr >> a1.pos;
					i++;
				}
				else
				{
					f << a2.sqr << ' ' << a2.pos << ' ';
					f2 >> a2.sqr >> a2.pos;
					j++;
				}
			}
			while (i < k && !f1.eof())
			{
				f << a1.sqr << ' ' << a1.pos << ' ';
				f1 >> a1.sqr >> a1.pos;
				i++;
			}
			while (j < k && !f2.eof())
			{
				f << a2.sqr << ' ' << a2.pos << ' ';
				f2 >> a2.sqr >> a2.pos;
				j++;
			}
		}
		while (!f1.eof())
		{
			f << a1.sqr << ' ' << a1.pos << ' ';
			f1 >> a1.sqr >> a1.pos;
		}
		while (!f2.eof())
		{
			f << a2.sqr << ' ' << a2.pos << ' ';
			f2 >> a2.sqr >> a2.pos;
		}
		f.close();
		f1.close();
		f2.close();
		k *= 2;
	}
}


int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	remove("result.txt");
	remove("f.txt");

	ifstream fin("input.txt");
	int m, n;
	fin >> m >> n;

	int **matr = new int*[m];
	for (int i = 0; i < m; i++)
		matr[i] = new int[n];

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fin >> matr[i][j];
		}
	}
	fin.close();

	cout << "Исходная матрица:" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%5d ", matr[i][j]);
		printf("\n");
	}

	position *p = new position[m];
	for (int i = 0; i < m; i++)
	{
		p[i].pos = i;
		p[i].sqr = SQR(matr[i], n);
	}

	SimpMergSort(p, m);

	int k, l;
	fstream f;
	f.open("f.txt", ios::in);
	ofstream f2out("output.txt");

	for (int i = 0; i < m; i++)
	{
		f >> k >> l;
		for (int j = 0; j < n; j++)
		{
			f2out << matr[l][j] << ' ';
		}
		f2out << "\r\n";
	}
	f.close();
	f2out.close();

	cout << "Отсортированная матрица:" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%5d ", matr[i][j]);
		printf("\n");
	}

	system("PAUSE");
	return 0;
}
