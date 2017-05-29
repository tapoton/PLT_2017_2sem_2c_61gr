#include "stdio.h"
#include "iostream"
#include "string"
#include <fstream>

using namespace std;

float age_find(string tmp)
{
	float age=0;
	int i = 0;
	while ((tmp[i] < '0') || (tmp[i] > '9'))
	{
		i++;
	}
	age = tmp[i] - '0';
	if ((tmp[i + 1] >= '0') && (tmp[i + 1] <= '9'))
	{
		age = 10 * age + tmp[i + 1] - '0';
		i++;
	}
	if (tmp[i + 1] == '.')
	{
		age = age + float(tmp[i + 2] - '0') / 10;
		if ((tmp[i + 3] >= '0') && (tmp[i + 3] <= '9'))
		{
			age = age + float(tmp[i + 3] - '0') / 100;
		}
	}
	return(age);
}

void group_form(void)
{
	ifstream fin;
	ofstream g1;
	ofstream g2;
	ofstream g3;
	fin.open("input.txt");
	g1.open("g1.txt");
	g2.open("g2.txt");
	g3.open("g3.txt");
	string tmp;
	while(fin)
	{
		getline(fin,tmp);
		if (tmp.length() == 0)
		{
			break;
		}
        float age=age_find(tmp);
		if (age <= 1.5)
		{
			g1<<tmp<<endl;	
		}
		else
		{
			if (age <= 6)
			{
				g2<<tmp<<endl;
			}
			else
			{
				g3<<tmp<<endl;
			}
		} 
	}
	fin.close();
	g1.close();
	g2.close();
	g3.close();	
}

void group_trans(ifstream &fin, ofstream &fout)
{
	string tmp;
	while(fin)
	{
		getline(fin, tmp);
		fout<<tmp<<endl;		
	}
}

void group_merge(void)
{
	ofstream fout;	
	ifstream g1;
	ifstream g2;
	ifstream g3;
	fout.open("output.txt");
	g1.open("g1.txt");
	g2.open("g2.txt");
	g3.open("g3.txt");
	fout<<"Группа 0-1.5 лет"<<endl;
	group_trans(g1, fout);
	g1.close();
	fout<<"Группа 1.5-6 лет"<<endl;
	group_trans(g2, fout);
	g2.close();
	fout<<"Группа 6+ лет"<<endl;
	group_trans(g3, fout);
	g3.close();
	fout.close();
}

void file_remove(void)
{
	remove("g1.txt");
	remove("g2.txt");
	remove("g3.txt");
}

int main()
{
	setlocale(LC_ALL, "Russian");
	group_form();
	group_merge();
	file_remove();	
}
