// Егоров Дмитрий 2 курс 61 группа 
// Лабораторная №1 Задача 13: В trie-дереве найти слово с наименьшей длиной.
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

int min = INT_MAX;

struct Trie
{
	int value;        
	char symbol;
	Trie *sibling;
	Trie *child;
};

Trie * CreateNode()
{
	Trie *node = new Trie;
	node->symbol = '\0';
	node->value = 0;
	node->sibling = NULL;
	node->child = NULL;
	return node;
}

Trie * Insert(Trie*root, char*key, int val)
{
	Trie *cur=new Trie, *parent, *list;
	parent = NULL;
	list = root;
	for (int i = 0; key[i] != '\0'; i++)
	{
		for (cur = list; cur != NULL; cur = cur->sibling)     
		{
			if (cur->symbol == key[i])
				break;
		}
		if (cur == NULL)                        
		{
			cur = CreateNode();
			cur->symbol = key[i];
			cur->sibling = list;
			if (parent != NULL)
				parent->child = cur;
			else
				root = cur;
			list = NULL;
		}
		else                               
		{
			list = cur->child;
		}
		parent = cur;
	}
	cur->value = val;
	return root;
}

Trie * Fill()                          
{
	int n;
	cout << "Enter the number of words.\n";
	cin >> n;
	Trie *rt = NULL;
	cout << "Enter words in English:\n";
	for (int i = 0; i<n; i++)
	{
		char *word = new char[25];
		cin >> word;
		rt = Insert(rt, word, 1);
	}
	return rt;

}

void FindMinimum(Trie*root,  int length)                          
{
	Trie *node;
	int i;
	for (node = root; node != NULL; node = node->sibling)
	{
		if (node->value != 1)
			FindMinimum(node->child,  ++length);
		else
			if (min > length) min = length;
			{
				if (node->child != NULL)
					FindMinimum(node->child, length);
			}
	}
}

void Print(Trie*root, int level)
{
	Trie*node = new Trie;
	int i;
	for (node = root; node != NULL; node = node->sibling)
	{
		for (i = 0; i < level; i++)
			printf("  ");
		if (node->value == 0)
			printf("%c \n", node->symbol);
		else
			printf("%c (%d)\n", node->symbol, node->value);
		if (node->child != NULL)
			Print(node->child, level + 1);
	}
}

int main()
{
	Trie*root;
	root = Fill();
	cout << endl;
	Print(root, 0);
	int m = 0;
	FindMinimum(root, 0);
	cout << "The minimum number of letters in the word: " << min << endl;
	system("PAUSE");
	return 0;
}