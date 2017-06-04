#include <iostream>
#include <fstream>
#include <cstring>
#include <io.h>
#include <sys/stat.h>
#include <cmath>
#include <conio.h>

using namespace std;

void show(const int n, int arr[])
{
		for (int i=0; i<n; i++)
	{
		cout<<arr[i]<<" ";
	}
}

void selectSort(int size, int* arr) 
{
    int tmp;
    for(int i = 0; i < size; ++i) 
    { 
        int pos = i; 
        tmp = arr[i];
        for(int j = i + 1; j < size; ++j) 
        {
            if (arr[j] < tmp) 
           {
               pos = j; 
               tmp = arr[j]; 
           }
        }
        arr[pos] = arr[i]; 
        arr[i] = tmp; 
    }
}

void CreateMass(int n, char *matrix, char *matrix_2, char *pob_diag)
{
	ifstream in(matrix);
	ofstream out(matrix_2);
	int a;
	int arr[n];
	int i=0, j=0;
		
	do
	{
		while(i!=n&&!in.eof())
		{
			i++;
			in>>a;
			if (n-j==i) arr[j]=a;  
			else
				if (j!=n)
				{	
					out<<a<<' ';
				}		
		}
		out<<'\n';
		j++; i=0;
	}while(!in.eof());
	selectSort(n,arr);
	cout<<"\nPobochnaya diagonal"<<endl;
	show(n,arr);
	ofstream s_3(pob_diag);
	for (int k=0; k<n; k++)
	s_3<<arr[k]<<' ';
	
	s_3.close();	
	in.close();
	out.close();
}

int getFileSizeMatrix(char * fileName)
{
	ifstream in(fileName);
	int i=0;
	int ch;
    while(!in.eof())
    {
    	i++;
    	in>>ch;
	}
	in.close();
	return i;
}

int merge1(char *s1, char *s2, char *s3)
{
	int p_s_1=getFileSizeMatrix(s1)-1;	
		int p_s_2=getFileSizeMatrix(s2)-1;
		int i1=0, i2=0;
		int a, b;
		fstream s_1(s1);
		fstream s_2(s2);
		ofstream s_4(s3);
		s_1>>a;
		s_2>>b;
		while (!s_1.eof()||!s_2.eof())	
		{
			if (a<=b) 
				{
					if (i1<p_s_1)
						{
							s_4<<a<<' ';
							s_1>>a;
							i1++;
						}
					else 
					{
						s_4<<b<<' ';
						s_2>>b;
					}
				}
			else 
				{
					if (i2<p_s_2)
						{
							s_4<<b<<' ';
							s_2>>b;
							i2++;
						}
					else 
					{
						s_4<<a<<' ';
						s_1>>a;
					}	
				}
		}
		s_1.close();
		s_2.close();
		a=getFileSizeMatrix(s2)-1;
		s_4.close();
		return a;
}

void razd(char *s1, char *s2, char *s3, int n)
{
		ifstream s_3(s3);
		ofstream  s_1(s1);
		ofstream  s_2(s2);
		
			int j=0, a, b, key=0;

			s_3>>a;	
			while(j<n)
			{
				s_3>>b;
				if (key==0)
				{	
				if (a<=b) 
					{
						s_1<<a<<' ';
						a=b;
					}
					else 
					{
						key=1;
						s_1<<a<<' ';
						a=b;
						s_3>>b;
						j++;	
					}
				}
				if (key==1&&j<n)
				{
				if (a<=b) 
					{
						s_2<<a<<' ';
						a=b;
					}
					else 
					{
						key=0;
						s_2<<a<<' ';
						a=b;											
					}
				}
			j++;
			}
		s_1.close();	
		s_2.close();
		s_3.close();
}

void Merge( int n, char *matrix_2, char *pob_diag, char *s1, char *s2,  char *s3, char *matr_preobr)
{
	
	ifstream p_d(pob_diag);
	ifstream out(matrix_2);
	ofstream m_p(matr_preobr);

		for(int i=0; i<n; i++)
		{

			ofstream s_1(s1);
			ofstream s_2(s2);
			int j=0, a, b, key=0;
			p_d>>a;	
			do
			{	
				out>>b;
				switch (key)
				{
					case 0:
						{	
							if (a<=b) 
								{
									s_1<<a<<' ';
									a=b;
								}
							else 
								{
									key=1;
									s_1<<a<<' ';
									a=b;
								}
						}; break;
					case 1:
						{
							if (a<=b) 
								{
									s_2<<a<<' ';
									a=b;
								}
								else 
								{
									key=0;
									s_2<<a<<' ';
									a=b;											
								}
						} break;
			}
			j++;
			}while(j<n-1);
		s_1<<b<<' ';
		s_1.close();	
		s_2.close();
		
		int p_s_2=getFileSizeMatrix(s2)-1;
		while (p_s_2>0)
		{
		p_s_2=merge1(s1, s2,s3);
		razd(s1, s2, s3, getFileSizeMatrix(s3)-1);	
		}
		
		int p_s_3=getFileSizeMatrix(s3)-1;
		int k=0;
		ifstream s_3(s3);
		while (k!=p_s_3)
		{
			s_3>>a;
			m_p<<a<<' ';
			k++;
		}
		s_3.close();
		m_p<<'\n';	
	}
	m_p.close();
	out.close();
	p_d.close();
	remove(pob_diag); remove(s1);	remove(s2); remove(s3); remove(matrix_2); 
}

int main()
{	
	int n=getFileSizeMatrix("matrix.dat"); //razmernosty;
	n=sqrt(n);
	CreateMass(n, "matrix.dat", "matrix_2.dat", "pob_diag.dat"); 	//pobochnaya diagonal
	
	Merge(n,"matrix_2.dat", "pob_diag.dat", "s1.dat", "s2.dat", "s3.dat", "matr_preobr.dat");
	
	return 0;
}
