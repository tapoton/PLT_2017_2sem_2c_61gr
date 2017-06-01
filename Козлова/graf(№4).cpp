#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

bool verifdata(int **,int ); //verification of data
void init(int *,int);     //zeroing of parents
int Kruskal(int **,int*,int); //search of weight
int **Matrix(int &n); //count's task
bool prover(int ,int,int* );

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
  mas[i]=i;
}

int Kruskal(int **mas,int *parent,int n)
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
  if(prover(in,jn,parent))
  {
   cout<<"edge ("<<(in+1)<<","<<(jn+1)<<")="<<min<<endl;
   weight+=min;
   int tmp=parent[jn];
   for(int i=0;i<n;i++)
    if(parent[i]==tmp) parent[i]=parent[in];
   --nprob;
  }
  mas[in][jn]=0;
  mas[jn][in]=0;
 }
 return weight;
}

bool prover(int i,int j,int *parent)
{
  if(parent[i]!=parent[j]) return 1; 
  return 0;
}

