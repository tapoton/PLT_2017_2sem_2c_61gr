#include "stdio.h"
#include "float.h"
#include "iostream"
#include "string"

using namespace std;

int City_Num,end;
float path_min;

void input(float *m, string *name)
{
	setlocale(LC_ALL, "Russian");
	float temp;
	cin.ignore(1);
	for (int i = 0; i < City_Num ; ++i)
	{
		cout<< "������� �������� " << i + 1 << " ������: ";
		getline(cin , name[i]);
	}
	for (int i = 0 ; i < City_Num ; ++i)
	{
		*( m + i * City_Num + i) = 0;
	}
	for (int i = 0 ; i < City_Num ; ++i)
	{
		for (int j = i + 1; j < City_Num ; ++j)
		{
			cout<< "������� ���������� �� " << name[i] << " �� " << name[j] << " (���� ������ ���, ������� -1) : ";
			cin.ignore(0);
			cin>>temp;
			if (temp == -1)
			{
				temp=FLT_MAX;
			}
			*( m + i * City_Num + j) = *( m + j * City_Num + i) = temp;
		}
	}
}

void optim__(float *m, int now, float path_now, bool *waypoint_)
{
	bool waypoint[City_Num];
	for(int j = 0; j < City_Num; ++j)
	{
		waypoint[j] = waypoint_[j];
	}
	waypoint[now] = 1;
	if (now == end)
	{
		if (path_now < path_min)
		{
			path_min = path_now;
		}
	}
	else
	{
		for(int i = 0; i < City_Num; ++i)
		{
			if ((waypoint[i] == 0 ) && (path_now + *( m + now * City_Num + i) < path_min))
			{
				path_now = path_now + *( m + now * City_Num + i);
				optim__(m, i, path_now, waypoint);
				path_now = path_now - *( m + now * City_Num + i);
			}
		}
	}
}

void optim_(float *m)
{
	bool waypoint[City_Num];
	for(int i = 0; i < City_Num; ++i)
	{
		waypoint[i] = 0;
	}
	float path_now = 0;
	for(int i = 0; i < City_Num; ++i)
	{
		if(i != end)
		{
			path_min = *( m + end * City_Num + i);
			optim__( m, i, path_now, waypoint);
			*( m + i * City_Num + end) = *( m + end * City_Num + i) = path_min;
		}
	}
}

void n_peref(float *m, string *name)
{
	cout<< "������� ������ ������� ���������: ";
	float r;
	cin>>r;
	bool trig = 0;
	string center;
	center = ' ';
	while (!trig)
	{
		cin.ignore();
		cout<< "������� ����� ���������: ";
		getline(cin , center);
		for (int i = 0 ; i < City_Num ; ++i)
		{
			if (!center.compare(name[i]))
			{
				trig = 1;
				end = i;
			}
			if (trig)
			{
				break;
			}
		}
		if(!trig)
		{
			cout<< "������ ������ ���" << endl;
			return;
		}
	}
	trig = 0;
	optim_(m);
	cout<< "�� N-��������� ������ " << name[end] << ": ";
	for (int i = 0 ; i < City_Num ; ++i)
	{
		if ((*( m + end * City_Num + i) > r) && (i != end) && (*( m + end * City_Num + i) != FLT_MAX))
		{
			cout<< name[i] << ", ";
			trig = 1;
		}
	}
	if (!trig)
	{
		cout<< "�����������";
	}
	cout<<endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout<< "������� ���������� �������: ";
	cin>>City_Num;
	float m[City_Num][City_Num];
	string name[City_Num];
	input(*m , name);
	cout<<endl;
	bool trig = 1;
	while (trig)
	{
		cout<< endl << "��������� �� N-���������? (1/0): ";
		cin>>trig;
		if(trig)
		{
			n_peref(*m , name);
		}
	}
}
