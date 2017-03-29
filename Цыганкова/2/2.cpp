/*
Tsygankova Elizaveta 2 c 61 g 
Lab №2: Create a module that realising methods of work with the hash-table:
initialization, adding item, deleting item, searchig. 
Moreover, when the table is filled above a given level its size shall be automatically increased.
*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

struct tablenode
{
 int x;
 bool emp;                //flag of unit emptyness
}; 
tablenode *Begin;         //pointer to a table



void Init (tablenode *T,int size)    
/*
Initialization
*/
{
 for(int i=0; i<size; i++)
 {
   T[i].emp=0; 
   T[i].x=0;
 }
 Begin=T;
}



int hash(int key, int s)
/*
Hash function
*/
{
  return key % s;
}



void print(int size)
{
  tablenode *T = Begin;
  int otv;
  cout<<"Введите 1, если хотите вывод с 'пустыми'= п полями или 2 - без них: ";
  cin>>otv;
  cout<<"\n Таблица: ";
  switch (otv)
  {
    case 1 :
    {
     for(int i=0; i<size; i++)
     if(T[i].emp==1)       
      cout<<T[i].x<<" "; 
     else
      cout<<"п  ";    
     break;}
    
    case 2 :
    {
     for(int i=0; i<size; i++)
     if(T[i].emp==1)       
      cout<<T[i].x<<" ";     
     break;}    
  }  
cout<<endl;
}




void expand(int dat,  int &size, int step)
/*
Table expanding
Increases table for 10 units. 
*/           
{  
  int size1 = size + step;           
  tablenode *T=Begin;            
  tablenode *Tmp= new tablenode[size1]; 
  Init(Tmp,size1);
  
  for(int i=0; i<size; i++ )
  {       
    int j= hash(T[i].x,size1);              
    Tmp[j].x=T[i].x;
    Tmp[j].emp=T[i].emp; 
  } 
  size=size1; 
  int k=hash(dat,size);
  if(!T[k].emp)                 //if unit empty
  {
    T[k].x=dat;
    T[k].emp=1; 
  }
  else 
    expand(dat,size, step);             
}




void addelem(int dat,int &size, int step)   
/*
Adding an element
*/   
{    
  tablenode *T=Begin;   
  int i=hash(dat,size);
  if(T[i].x==dat)
    return;
  if(!T[i].emp)                 //if unit empty
  {
    T[i].x=dat;
    T[i].emp=1; 
  }      
  else
    expand(dat,size,step);
     
} 



int search (int dat, int size)
/*
Search an index by key(dat)
*/
{
  tablenode *T = Begin;    
  int l = hash(dat,size);
  if( T[l].emp &&  T[l].x == dat)
    return l;
  cout<<"Такого элемента в таблице нет."<<endl;                     
  return -1;
}



void keydelete(int dat, int size)
/*
Deleting element
*/
{
  int ind = search(dat,size);
  if (ind > 0)
  {
    tablenode *T = Begin; 
    T[ind].emp = 0;
    T[ind].x = 0;      
  }      
}



int main()
{
  setlocale(LC_ALL,"Russian"); 
  
  int size,step,kol;
  cout<<"Введите первоначальный размер таблицы: ";
  cin>>size;
  step = size;
  cout<<"Введите количество элементов: ";
  cin>>kol;
  
  tablenode *Table = new tablenode[size];
  Init(Table,size);     
  
  srand ( time(NULL) );                     

  ofstream fout("f1.txt");
  for(int i=0; i<kol; i++)
    fout<<rand() % 500 << " ";
  fout.close();    
                                                                     
  int dat;
  
  ifstream fin("f1.txt");             
  while (fin>>dat)                                     //filling       
    addelem(dat,size,step);                                   
  fin.close(); 
      
  print(size);
  
  int h;
  cout<<endl<<"Введите значение которое хотите найти в таблице: ";
  cin>>h;
  if(search (h, size) >= 0)
    cout<<"Индекс этого значения: "<<search (h, size)<<endl;
    
  cout<<endl<<"Введите значение которое хотите удалить из таблицы: ";
  cin>>h;
  keydelete(h, size);
  print(size);
  
    system("PAUSE");
    return EXIT_SUCCESS;
}
