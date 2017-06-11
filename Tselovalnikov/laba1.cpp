#include <iostream>
#include <cstring>
using namespace std;

struct trie
{
	char *value;
	char ch;
	trie *sibling;
	trie *child;
};

trie *trie_createNode()
{
	trie *node = new trie;
	node->ch = NULL;
	node->value = NULL;
	node->sibling = NULL;
	node->child = NULL;
	return node;
}

trie *trie_insert(trie *root, char *key, char *value)
{
	trie *node;
	trie *parent,*list;
	parent = NULL;
	list = root;
	for (;*key!='\0';key++)
	{
		for (node = list; node!=NULL; node = node->sibling) 
			if (node->ch == *key)
				break;		
		if (node == NULL)
		{
			node = trie_createNode();
			node->ch = *key;           
			node->sibling = list;
			if (parent != NULL)
				parent->child = node;
			else
				root = node;
			list = NULL;
		}
		else
		{
			list = node->child;
		}		
		parent = node;
	}		
	node->value = strdup(value);
	return root;
}

void trie_print(trie *root, int level)
{
	trie *node;
	int i;
	for (node = root; node!=NULL;node = node->sibling)
	{
		for (i=0;i<level;i++)
			printf(" ");
	
		if (node->value != NULL)
			printf("%c (%s)\n",node->ch,node->value);
		else
			printf("%c \n",node->ch);
	
		if (node->child != NULL)
			trie_print(node->child, level+1);
	}		
}

char *trie_lookup(struct trie *root, char *key)
{
	struct trie *node, *list;
	for (list = root; *key != '\0'; key++) {
		for (node = list; node != NULL; node = node->sibling)
		{
			if (node->ch == *key)
				break;
		}
		if (node != NULL)
			list = node->child;
		else
			return NULL;
	}
	return node->value;
}

int main()
{
	trie *root;
	char value[100], key[100];
	int command,count = 0;
	
	cout<<"0) Exit"<<endl;
	cout<<"1) Insert key and value"<<endl;
	cout<<"2) Show trie-tree"<<endl;
	cout<<"3) Lookup key"<<endl;
	cout<<"Enter command: ";
	cin>>command;	
	
	while (true)
	{
		switch (command)
		{
			case 0 : 
			{
				return 0;
			}
			case 1 :
			{
				cout<<"Enter key and value: ";
				cin>>key>>value;
				if (count == 0)
				{
					root = trie_insert(NULL,key,value);
					count = 1;
				}						
				else
					root = trie_insert(root,key,value);
				break;	
			}
			case 2 :
			{
				cout<<"Tree is : "<<endl;
				trie_print(root,0);
				break;
			}
			case 3:
			{
				cout<<"Enter key: ";
				cin>>key;
				cout<<"Trie lookup '"<<key<<"' "<<trie_lookup(root, key)<<endl;
				break;
			}
		}
		cout<<"Enter command: ";
		cin>>command;
	}	
	
	return 0;
}
