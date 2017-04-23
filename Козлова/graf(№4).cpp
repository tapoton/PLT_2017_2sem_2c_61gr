#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

bool verifdata(int **,int ); //verification of data
void init(int *,int);     //zeroing of parents
int Kruskal(int **,int*,int); //search of weight
int **Matrix(int &n); //count's task

int main()
{
 int n;
 int **matr=Matrix(n);
 cout<<"Matrix:"<<endl;
 int *parent=new int [n];
 init(parent,n);
 for(int i=0;i<n;i++)
 {
   for(int j=0;j<n;j++)
    cout<<setw(5)<<matr[i][j];
   cout<<endl;
 } 
 if(verifdata(matr,n))
 {
  int weight=0;
  weight=Kruskal(matr,parent,n);
  cout<<"\nWeight:"<<weight<<endl;
 }
 else cout<<"\nInput error"<<endl;
 system("pause");
 return 0;	
}

int** Matrix(int &n)
{
 char symb[10];
 ifstream text("flopen1.txt");
 if(!text) 
 {
 	cout<<"False";
 	return NULL;
 }
 text>>symb;
 n=atoi(symb);
 cout<<"N="<<n<<endl;
 int **mas=new int*[n];
 for(int i=0;i<n;i++)
  mas[i]=new int [n];
 for(int i=0;i<n;i++)
  for(int j=0;j<n;j++)
  {
    text>>symb;
    mas[i][j]=atoi(symb);
  }
 return mas;	
}


bool verifdata(int **mas,int n)
{
 for(int i=0;i<n;i++)
  for(int j=i;j<n;j++)
    if(mas[i][j]!=mas[j][i] || mas[i][j]<0 || mas[j][i]<0) 
     return 0;
 return 1;
}

void init(int *mas,int n) 
{
 for(int i=0;i<n;i++)
  mas[i]=0;
}

int Kruskal(int **mas,int *masprob,int n)
{
 int weight=0;
 int nprob=n-1;
 while(nprob>0)
 {
  int in,jn,min=0;
  for(int i=0;i<n;i++)
   for(int j=i+1;j<n;j++)
    if(mas[i][j]>0 && (min==0 || mas[i][j]<min))
    {
     min=mas[i][j];
     in=i;
     jn=j;
    }
   if(masprob[jn]!=0 && masprob[in]==0) 
   {
     int tmp=in;
     in=jn;
     jn=tmp;
   }
   if(masprob[jn]==0 && masprob[in]!=jn)
   {
    if(masprob[in]!=0) masprob[jn]=masprob[in];
     else masprob[jn]=in;
    for(int i=0;i<n;i++)
     if(masprob[i]==jn) masprob[i]=masprob[jn]; 
    weight+=min;
    --nprob;
   }
   mas[in][jn]=0;
   mas[jn][in]=0;
 }
 return weight;
}

