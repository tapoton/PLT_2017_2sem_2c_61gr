#include <iostream>
#include <string>
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
	trie *node;

	node->ch = '\0';
	node->value = NULL;
	node->sibling = NULL;
	node->child = NULL;

	return node;
}

trie *trie_insert(trie *root, char *x, char *value)
{
	trie *node, *parent, *list;
	parent = NULL; 
	list = root;

	for ( ; *x != '\0'; x++)
	{
		for (node = list; node != NULL; node = node->sibling)
		{
			if (node->key == *x)
				break;
		}
	}
	
	if (node == NULL)
	{
		node = trie_create();
		node->key = *x;
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
	        parent = node;
	}

	if (node->value != NULL)
		free (node->value);

	node->value = strdup(value);

	return root;
}

trie *trie_delete1(trie *root, trie *parent, char *x, int *found)
{
	trie *node, *prev = NULL;
	*found = (*x == '\0' && root == NULL)?1:0;

	if (root == NULL || *x == '\0')
		return root;

	for (node = root, node != NULL; node = node->sibling)
	{
		if (node->key == *x)
			break;
		prev = node;
	}

	if (node == NULL)
		return root;

	if (*found > 0 && node->child == NULL)
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

		free (node->value);
		free (node);
	}

	return root;
}

trie *trie_delete(trie *root, char *x)
{
	int found;
	return trie_delete1(root, NULL, x, &found);
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
	trie *root;
	root = trie_insert(NULL, "bars", "60");
	root = trie_insert(root, "baribal", "100");
	root = trie_insert(root, "kit", "3000");
	trie_print(root, 0);
	return 0;
}

