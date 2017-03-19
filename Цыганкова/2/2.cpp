/*
Tsygankova Elizaveta 2 c 61 g 
Lab №2: Create a module that realising methods of work with the hash-table:
initialization, adding item, deleting item, searchig. 
Moreover, when the table is filled above a given level its size shall be automatically increased.
*/
#include <cstdlib>
#include <iostream>
#include <fstream>

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


int hesh(int key)
/*
Hash function
*/
{
  return key % 10;
}


void print(int size)
{
  tablenode *T1 = Begin;
  cout<<"\n Таблица: ";   
  for(int i=0; i<size; i++)
    if(T1[i].emp==1)       
      cout<<T1[i].x<<" "; 
    else
      cout<<"пусто  ";
  cout<<endl;
}


void addelem(int dat,int size, bool &noexp)   
/*
Adding an element
noexp - flag of table fullness
*/   
{    
  tablenode *T2=Begin;   
  int i=hesh(dat);
  if(!T2[i].emp)                 //if unit empty
  {
    T2[i].x=dat;
    T2[i].emp=1; 
  }      
  else
  {
    int k=i;
    i++;
    bool t=0;
    while(!t && i!=k)             //linear search
    {       
      if(!T2[i].emp)
      {  
        T2[i].x=dat;
        T2[i].emp=1;
        t=true;
      }
      i++;
      if(i>=size)             
        i=0; 
    }
    if(!t)                        //if table is full
      noexp=0; 
  }
} 


void expand(int dat,  int &size)
/*
Table expanding
Increases table for 10 units. 
*/           
{  
  tablenode *T3=Begin;            
  tablenode *Tmp= new tablenode[size+10]; 
  Init(Tmp,size+10);
  
  for(int j=10,i=0; j<size+10,i<size; j++,i++ )
  {          
    Tmp[j].x=T3[i].x;
    Tmp[j].emp=T3[i].emp; 
  } 
  size=size+10; 
  int k=hesh(dat);
  Tmp[k].x=dat;
  Tmp[k].emp=1; 
}



int search (int dat, int size)
/*
Search an index by key(dat)
*/
{
  tablenode *Begin3 = Begin;    
  int l = hesh(dat);
  if( Begin3[l].emp &&  Begin3[l].x == dat)
    return l;
  else                                            //if enother key in this unit
  {  
    int k=l;
    l++;
    while(l!=k)                                   //linear search
    {       
      if(Begin3[l].x == dat)
        return l;
      l++;
      if(l>=size)             
        l=0; 
    }
    cout<<"Такого элемента в таблице нет."<<endl;                     
    return -1;
  }  
}


void keydelete(int dat, int size)
/*
Deleting element
*/
{
  int ind = search(dat,size);
  if (ind > 0)
  {
    tablenode *Begin4 = Begin; 
    Begin4[ind].emp = 0;
    Begin4[ind].x = 0;      
  }      
}



int main()
{
  setlocale(LC_ALL,"Russian"); 
  
  int size = 10; 
  tablenode *Table=new tablenode[size];
  Init(Table,size);                                                 
  
  int dat;
  
  ifstream fin("f1.txt");             
                                             
  while (fin>>dat)                                     //filling
  {   
    bool y=1;             
    addelem(dat,size,y);                                   
    if(!y)      
      expand(dat,size);                  
  }  
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
