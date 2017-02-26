#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
 
struct Trie  //структура
{
 bool*value;
 char ch;
 Trie *sibling;
 Trie *child;
};

Trie* trie_create()  //создание пустой узла
{
 Trie *node=new Trie;	
 node->ch='\0';
 node->value=NULL;
 node->sibling=NULL;
 node->child=NULL;
 return node;
}

Trie *trie_insert(Trie *root,char *key, bool* value) //вставка в дерево
{
 Trie *node, *parent, *list;
 parent = NULL;
 list = root;
 for (; *key != '\0'; key++) 
 {
  for (node = list; node!= NULL;node = node->sibling)
    if (node->ch == *key) break;
  if (node == NULL) 
  {
   node = trie_create();
   node->ch = *key;
   node->sibling = list;
   if (parent != NULL) parent->child = node;
   else 
     root = node;
   list = NULL;
  } 
  else 
    list = node->child;
  parent = node;
 }
 node->value=value;
 return root;
} 

void trie_print(Trie *root, int level) //вывод на экран
{
 Trie *node;
 int i;
 for (node = root; node != NULL;node = node->sibling)
 {
  for (i = 0; i < level; i++)
   printf(" ");
   printf("%c \n", node->ch);
  if (node->child != NULL)
   trie_print(node->child, level + 1);
 }
}



Trie* delete2(Trie *root,Trie *parent,int *found) //основное удаление 
{ 
 Trie *node;
 for(Trie *cur=root,*prev=NULL;cur!=NULL;cur=cur->sibling) 
 {
  node=cur;
  if(node->child!=NULL) 
   node=delete2(node->child,node,found); //рекурсия
  if(node->value!=NULL) 
    *found=*node->value==true; 
  if(*found && node->child==NULL)  //полное удаление звена(как в обычном удалении)
  {
   if(prev!=NULL) 
    prev->sibling=node->sibling;
   else 
   {
    if (parent!= NULL)
     parent->child=node->sibling;
    else
     root=node->sibling;
   }
   delete(node);
  }
  else if(*found && node->child!=NULL && node->value!=NULL) //удаление только номера(если четное находится внутри нечетного)
  {
    node->value=NULL;	
    *found=0;
  }
  if(node->value==false) prev=node; 
 }
 if(parent!=NULL) return parent;
  else return root;		 
}
 	
 Trie *delete1(Trie *root) //вспомогательная функция удаления
{
 int found;
 return delete2(root,NULL,&found);
}

int main()
{ 
 setlocale(LC_ALL,"Russian"); 
 Trie *root=trie_create();
 cout<<"Создание дерева"<<endl;
 cout<<"Вводите слова(латинские) до cлова='.'"<<endl;
 char sl[20];
 cin>>sl;
 root=NULL;
 bool nechet=false,chet=true;
 while(sl[0]!='.')	
 {
  if(strlen(sl)%2==0) root=trie_insert(root,sl,&chet); //вставка значение "1" для слова четной длины 
   else root=trie_insert(root,sl, &nechet); //вставка значение "0" для слова нечетной длины 
  cin>>sl;
 }
 cout<<"\nНачальное дерево:"<<endl;
 trie_print(root, 0);
 cout<<"\nДерево без слов четной длины:"<<endl;
 root=delete1(root);
 if(root==NULL) cout<<"Дерево пусто"<<endl;
 else
  trie_print(root, 0);
 return 0;		
}
