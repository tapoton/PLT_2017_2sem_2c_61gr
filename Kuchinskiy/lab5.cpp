#include "stdafx.h"
#include <fstream>
#include <iostream>

using namespace std;

char* sum(char *input)
{
	char* temp = "temp.txt";
	ifstream fin(input);
	ofstream fout(temp);
	int count;
	fin >> count;
	for (int index = 0; index < count; index++)
	{
		int size;
		fin >> size;
		int sum = 0;
		for (int i = 0; i < size; i++)
		{
			int tmp;
			for (int j = 0; j < size; j++)
			{
				fin >> tmp;
				if (i == size - 1 - j)
					sum += tmp;
			}
		}
		fout << index << " " << sum << "\n";
	}
	fout.close();
	fin.close();
	return temp;
}

void Sort(char *temp)
{
	int i1, i2, x1, x2, i, j, k = 1, count = 0;
	fstream f, f1, f2;
	f.open(temp, ios::in);
	if (!f)
	{
		cout << "Error" << endl;
		return;
	}
	while (!f.eof())
	{
		f >> i1 >> x1;
		count++;
	}
	f.close();
	while (k<count)
	{
		f.open(temp, ios::in);
		f1.open("f1.txt", ios::out);
		f2.open("f2.txt", ios::out);
		if (!f.eof())
			f >> i1 >> x1;
		while (!f.eof())
		{
			for (i = 0; i < k && !f.eof(); i++)
			{
				f1 << i1 << " " << x1 << "\n";
				f >> i1 >> x1;
			}
			for (j = 0; j < k && !f.eof(); j++)
			{
				f2 << i1 << " " << x1 << "\n";
				f >> i1 >> x1;
			}
		}
		f.close();f1.close();f2.close();

		f.open(temp, ios::out);
		f1.open("f1.txt", ios::in);
		f2.open("f2.txt", ios::in);
		if (!f1.eof())
			f1 >> i1 >> x1;
		if (!f2.eof())
			f2 >> i2 >> x2;
		while (!f1.eof() && !f2.eof())
		{
			i = 0;
			j = 0;
			while (i < k && j < k && !f1.eof() && !f2.eof())
			{
				if (x1<x2)
				{
					f << i1 << " " << x1 << "\n";
					f1 >> i1 >> x1;
					i++;
				}
				else
				{
					f << i2 << " " << x2 << "\n";
					f2 >> i2 >> x2;
					j++;
				}
			}
			while (i < k && !f1.eof())
			{
				f << i1 << " " << x1 << "\n";
				f1 >> i1 >> x1;
				i++;
			}
			while (j < k && !f2.eof())
			{
				f << i2 << " " << x2 << "\n";
				f2 >> i2 >> x2;
				j++;
			}
		}
		while (!f1.eof())
		{
			f << i1 << " " << x1 << "\n";
			f1 >> i1 >> x1;
		}
		while (!f2.eof())
		{
			f << i2 << " " << x2 << "\n";
			f2 >> i2 >> x2;
		}
		f.close();f1.close();f2.close();
		k *= 2;
	}
	remove("f1.txt");
	remove("f2.txt");
}

void print(char* temp, char* input)
{
	ifstream m(input);
	ifstream f(temp);
	ofstream fout("output.txt");
	int index, x, count0, count;
	m >> count0;
	m.close();
	int k = 0;
	char *s = new char[20];
	while (!f.eof()&&k<count0)
	{
		f >> index >> x;
		m.open(input);
		m >> count;
		//fout << "index: " << index << "\n";
		for (int i = 0;i < index; i++)
		{
			m >> count;
			for (int j = 0;j <=count;j++)
				m.getline(s,20);
		}
		m >> count;
		//fout <<"size:" <<count << "\n";
		for (int j = 0;j <=count;j++)
		{
			m.getline(s, 20);
			fout << s<<"\n";
		}
		//fout << "\n";
		m.close();
		k++;
	}
	f.close();
	fout.close();
	//remove(temp);
}


int main()
{
	char *input = "input5.txt";
	char *temp = sum(input);
	char *fn1 = "f1.txt";
	char *fn2 = "f2.txt";
	Sort(temp);
	print(temp, input);
}
