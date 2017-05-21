#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

char* Prois(char *begfile) //creation of the file with indexes and products of numbers(proiswedenie)

{
    char *inpr="indexandprois.txt";
    ifstream fin(begfile);
    ofstream fout(inpr);
    int m;
    fin>>m;
    for (int ind=0; ind<m; ind++)
    {
        int n,x,prois=1;
        fin>>n;
        for (int  i = 0, x; i < n; i++)
        {
           for  (int j = 0; j<n; j++)   
             {
                fin >> x;
                prois*=x;
	   }
        }
        fout<<ind<<" "<<prois <<" ";
    }
    fout.close();
    fin.close();
    return inpr;
}

void Sort(char *name) //sorting by simple merge
{
    int i1,i2,a1,a2,i,j,k=1,kol=0;
    fstream f,f1,f2;
    f.open(name,ios::in);
    if(!f)
    {
       cout<<"Error"<<endl;
       return;
    }    	
    while (!f.eof())  //determination of quantity of series(index,proiswedenie)
    {    
       f>>i1>>a1;
       kol++;      
    }
    f.close(); 
    while (k<kol)
    {
       f.open(name,ios::in); //splitting file
       f1.open("file1_sort.txt",ios::out);
       f2.open("file2_sort.txt",ios::out);
       if (!f.eof())
        f>>i1>>a1;
       while (!f.eof())
       {
          for ( i = 0; i < k && !f.eof() ; i++ )
          {
              f1<<i1<<" "<<a1<<" ";
              f>>i1>>a1;
          }
          for ( j = 0; j < k && !f.eof() ; j++ )
          {
              f2<<i1<<" "<<a1<<" ";
              f>>i1>>a1;
          }
       }
       f.close();f1.close();f2.close();

       f.open(name,ios::out); //merge of the file
       f1.open("file1_sort.txt",ios::in);
       f2.open("file2_sort.txt",ios::in);
       if ( !f1.eof() )
        f1>>i1>>a1;
       if ( !f2.eof() )
        f2>>i2>>a2;
       while ( !f1.eof() && !f2.eof() )
       {
          i = 0;
          j = 0;
          while ( i < k && j < k && !f1.eof() && !f2.eof() )
          {
              if ( a1>a2 )
              {
                  f<<i1<<" "<<a1<<" ";
                  f1>>i1>>a1;
                  i++;
              }
              else
              {  
                  f<<i2<<" "<<a2<<" ";
                  f2>>i2>>a2;
                  j++;
              }
          }
          while ( i < k && !f1.eof())
          {
              f<<i1<<" "<<a1<<" ";
              f1>>i1>>a1;
              i++;
          }
          while ( j < k && !f2.eof())
          {
              f<<i2<<" "<<a2<<" ";
              f2>>i2>>a2;
              j++;
          }
      }
      while ( !f1.eof() )
      {
          f<<i1<<" "<<a1<<" ";
          f1>>i1>>a1;
      }
      while ( !f2.eof() )
      {
         f<<i2<<" "<<a2<<" ";
         f2>>i2>>a2;
      }
      f.close();f1.close();f2.close();
      k*=2;
   }
   remove("file1_sort.txt");
   remove("file2_sort.txt");
}

char* FindMatrix(char*begfile,char*inpr,char*endfile) //creation of the output file
{
 fstream fb,fi,fe;
 int index,kolmatr,n,x,curindex;
 fi.open(inpr, ios::in); 
 fe.open(endfile,ios::out);
 fi>>index;
 while(!fi.eof())
 { 
   fb.open(begfile, ios::in);
   fb>>kolmatr;
   for(curindex=0;curindex<kolmatr && curindex<index; curindex++)
   {
    fb>>n;
    for(int i=0;i<n*n;i++)
      fb>>x;
   }
   if(curindex!=index) return "FALSE";
   fb>>n;
   for(int i=0;i<n;i++)
   {
    for(int j=0;j<n;j++)
     {
       fb>>x;
       fe<<x<<" ";
     }
     fe<<"\n";
   } 
   fe<<"\n";
   fi>>index;
   fi>>index;   //propusk proiswedenia
   fb.close();   
 }
 fi.close();
 fe.close();
 remove(inpr);
 return endfile;
}
 
int main()
{
  char *begfile="f1.txt";  //f1-input file
  char *inpr=Prois(begfile);  
  Sort(inpr);
  char *endfile=FindMatrix(begfile,inpr,"f2.txt"); 
  cout<<"Output file:"<<endfile<<endl;
  system("pause");
  return 0;
}

