#include <iostream>

using namespace std;

const int n=4;
int beg; //initial top(main top)
bool mprob[n]; //array, for a mark - whether the top was used earlier
int x[n][n]=
{
  { 0,20, 1,20},
  { 20,0,30,5 },
  { 1,30,0,40 },
  { 20,5,40,0 },
};

bool Provdwyh(); //whether roads are correctly bidirectional
void initmp(); 
bool back(int &,int); //Search of all tops (recursion) for finding of the closed way
bool Provend(int,int &); //definition of the end of search


int main()
{
 initmp();
 if(Provdwyh())
 {
 beg=0;//definition of initial top
 cout<<"Tops:"<<endl;
 int sum=0;	
 if(!back(sum,beg)) 
  cout<<"NO";	
 else 
  cout<<"\nGeneral distance:"<<sum<<endl;
 }
 else 
  cout<<"Roads are not bilateral"<<endl;
 return 0;	
}

bool Provdwyh()
{
 for(int i=0;i<n;i++)
  for(int j=0;j<n;j++)
   if(x[i][j]!=x[j][i]) 
    return 0;
 return 1;
}

void initmp() 
{
 for(int i=0;i<n;i++)
  mprob[i]=0;
}

bool back(int &sum,int i) //recursive viewing of all tops
{
 bool fl=0;
 mprob[i]=1; //the top - is marked  
 for(int j=0;j<n;j++)
  if(i!=j && x[i][j]!=0 && mprob[j]==0) 
  {
   sum+=x[i][j];
   if(back(sum,j)) 
   {
    cout<<"<-"<<(i+1);
    return 1;
   }
   else 
    sum-=x[i][j];
  }  
 fl=Provend(i,sum);
 if(fl) return 1;
  else mprob[i]=0;
 return 0;
}

bool Provend(int i,int &sum)//definition of the end of search
 {
 if(x[beg][i]!=0) //check of isolation of a way
 {
  sum+=x[beg][i];
  if(sum<100) //the distance has to be<100
  {
   int fl=1; 
   for(int j=0;j<n;j++)
    if(mprob[j]==0)fl=0; //check: whether everything tops have been used
   if(fl)
   {
    cout<<(beg+1)<<"<-"<<(i+1);
    return 1;
   }
  }
 }
 sum-=x[beg][i];
 return 0;
}


