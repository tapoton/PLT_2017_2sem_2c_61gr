#include <iostream>
#include <cstdlib>

using namespace std;

struct trie
{
	char *value;
	char key;
        trie *sibling;
	trie *child;
};

trie *trie_create()
{
	trie *node = new trie;

	node->key = NULL;
	node->value = NULL;
	node->sibling = NULL;
	node->child = NULL;

	return node;
}

trie *trie_insert(trie *root, char *key, char *value)
{
	trie *node, *parent, *list;
	parent = NULL;
	node = root;
	list = root;

	for (key; *key != '\0'; key++)
	{
		for (node; node != NULL; node = node->sibling)
		{
			if (node->key == *key)
				break;
		}
	
	
	        if (node == NULL)
        	{
	        	node = trie_create();
		        node->key = *key;
		        node->sibling = list;

		        if (parent != NULL)
			        parent->child = node;
		        else
			        root = node;

		        list = NULL;
	        }

	        else
		        list = node->child;

                parent = node;
	
        }
	node->value = _strdup(value);

	return root;
}

trie *trie_delete1(trie *root, trie *parent, char *key, bool *found)
{
	trie *node, *prev = NULL;
	*found = (*key == '\0' && root == NULL) ? true : false;

	if (root == NULL || *key == '\0')
		return root;

	for (node = root, node != NULL; node = node->sibling)
	{
		if (node->key == *key)
			break;
		prev = node;
	}

	if (node == NULL)
		return root;

	trie_delete1(node->child, node, key + 1, found);

	if (*found && node->child == NULL)
	{
		if (prev != NULL)
			prev->sibling = node->sibling;
		else
		{
			if (parent != NULL)
				parent->child = node->sibling;
			else
				root = node->sibling;
		}

		delete node->value;
		node = NULL;
	}

	return root;
}

trie *trie_delete(trie *root, char *key)
{
	bool found;
	return trie_delete1(root, NULL, key, &found);
}

void trie_print(trie *root, int level)
{
	trie *node;
	int i;

	for (node = root; node != NULL; node = node->sibling)
	{
		for (i = 0; i < level; i++)
			cout << ' ';

		if (node->value == NULL)
			cout << '\n' << node->key << ' ' << node->value;
				
		else
			cout << '\n' << node->key;

		if (node->child != NULL)
			trie_print(node->child, level+1);
	}
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	trie *root = NULL;

	cout << "Исходное дерево: \n";

	root = trie_insert(root, "bars", "60");
	root = trie_insert(root, "baribal", "100");
	root = trie_insert(root, "whale", "3000");
	root = trie_insert(root, "lion", "500");
	trie_print(root, 0);

	cout << endl << endl;
	cout << "Дерево, с удаленным ключом "bars": \n";
	cout << endl << endl;

	system("PAUSE");
	return 0;
}

