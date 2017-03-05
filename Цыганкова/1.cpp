// Цыганковой Елизаветы 2 курс 61 группа 
// Лабораторная №1 Задача 12 : подсчитать в trie-дереве кол-во слов, оканчивающихся на согласную букву.
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

struct Trie
{
  int value;        // 0 если текущий символ и 1 если последний символ слова 
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


Trie * Insert ( Trie*root, char*key, int val)
{
  Trie *cur, *parent, *list;
  parent = NULL;
  list = root;
  for(int i=0; key[i] != '\0'; i++) 
  {
    for(cur = list; cur != NULL; cur = cur->sibling)     // просматриваем всех братьев
    {
      if(cur->symbol == key[i])
        break;
    }
    if(cur == NULL)                        // такой ключ не найден, добавляем в качестве нового узла
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
    else                               // такой ключ найден, спускаемся на следующий уровень  
    {
      list = cur->child;
    }
    parent = cur;
  }        
  cur->value = val;
  return root;
} 


Trie * Fill ()                          // Заполнение дерева 
{
 int n;
 cout<<"Введите количество слов:\n";
 cin>>n;
 Trie *rt=NULL;
 cout<<"Вводите слова на английском:\n";
 for (int i=0;i<n;i++)
 {
  char *word =new char[25];
  cin>>word;
  rt = Insert(rt, word, 1);
 }
 return rt;
  
}


void Soglas(Trie*root,int &kol)                          //Поиск слов оканчивающихся на согласную букву
{  
  Trie *node;
  int i;
  for (node = root; node != NULL; node = node->sibling) 
  {
    if(node->value != 1)
      Soglas(node->child, kol);
    else
     if (node->symbol=='q' || node->symbol=='w' || node->symbol=='r' || node->symbol=='t'
         || node->symbol=='p' || node->symbol=='s' || node->symbol=='d' || node->symbol=='f'
         || node->symbol=='g' || node->symbol=='h' || node->symbol=='j'|| node->symbol=='k'
         || node->symbol=='l' || node->symbol=='z' || node->symbol=='x' || node->symbol=='c'
         || node->symbol=='v' || node->symbol=='b' || node->symbol=='n' || node->symbol=='m')
     {
       kol++;
       if(node->child != NULL)
         Soglas(node->child, kol);
     }      
       
  } 
}



void Print(Trie*root, int level)
{
  Trie*node=new Trie;
  int i;
  for (node = root; node != NULL; node = node->sibling) 
  {
    for(i = 0; i < level; i++)
      printf("  ");
    if(node->value == 0)
      printf("%c \n", node->symbol);
    else 
      printf("%c (%d)\n", node->symbol, node->value);    
    if(node->child != NULL)
      Print(node->child, level + 1);
  }
}

int main()
{
  setlocale(LC_ALL,"Russian"); 
  
  Trie*root;
  root=Fill();
  cout<<endl;
  Print(root, 0);
  int m=0;
  Soglas(root,m);
  cout<<"Количество слов, оканчивающихся на согласную = "<<m<<endl;

    
    system("PAUSE");
    return EXIT_SUCCESS;
}
