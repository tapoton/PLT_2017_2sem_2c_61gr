#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>

#define HASHTAB_SIZE 10

using namespace std;

struct actor
{
	string name;
	string surname;
};

struct film
{
	string name;
	string producer;
	actor actors[5];
	string summary;
	film *next;
};

film *hashtab[HASHTAB_SIZE];

unsigned int hashtab_hash(string text)
{
	int sum = 0, hash;
	for (int i = 0; i < sizeof(text) / sizeof(string); i++)
		sum += (int)text[i] - (int)'0';
	hash = sum%HASHTAB_SIZE;
	return hash;
}

void hashtab_init(film **hashtab)
{
	for (int i = 0; i < HASHTAB_SIZE; i++)
		hashtab[i] = NULL;
}

void hashtab_add(film **hashtab, string name)
{
	film *node = new film;
	int index = hashtab_hash(name);
	// adding to the begin of list

	if (node != NULL)
	{
		(*node).name = name;
		cout << endl << "Введите имя режиссера " << endl;
		cin >> (*node).producer;
		cout << endl << "Введите 5 актеров " << endl;

		for (int i = 0; i < 5; i++)
		{
			cin >> ((*node).actors[i]).name >> ((*node).actors[i]).surname;
		}

		cout << endl << "Расскажите краткое содержание фильма";
		getline(cin, (*node).summary);

		cout << endl;

		node->next = hashtab[index];
		hashtab[index] = node;
	}
}

film *hashtab_lookup(film **hashtab, string text)
{
	int index = hashtab_hash(text);
	film *node;
	for (node = hashtab[index]; node != NULL; node = node->next)
	{
		if (node->name == text)
			return node;
	}
	return NULL;
}

void show(film **hashtab)
{
	cout << "Какой фильм найти?" << endl;
	string text;
	cin >> text;
	film *q = hashtab_lookup(hashtab, text);

	if (!q)
		cout << "Такого фильма нет в списке\n";

	if (q)
	{
		cout << "По запросу " << text << "найдено: " << endl;
		cout << "Режиссер : " << hashtab[hashtab_hash(text)]->producer << endl;
		cout << "В фильме снимались : | ";
		for (int i = 0; i < 5; i++)
			cout << hashtab[hashtab_hash(text)]->actors[i].surname << " " << hashtab[hashtab_hash(text)]->actors[i].surname << " | ";
		cout << endl << "Краткое содержание фильма : " << hashtab[hashtab_hash(text)]->summary << endl;
	}

}

int main()
{
	hashtab_init(hashtab);
	setlocale(LC_ALL, "RUSSIAN");

	cout << "Какую операцию выполнить?" << endl << "1.Добавить элемент в таблицу." << endl << "2.Найти информацию о фильме." << endl << "3. Закончить программу." << endl;
	int command;
	cin >> command;

loop1:
	if (command == 1)
	{
		cout << "Введите название фильма." << endl;
		string text;
		cin >> text;
		hashtab_add(hashtab, text);
		cin >> command;
		goto loop1;
	}

	if (command == 2)
	{
		show(hashtab);
		cin >> command;
		goto loop1;
	}

	system("PAUSE");
	return 0;
}