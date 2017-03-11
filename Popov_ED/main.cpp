// Popov Evgeny 2 course 61 group 
//number words are counting in trie-tree, last consonant words.
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

struct Trie
{
  int value;        //  if current word 0 and if last simbol in word 1  
  char symbol;      
  Trie *sibling;   
  Trie *child;     
};

Trie * CreateNode()
{
  Trie *node = new Trie;
  node->symbol='\0';
  node->value = 0; 
  node->sibling = NULL;
  node->child = NULL;
  return node;        
}


Trie * Insert ( Trie *root, char *key, int val)
{
  Trie *cur, *parent, *list;
  parent = NULL;
  list = root;
  for(int i=0; key[i] != '\0'; i++) 
  {
    for(cur = list; cur != NULL; cur = cur->sibling)     
    {
      if(cur->symbol == key[i])
        break;
    }
    if(cur == NULL)                        
    {
      cur = CreateNode();
      cur->symbol = key[i];
      cur->sibling = list;
      if(parent != NULL)
        parent->child = cur;
      else
        root = cur;
      list = NULL;
    } 
    else                               // this key have search, down up on next level  
    {
      list = cur->child;
    }
    parent = cur;
  }        
  cur->value = val;
  return root;
} 


Trie * Fill ()                          
{
 int n;
 cout<<"input the number word :\n";
 cin>>n;
 Trie *rt=NULL;
 cout<<"Input the word in English :\n";
 for (int i=0;i<n;i++)
 {
  char *word =new char[25];
  cin>>word;
  rt = Insert(rt, word, 1);
 }
 return rt;
  
}

bool consonant(char ch)
{
	if (    ch=='q' || ch=='w' || ch=='r' || ch=='t'
         || ch=='p' || ch=='s' || ch=='d' || ch=='f'
         || ch=='g' || ch=='h' || ch=='j' || ch=='k'
         || ch=='l' || ch=='z' || ch=='x' || ch=='c'
         || ch=='v' || ch=='b' || ch=='n' || ch=='m')
    	return 1;
    return 0;
}

void Soglas(Trie*root,int &kol)                         
{  
  Trie *node;
  int i;
  for (node = root; node != NULL; node = node->sibling) 
  {
    if(node->value == 0)
      Soglas(node->child, kol);
    else
     if (consonant(node->symbol))
     {
    kol++;
    if(node->child != NULL)
        Soglas(node->child, kol);
     }      
       
  } 
}



void trie_print(Trie *root, int level)
{
	Trie *node;
	int i;
	for (node = root; node!=NULL;node = node->sibling)
	{
		for (i=0;i<level;i++)
			cout<<(" ");
	
		if (node->value == 1)
			cout<<'\n'<<node->symbol<<node->value;
		else
			cout<<'\n'<<node->symbol;
	
		if (node->child != NULL)
			trie_print(node->child, level+1);
	}		
}


int main()
{ 
  Trie*root;
  root=Fill();
  cout<<endl;
  int m=0;
  Soglas(root,m);
  trie_print(root, 0);
  cout<<"\nNumbers words have ended on consonant word = "<<m<<endl;
  return 0;
}
