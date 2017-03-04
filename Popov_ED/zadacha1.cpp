#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>                   
#include <malloc.h>

using namespace std;

struct trie 
 { 
   char *value; 
   char ch; 
   struct trie *sibling;   /* Sibling node */ 
   struct trie *child;     /* First child node */ 
 };
 
 struct trie *trie_create() 
 { 
	struct trie *node=new trie;
	//node = malloc(sizeof(*node));
	node->ch ='\0'; 

	node->value = NULL; 
	node->sibling = NULL; 
	node->child = NULL;
 return node;        
}

char *trie_lookup(struct trie *root, char *key) 
 { 
	struct trie *node, *list;
	for (list = root; *key != '\0'; key++) 
	{ 
	 	for (node = list; node != NULL; node = node->sibling) 
	 	{ 
	   		if (node->ch == *key) break; 
	 	} 
	 if (node != NULL) list = node->child; 
	 else return NULL; 
	} /* Check: Node must be a leaf node! */ 
 return node->value;
}

struct trie *trie_insert(struct trie *root, char *key, char *value) 
 { 
	struct trie *node, *parent, *list;
	parent = NULL; 
	list = root; 
	for (; *key != '\0'; key++) 
	{ // Lookup sibling node 
		for (node = list; node != NULL; node = node->sibling) 
	 	 	if (node->ch == *key) break;
     	if (node == NULL) 
	 	{  //Node not found. Add new node 
	  		node = trie_create(); 
	  		node->ch = *key; 
	  		node->sibling = list; 
	  		if (parent != NULL) parent->child = node; 
	  		else root = node; 
			  list = NULL; 
	 	} 
	 	else 
		{ // Node found. Move to next level 
	 		list = node->child; 
	 	} 
		parent = node;
	}
      // Update value in leaf 
	 if (node->value != NULL) free(node->value); 
	 node->value = strdup(value); 
	 return root; 
	}
	
struct trie *trie_delete_dfs(struct trie *root, struct trie *parent, char *key, int *found) 
 {
	struct trie *node, *prev = NULL;
	*found = (*key == '\0' && root == NULL) ? 1 : 0; 
	if (root == NULL || *key == '\0') return root;       
	for (node = root; node != NULL; node = node->sibling) 
	{ 
		if (node->ch == *key) break; prev = node; } 
		if (node == NULL) return root; 
		trie_delete_dfs(node->child, node, key + 1, found);
		if (*found > 0 && node->child == NULL) 
		{ 
			/* Delete node */        
			if (prev != NULL) prev->sibling = node->sibling; 
			else 
			{ 
				if (parent != NULL) parent->child = node->sibling;
				else root = node->sibling; 
			} 
	free(node->value); 
	free(node); 
		}	 
	return root;
 }	

struct trie *trie_delete(struct trie *root, char *key) 
{ 
	int found;
	return trie_delete_dfs(root, NULL, key, &found);
}

void trie_print(trie *root, int level)
{
	trie *node;
	int i;
	for (node = root; node!=NULL;node = node->sibling)
	{
		for (i=0;i<level;i++)
			cout<<(" ");
	
		if (node->value != NULL)
			cout<<'\n'<<node->ch<<node->value;
		else
			cout<<'\n'<<node->ch;
	
		if (node->child != NULL)
			trie_print(node->child, level+1);
	}		
}

void search_count(trie *root)
{
	char name;
	cout<<"\nInput srarching name: "; cin>>name;
	printf("Lookup: %s\n", trie_lookup(root, &name));
}

int menu()
{
	int m_change;
	do
	{
		system("cls");
    	cout<<"1-input the count\n";
    	cout<<"2-search the count\n";
    	cout<<"3-delete the count\n";
    	cout<<"4-to change the count\n";
    	cout<<"5-to print on the screen\n";
    	cout<<"0-exit\n";	
    	cin>>m_change;
	}while(m_change>5);
    return m_change;
}

void add_count(trie *root)
{
	bool p;
	char name, value;
	cout<<"Add the value 1-yes 0-no \n"; cin>>p;
	if (p) 
	{
		cout<<"Input the name: "; cin>>name;
		cout<<"\nInput the value: "; cin>>value;
		root = trie_insert(NULL, &name, &value);
	}
	while(p)
	{
		cout<<"Input the name: "; cin>>name;
		cout<<"\nInput the value: "; cin>>value;		
		root = trie_insert(root, &name, &value);		
	}	
}

void del_count(trie *root)
{
	char name;
	cout<<"\nInput deleted name: "; cin>>name;
	root = trie_delete(root, &name); 
}

trie *change1(struct trie *root, char *key) 
 { 
	struct trie *node, *list;
	for (list = root; *key != '\0'; key++) 
	{ 
	 	for (node = list; node != NULL; node = node->sibling) 
	 	{ 
	   		if (node->ch == *key) break; 
	 	} 
	 if (node != NULL) list = node->child; 
	 else return NULL; 
	} /* Check: Node must be a leaf node! */ 
 return node;
}


void change_count(trie *root)
{
	char cout1,cout2;
	cout<<"Input serching name"; 
	cin>>cout1;
	cout<<"Input the new value"; 
	cin>>cout2;
	change1(root, &cout1)->ch=cout2;
}


int main() 
	{ 
	struct trie *root=NULL;
	switch(menu())
	{
		case 1: add_count(root);
		case 2: search_count(root);
		case 3: del_count(root);
		case 4: 
		case 5:	trie_print(root, 0);
		default:;
	};
    
	
	

	return 0;
	}
