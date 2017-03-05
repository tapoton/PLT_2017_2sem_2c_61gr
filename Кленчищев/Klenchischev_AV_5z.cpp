// Кленчищев А.В. 2к. 61 гр. 
// 5. Вставка в trie-дерево перевернутого слова и поиск по заданному окончанию

#include "stdafx.h"
#include <iostream>
#include <cstring>

using namespace std;

struct trie
{
	char key;
	char *value;
	trie *sibling;
	trie *child;
};

trie *createNode();
trie *insertNode(trie *root, char *key, char *value);
void printTrie(trie *root, int lvl);
void findWords(trie *root, char *key);
void printValues(trie *list);

int main()
{
	setlocale(LC_ALL, "Russian");
	trie *root = NULL;

	int choice = 1;
	while (choice) {
		cout << endl << "Выберите операцию: " << endl;
		cout << "0. Выход" << endl;
		cout << "1. Вставить слово" << endl;
		cout << "2. Вывести дерево" << endl;
		cout << "3. Найти ключи в дереве по окончанию" << endl;

		cin >> choice;

		switch (choice) {
		case 1: {
			cout << "Введите слово: ";
			char word[64];
			cin >> word;
			char value[64];
			char key[64];
			strcpy_s(value, word);
			strcpy_s(key, word);
			root = insertNode(root, key, value);
			break;
		}
		case 2: {
			cout << "Дерево: " << endl;
			printTrie(root, 0);
			break;
		}
		case 3: {
			cout << "Введите окончание:";
			char word[64];
			cin >> word;
			char key[64];
			strcpy_s(key, word);
			findWords(root, key);
			break;
		}
		default: {
			choice = 0;
			break;
		}
		}
	}
	return 0;
}

trie *createNode() {
	trie *node = new trie;
	node->key = NULL;
	node->value = NULL;
	node->sibling = NULL;
	node->child = NULL;

	return node;
}

trie *insertNode(trie *root, char *key, char *value) {
	for (int i = 0, l = strlen(key); i < l / 2; i++) {
		char c = key[i];
		key[i] = key[l - i - 1];
		key[l - i - 1] = c;
	}
	trie *node = NULL, *parent, *list;
	parent = NULL;
	list = root;

	for (; *key != '\0'; key++) {
		for (node = list; node != NULL; node = node->sibling) {
			if (node->key == *key)
				break;
		}
			
		if (node == NULL) {
			node = createNode();
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

void printTrie(trie *root, int lvl) {
	trie *node;
	for (node = root; node != NULL; node = node->sibling) {
		for (int i = 0; i < lvl; i++)
			cout << " ";

		cout << node->key;
		if (node->value != NULL)
			cout << "-" << node->value;
		cout << endl;

		if (node->child != NULL)
			printTrie(node->child, lvl + 1);
	}

	cout << endl;
}

void findWords(trie *root, char *key) {
	trie *node = NULL, *list = root, *parent = NULL;

	for (int i = 0, l = strlen(key); i < l / 2; i++) {
		char c = key[i];
		key[i] = key[l - i - 1];
		key[l - i - 1] = c;
	}

	while (*key != '\0') {
		for (node = list; node != NULL; node = node->sibling)
			if (node->key == *key)
				break;

		if (node == NULL) {
			cout << "Нет слов с таким окончанием" << endl;
			return;
		}
		parent = list;
		list = node->child;
		key++;
	}

	if (parent->value != NULL)
		cout << parent->value << endl;

	printValues(list);
}

void printValues(trie *list) {
	trie *node;
	for (node = list; node != NULL; node = node->sibling) {
		if (node->value != NULL)
			cout << node->value << endl;
		if (node->child != NULL)
			printValues(node->child);
	}
}