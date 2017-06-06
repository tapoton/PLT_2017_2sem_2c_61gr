#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <cstring>
#include <string.h>

using namespace std;

#define HASHTABLE_SIZE 5

struct Node
{
	string name;
	unsigned int counter = 0;
	Node *next;
}**hashtable;

void HashTable_Create()
{
	hashtable = new Node *[HASHTABLE_SIZE];
	for (int i = 0; i < HASHTABLE_SIZE; i++)
		hashtable[i] = NULL;
}

unsigned int HashTable_Index(string name)
{
	int sum = 0;
	for (unsigned int i = 0; i <name.length(); i++)
		sum += name[i] - '0';
	return (sum % HASHTABLE_SIZE);
}

void HashTable_Fill(string text, Node ** hashtable)
{
	bool check=0;
	string word;
	ifstream fin(text);
	while (!fin.eof())
	{
		fin >> word;
		Node *cur = new Node;
		int index = HashTable_Index(word);
		Node *current = new Node;
		current = hashtable[index];
		while(current&&!check)
		{
			if (current->name == word)
			{
				current->counter++;
				check = 1;
			}
			current = current->next;
		}
		if (!check)
		{
			cur->name = word;
			cur->counter = 1;
			cur->next = hashtable[index];
			hashtable[index] = cur;
		}
	}
}

void HashTable_WordCounter(string text, string list, Node **hashtable)
{
	ifstream fin(list);
	string listname;
	bool check=0;
	unsigned int index;
	while (!fin.eof())
	{
		check = 0;
		fin >> listname;
		index = HashTable_Index(listname);
		Node *current = new Node;
		current = hashtable[index];
		while (current&&!check)
		{
			if (current->name == listname)
			{
				cout << listname << " = " << current->counter<<endl;
				check = 1;
			}
			current = current->next;
		}
	}
}

int main()
{
	string text;
	string list;
	cout << "Enter the text: " << endl;
	cin>>text;
	cout << "Enter the list: " << endl;
	cin >> list;
	
	HashTable_Create();
	HashTable_Fill(text, hashtable);
	cout << "The result is: " << endl;
	HashTable_WordCounter(text, list, hashtable);

	system("PAUSE");
	return EXIT_SUCCESS;
}