/*
    Zharkovskiy Nikita 2nd year 61 group
    Lab 1 task 8: From trie-tree to remove all the words containing a given substring.
*/

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
using namespace std;

struct trie {
	char ch;              //key
	int count;            //count the words
	struct trie *sibling; //sibling node
	struct trie *child;   //first child node
	struct trie *parent;  //parent
};

struct trie *mainroot = NULL;

struct trie *trie_create(); //create empty node in Tree
struct trie *trie_insert(struct trie *root, char *key); //insert word
void trie_print(struct trie *root, int level); //print Trie-tree

//My task
void del_substring(struct trie *root, char *word); 
void check_node(struct trie *root, char *key);
void rebuild_tree(trie*root);
bool del_null(trie*root);
void free_trie(struct trie *root);

int main()
{
	cout<<"Commands:"<<endl
	<<"0 - Stop the program"<<endl
	<<"1 - Insert word"<<endl
	<<"2 - Delete all words containing a given substring //my task"<<endl
	<<"3 - Print tree"<<endl;
	int command;
	while(1)
	{
		cout<<"Enter a command: ";
	    cin>>command;
		switch(command)
	    {
		    case 0: return 0;
		    case 1:{
				char word[80], key[80];
				cout<<"Enter a word: ";
				cin>>word;
				mainroot = trie_insert(mainroot, (char*)word);
				break;
			}
			case 2:{
				char word[80];
				cout<<"Enter a substring: ";
				cin>>word;
				del_substring(mainroot, (char*)word);
				rebuild_tree(mainroot);
				break;
			}
			case 3:{
				cout<<endl<<"Commands:"<<endl
	            <<"0 - Stop the program"<<endl
	            <<"1 - Insert word"<<endl
	            <<"2 - Delete all words containing a given substring //my task"<<endl
	            <<"3 - Print tree"<<endl;
				trie_print(mainroot,0);
				break;
			}
		}
	}
	return 0;
}

struct trie *trie_create() 
{
	struct trie *node=new trie;
	node->ch = '\0';
	node->sibling = NULL;
	node->child = NULL;
	node->parent = NULL;
	node->count=1;
	return node;
}

struct trie *trie_insert(struct trie *root, char *key)
{
	trie *node, *parent, *list;
	parent = NULL, list = root;
	for(; *key != '\0'; key++) //Lookup sibling node
	{
		for(node = list; node != NULL; node = node->sibling)
		    if(node->ch == *key)
			{
			    node->count++; 
				break;
			}
		if(node == NULL) //Node not found. Add new node
		{
			node = trie_create();
			node->ch = *key;
			node->sibling = list;
			if(parent != NULL) parent->child = node;
			else root = node;
			node->parent=parent;
			list = NULL;
		}
		else list = node->child; //Node found. Move to next level
		parent = node;
	}
	return root;
}

void trie_print(struct trie *root, int level)
{
	struct trie *node;
	int i;
	for(node = root; node != NULL; node = node->sibling)
	{
		for(i = 0; i < level; i++) printf("  ");
		 printf("%c\n", node->ch);
		if(node->child != NULL) trie_print(node->child, level+1);
	}
}

void del_substring(struct trie *root, char *word) 
{
	struct trie *node;
	for(node = root; node != NULL; node = node->sibling)
	{
		if(node->child != NULL) del_substring(node->child, word);
		check_node(node,word); 
	}
}

void check_node(struct trie *root, char *key) 
{
	struct trie *node, *list = root;
	for(; *key != '\0'; key++) 
	{
		for(node = list; node != NULL; node = node->sibling)
		    if(node->ch == *key) break;
		if(node == NULL) return;
		else list = node->child;
	}
	//checked, then count everything from current to top
	trie* back=node;
	int minus=back->count;
	while(back!=NULL)
	{
		back->count-=minus;
		back=back->parent;
	}
}

void rebuild_tree(trie*root)
{
	struct trie *node,*temp;
	for(node = root; node != NULL; )
	{
		if(node->child != NULL) rebuild_tree(node->child);
		temp=node->sibling;
		del_null(node);
		node=temp;
	}
}
bool del_null(trie*root)
{
	trie*node=root;
	//cout<<node->ch;
	if(node!=NULL && node->count<=0)
	{
		node->count=0;
		if(node->parent!=NULL && node->parent->child==node)
		{
			node->parent->child=node->sibling;
			node->sibling=NULL;
			free_trie(node);
			node=NULL;
		}
		else if(node->parent!=NULL && node->parent->child!=node)
		{
			trie*temp;
			for(temp=node->parent->child;temp->sibling!=node;temp=temp->sibling){}
			temp->sibling=node->sibling;
			node->sibling=NULL;
			free_trie(node);
			node=NULL;
		}
		else if(node->parent==NULL)
		{
			trie*temp;
			if(node==mainroot)
			{
				mainroot=node->sibling;
				node->sibling=NULL;
				free_trie(node);
				return 1;
			}
			else
			{
				for(temp=mainroot;temp->sibling!=NULL;temp=temp->sibling)
				{
					if(temp->sibling==node)
					{
						temp->sibling=node->sibling;
						node->sibling=NULL;
						free_trie(node);
						break;
					}
				}
			}
		}
	}
	return 0;	
}
void free_trie(struct trie *root)
{
	trie*node,*temp;
	for(node=root;node!=NULL;)
	{
		if(node->child) free_trie(node->child);
		temp=node;
		node=node->sibling;
		delete(temp);
	}
}
