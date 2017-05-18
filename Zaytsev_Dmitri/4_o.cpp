#include "stdio.h"
#include "iostream"
#include "string"
#include "float.h"

using namespace std;

int Num;

void input(float *m)
{
	setlocale(LC_ALL, "Russian");
	float temp;
	for (int i = 0 ; i < Num ; ++i)
	{
		cout<< "Введите строку № " << i+1<<":"<<endl;
		for (int j = 0; j < Num ; ++j)
		{
			cin>>temp;
			if (temp == -1)
			{
				temp=FLT_MAX;
			}
			*( m + i * Num + j) = *( m + j * Num + i) = temp;
		}
		cout<< endl;
	}
}

void optim(float *m)
{
	for (int k = 0 ; k < Num ; ++k)
	{
		for (int i = 0 ; i < Num ; ++i)
		{
			for (int j = i + 1 ; j < Num ; ++j)
			{
				if ((*( m + i * Num + k) > 0) && (*( m + k * Num + j) > 0))
				{
					*( m + j * Num + i) = *( m + i * Num + j) = min(*( m + i * Num + j), *( m + i * Num + k) + *( m + k * Num + j));
				}
			}
		}
	}
}

float find_max(float *m)
{
	float max=0;
	for (int i = 0 ; i < Num ; ++i)
	{
		for(int j = i + 1 ; j < Num ; ++j)
		{
			if ( ( max < *( m + j * Num + i)) && (*( m + j * Num + i) != FLT_MAX) )
			{
				max=*( m + j * Num + i);
			}
		}
	}
	return ( max );
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout<< "Введите количество вершин: ";
	cin>> Num;
	float m[Num][Num];
	string name[Num];
	input(*m);
	optim(*m);
	float max;
	max = find_max(*m);
	cout<<endl<<"Максимальное расстояние = "<<max<<endl;
}
