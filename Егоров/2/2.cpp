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

void HashTable_Fill(string list, Node ** hashtable)
{
	string sname;
	ifstream fin(list);
	while (!fin.eof())
	{
		fin >> sname;
		Node *cur = new Node;
		int index = HashTable_Index(sname);
		cur->name = sname;
		cur->counter = 0;
		cur->next = hashtable[index];
		hashtable[index] = cur;
	}

}

void HashTable_WordCounter(char* text, Node **hashtable)
{
	for (int i = 0; i < HASHTABLE_SIZE; i++)
		if (hashtable[i]) 
		{
			int count=0, TextIndex = 0, WordIndex=0;
			while (text[TextIndex]!='.')
			{
				while (hashtable[i]->name[WordIndex] == text[TextIndex]/**/ && hashtable[i]->name[WordIndex] /**/ && text[TextIndex]!='.')
				{
					count++;
					WordIndex++;
					TextIndex++;
				}

				if (count == hashtable[i]->name.length())
					hashtable[i]->counter++;
				count = 0;
				WordIndex = 0;
				TextIndex++;
			}
		}
}

void HashTable_Print(Node **hashtable)
{
	cout << "The resulting hash function:" << endl;
	int sum = 0;
	for (int i = 0; i < HASHTABLE_SIZE; i++)
		if (hashtable[i] != NULL)
		{
			Node *q;

			while (hashtable[i] != NULL)
			{
				q = hashtable[i];
				cout << q->name << " = " << q->counter << endl;
				hashtable[i] = hashtable[i]->next;
			}
		}
}



int main()
{
	string list="list.txt";
	cout << "Enter the text: " << endl;
	char  text[1000];
	gets_s(text);

	HashTable_Create();
	HashTable_Fill(list, hashtable);
	HashTable_WordCounter(text, hashtable);
	HashTable_Print(hashtable);

	system("PAUSE");
	return EXIT_SUCCESS;
}