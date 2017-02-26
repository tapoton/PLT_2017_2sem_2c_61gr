/*
    Zharkovskiy Nikita 2nd year 61 group
    Lab 1 task 8: From trie-tree to remove all the words containing a given substring.
    
    p.s. Implemented basic functions of trie-tree and 3 functions to solve my problem:
    1) Pass around the tree. Each tree node calls the function 2.
    2) check whether the root of a subtree with the specified word. If Yes, proceed to step 3
    3) Delete subtree
*/

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
using namespace std;

struct trie {
	char *value;
	char ch;
	struct trie *sibling; //sibling node
	struct trie *child; //first child node
};

struct trie *trie_create(); //create empty node in Tree
char *trie_lookup(struct trie *root, char *key); //lookup word  in tree
struct trie *trie_insert(struct trie *root, char *key, char *value); //insert word
struct trie *trie_delete(struct trie *root, char *key); //delete word using trie_delete_dfs
struct trie *trie_delete_dfs(struct trie *root, struct trie *parent, char *key, int *found);
void trie_print(struct trie *root, int level); //print Trie-tree

//My task
void del_substring(struct trie *root, char *word); //run across all structure
void chek_node(struct trie *root, char *key); //check the current node, if it starts from substring go to free_trie
void free_trie(struct trie *root); //delete all the tree from given root

int main()
{
    struct trie *root = NULL;
	
	cout<<"Commands:"<<endl
	<<"0 - Stop the program"<<endl
	<<"1 - Insert word"<<endl
	<<"2 - Lookup word"<<endl
	<<"3 - Delete word"<<endl
	<<"4 - Delete all words containing a given substring //my task"<<endl
	<<"5 - Print tree"<<endl;
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
				cout<<"Enter a word and key: ";
				cin>>word>>key;
				root = trie_insert(root, (char*)word, (char*)key);
				break;
			}
			case 2:{
				char word[80], *ans=new char[80];
				cout<<"Enter a word: ";
				cin>>word;
				cout << "Lookup '"<<word<<"' : ";
				ans=trie_lookup(root,word);
				if(!ans) cout<<"not found"<<endl;
				else cout<<ans<<endl;
				break;
			}
			case 3:{
				char word[80];
				cout<<"Enter a word: ";
				cin>>word;
				root=trie_delete(root, (char*)word);
				break;
			}
			case 4:{
				char word[80];
				cout<<"Enter a substring: ";
				cin>>word;
				del_substring(root, (char*)word);
				break;
			}
			case 5:{
				cout<<endl<<"Commands:"<<endl
	            <<"0 - Stop the program"<<endl
	            <<"1 - Insert word"<<endl
	            <<"2 - Lookup word"<<endl
	            <<"3 - Delete word"<<endl
	            <<"4 - Delete all words containing a given substring //my task"<<endl
	            <<"5 - Print tree"<<endl;
				trie_print(root,0);
				break;
			}
		}
	}
	return 0;
}

struct trie *trie_create() 
{
	struct trie *node;
	if((node=(trie *)malloc(sizeof(*node)))==NULL) return NULL;
	node->ch = '\0';
	node->value = NULL;
	node->sibling = NULL;
	node->child = NULL;
	return node;
}

char *trie_lookup(struct trie *root, char *key) 
{
	struct trie *node, *list;
	for(list = root; *key != '\0'; key++) 
	{
		for(node = list; node != NULL; node = node->sibling)
			if(node->ch == *key) break;
		if(node != NULL) list = node->child;
		else return NULL;
	}
	return node->value; //Check: Node must be a leaf node!
}

struct trie *trie_insert(struct trie *root, char *key, char *value)
{
	trie *node, *parent, *list;
	parent = NULL, list = root;
	for(; *key != '\0'; key++) //Lookup sibling node
	{
		for(node = list; node != NULL; node = node->sibling)
		    if(node->ch == *key) break;
		if(node == NULL) //Node not found. Add new node
		{
			node = trie_create();
			node->ch = *key;
			node->sibling = list;
			if(parent != NULL) parent->child = node;
			else root = node;
			list = NULL;
		}
		else list = node->child; //Node found. Move to next level
		parent = node;
	}
	if(node->value !=NULL) free(node->value);
	node->value = strdup(value);
	return root;
}

struct trie *trie_delete(struct trie *root, char *key)
{
	int found;
	return trie_delete_dfs(root, NULL, key, &found);
}

struct trie *trie_delete_dfs(struct trie *root, struct trie *parent, char *key, int *found)
{
	struct trie *node, *prev = NULL;
	*found = (*key == '\0' && root == NULL) ? 1:0;
	if(root == NULL || *key == '\0') return root;
	for(node = root; node != NULL; node = node->sibling)
	{
		if(node->ch == *key) break;
		prev = node;
	}
	if(node == NULL) return root;
	trie_delete_dfs(node->child, node, key+1, found);
	if(*found > 0 && node->child == NULL) //Delete node
	{
		if(prev != NULL) prev->sibling = node->sibling;
		else
		{
			if(parent != NULL) parent->child = node->sibling;
			else root = node->sibling;
		}
		free(node->value);
		free(node);
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
		if(node->value != NULL) printf("%c (%s)\n", node->ch, node->value);
		else printf("%c \n", node->ch);
		if(node->child != NULL) trie_print(node->child, level+1);
	}
}

void del_substring(struct trie *root, char *word) 
{
	struct trie *node=root;
	while(node)
	{
		if(node->child)
		{
			del_substring(node->child,word);
		}
		chek_node(root,word);
		node=node->sibling;
	}
}

void chek_node(struct trie *root, char *key) 
{
	struct trie *node, *list = root;
	for(; *key != '\0'; key++) 
	{
		for(node = list; node != NULL; node = node->sibling)
		    if(node->ch == *key) break;
		if(node == NULL) return;
		else list = node->child;
	}
	free_trie(node);
}

void free_trie(struct trie *root)
{
	struct trie *node=root,*temp;
	while(node)
	{
		if(node->child)
		{
			free_trie(node->child);
		}
		temp=node;
		node=node->sibling;
		temp->ch = '\0';
	    temp->value = NULL;
	    temp->sibling = NULL;
	    temp->child = NULL;
	}
}
