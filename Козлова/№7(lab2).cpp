#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
int tablesize;
 
struct Node{
 string FIO;
 string mark;
 string key;
 Node *next;
}**hashTable;
 


int hash_(string key);
void insertNode(string FIO,string mark,string key);
void findNode (string key);
void Create_tab();
void Del_tab();


int main()
{
  int i,maxnum,x;
  string k,f,m;
  bool fl=1;
  cout<<"Use Latin letters at cin"<<endl;
  cout<<"Count of data: "; 
  cin>>maxnum;
  cout<<"Size of hash table: ";
  cin>>tablesize;
  Create_tab();
  //filling of the table
  for (i = 0; i < maxnum; i++)
  { 
  cout<<(i+1)<<")"<<endl;
  cout<<"Number of the car(key):";
  cin>>k;
  cout<<"FIO:";
  cin>>f;
  cout<<"Model of the car:";
  cin>>m;
  insertNode(f,m,k);
  }
  while(fl)
  {
   cout<<"\nChoose:1.To find data on a key  2.Exit:";	
   cin>>x;
   switch(x)
   {
     case 1:
      cout<<"Enter number of the car(key):";
      cin>>k;findNode(k);
     break;
     case 2:
      fl=0;
     break;
     default:
      cout<<"False"<<endl; 
      fl=0;
     break;	
   }	
  }
  Del_tab(); 
  system("pause");
  return 0;
}



//creation of the hash table  
void Create_tab()
{
  hashTable = new Node*[tablesize];
  for (int i = 0; i<tablesize; i++)
    hashTable[i] = NULL;	
}

// hash-function
int hash_(string key)
{
 int sum = 0;
 for(int i=0 ;i<key.length(); i++)
  sum +=key[i];
 return (sum % tablesize);
}

//insert of data (filling of a chain since the beginning)  
void insertNode(string FIO,string mark,string key) 
{
  Node *p=new Node, *p0;
  int hash=hash_(key);
  if (p==0) 
   {
    fprintf (stderr, "Memory contention (insertNode)\n");
    exit(1);
   }
  p0 = hashTable[hash];
  hashTable[hash] = p;
  p->next = p0;
  p->key=key;
  p->mark=mark;
  p->FIO=FIO;
}

//search in a key
void findNode (string k) 
{
  Node *p;
  p=hashTable[hash_(k)];
  while (p && p->key!=k) 
  p = p->next;
  if(!p) {cout<<"key not found"<<endl;return;}
  cout<<"FIO of the owner:"<<p->FIO<<"   Model of the car:"<<p->mark<<endl;
  return;
}


//removal hash table
void Del_tab()
{
 for(int i=0;i<tablesize;i++)
   if(hashTable[i]!=NULL) 
   {
    Node *p;
    while(hashTable[i]!=NULL)
     {
      p=hashTable[i];
      hashTable[i]=hashTable[i]->next;
      delete p;
      p=NULL; 
     }
   }
  delete [] hashTable;		
}
