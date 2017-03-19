// Kuchinskiy Pavel Igorevich, 2 coure, 61 group
// Labaratory work №1, Delete all palindroms from trie tree
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

struct trie
{
    bool value;        // 1 - if it is the last char of the word
    char symbol;
    trie *sibling;
    trie *parent;
    trie *child;
};

trie * CreateNode()
{
    trie *node = new trie;
    node->symbol='\0';
    node->value = 0;
    node->sibling = NULL;
    node->child = NULL;
    node->parent = NULL;
    return node;
}


trie *trie_insert(struct trie *root, char *key)
{
	trie *node, *parent, *list;
	parent = NULL, list = root;
	for(int i=0; key[i] != '\0'; key++) //Lookup sibling node
	{
		for(node = list; node != NULL; node = node->sibling)
		    if(node->symbol == key[i])
			{
				break;
			}
		if(node == NULL) //Node not found. Add new node
		{
			node = CreateNode();
			node->symbol = key[i];
			node->sibling = list;
			if(parent != NULL) parent->child = node;
			else root = node;
			node->parent=parent;
			list = NULL;
		}
		else list = node->child; //Node found. Move to next level
		parent = node;
	}
	node->value=1;
	return root;
}


trie *trie_fill ()
{
    int n;
    cout<<"Enter count of words:\n";
    cin>>n;
    trie *rt=NULL;
    cout<<"Enter words:\n";
    for (int i=0;i<n;i++)
    {
        char *word =new char[25];
        cin>>word;
        rt = trie_insert(rt, word);
    }
    return rt;

}

bool CheckPalindrom (string s)
{
    string s1;
    for (int i=s.length()-1; i>=0; i--)
        s1=s1+s[i];
    if(s1==s)
        return true;
    else return false;
}

void DelPalindrom1(trie *q,string s)
{
    trie *w=q; int i=0; w->value=0;
    for(i=0;i<s.length();i++)
    {
        if(w->child==NULL)
        {
            w=w->parent;
            w=w->child;
            if(w->symbol==s[i])
            {
                w->parent->child=w->sibling;
            }else
            {
                while(w->sibling->symbol!=s[i])
                {
                    w=w->sibling;
                }
                trie *t=w->sibling;
                w->sibling=w->sibling->sibling;
                delete t;
            }
        }  else break;
        if(w->parent!=NULL)
            w=w->parent;
        if(w->value==1) break;
    }
}
void DelPalindrom ( trie *root, string s)
{
    if(root->sibling!=NULL)
        DelPalindrom(root->sibling,s);
    s=s+root->symbol;
    if(root->child!=NULL)
        DelPalindrom(root->child,s);
    if(CheckPalindrom(s))
    {
        if(root->value==1)
            DelPalindrom1(root,s);
    }

}


void Print(trie*root, int level)
{
    trie*node=new trie;
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
      trie*root;
      root=trie_fill();
      cout<<"Input:"<<endl;
      Print(root, 0);
      root->parent =new trie;
      root->parent->child=root;
      root->parent->value=1;
      trie *q=root->parent;
      string s;
      DelPalindrom(root,s);
      cout<<"\nOutput:"<<endl;
      if(q->child)
        Print(root, 0); else cout<<"Empty tree";
            return EXIT_SUCCESS;
}
