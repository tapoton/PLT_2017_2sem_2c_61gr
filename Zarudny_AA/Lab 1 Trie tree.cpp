// ЛАБОРАТОРНАЯ №1: Вставка слова наоборот в Trie-дерево и поиск по заданному окончанию
//
#include "stdafx.h"
#include <iostream>
#include <string>
#define qlab5 25 // Маловажная константа для рисовки линий cline()
#define LETTERS 58 // Количество букв, в данном случае большие и маленькие латинского алфавита
#define firstletter 65 // Первый символ из используемых, большая латинская A

using namespace std;
void cline()
{
	cout << endl;
	for (int i = 0; i < qlab5; i++)
	{
		cout << "-";
	}
	cout << endl;
}
void output(string b)
{
	cout << endl << b << endl;
}
string reverse(string a)
{
	char b;
	unsigned int i, l = a.length();
	for (i = 0; i < l / 2; i++)
	{
		b = a[i];
		a[i] = a[l - i - 1];
		a[l - i - 1] = b;
	}
	return a;
}
bool arethelettersallowed(string a) //Проверка, состоит ли слово из букв диапазона
{
	for (int i = 0; i < a.length(); i++) 
	{
		if (a[i] < firstletter || a[i] >= firstletter + LETTERS)
			return 0;
	}
}

// СТРУКТУРА ЛИСТА
struct leaf
{
	leaf *children[LETTERS], *ancestor;
	char l;
	bool passing;
	
	
	leaf(leaf *ancestor1)
	{
		ancestor = ancestor1;
		passing = 1;
		for (int i = 0; i < LETTERS; i++)
			children[i] = NULL;
	}
};


// СТРУКТУРА И КЛАСС ДЛЯ СБОРА АДРЕСОВ НАЙДЕННЫХ ЛИСТЬЕВ
// И ИХ ПОТЕНЦИАЛЬНОЙ ОБРАБОТКИ
struct result_address
{
	leaf *list;
	result_address *next;
};
class found_by_ending
{
private:
	unsigned int n, i;
	result_address *root, *current, *last;
public:
	found_by_ending()
	{
		root = NULL;
		n = 0;
	}
	void letters_output()
	{
		cout << "\n";
		current = root;
		for (i = 0; i < n; i++)
		{
			this->output_by_step(current->list);
			cout << "\n";
			current = current->next;
		}
		cout << "Found: " << n << "\n";
	}
	void output_by_step(leaf *c)
	{
		if (c->ancestor != NULL)
		{
			output_by_step(c->ancestor);
			cout << c->l;
		}
	}
	unsigned int number()
	{
		return n;
	}
	void addleaf(leaf *l)
	{
		if (root != NULL)
		{
			current = new result_address;
			current->list = l;
			last->next = current;
			last = current;
		}
		else
		{
			root = new result_address;
			root->list = l;
			last = root;
		}
		n++;
	}
};


// КЛАСС TRIE ДЕРЕВА
class TRIE
{
private:
	leaf *root; int i; string s;
	// Рекурсия для добавления слова
	int addstep(string a, leaf *list, unsigned int k, int n)
	{
		int i, id = a[k] - firstletter;
		if (k < n)
		{
			if (list->children[id] == NULL)
			{
				list->children[id] = new leaf(list);
				list->children[id]->l = a[k];
			}
			return this->addstep(a, list->children[id], k + 1, n);
		}
		else
		{
			if (list->children[id] == NULL)
			{
				list->children[id] = new leaf(list);
				list->children[id]->l = a[k];
				list->children[id]->passing = 0;
				return 1; // Успех
			}
			else
			{
				return 2; // Слово уже есть
			}
		}
	}
public:
	TRIE()
	{
		root = new leaf(NULL);
	}

	// ДОБАВИТЬ СЛОВО
	int add(string a)
	{
		if (arethelettersallowed(a)) //Проверка, состоит ли слово из букв диапазона
			return this->addstep(a, root, 0, a.length() - 1);
		else
			return 0;
	}
	// ДОБАВИТЬ СЛОВО НАОБОРОТ
	int addbackwards(string a)
	{
		a=reverse(a);
		return this->add(a);
	}


	// НАЙТИ ПО ОКОНЧАНИЮ СЛОВА
	// ВЕРНУТЬ КЛАСС С АДРЕСАМИ ЛИСТЬЕВ
	found_by_ending * findbyending(string a)
	{
		if (arethelettersallowed(a)) //Проверка, состоит ли слово из букв диапазона
		{
			found_by_ending * R = new found_by_ending();
			findbyendingrecursion(root, R, a, 0, a.length()-1);
			return R;
		}
		else
			return NULL;
	}
	// Заполнить класс-результат
	void findbyendingrecursion(leaf * list, found_by_ending *R, string a, unsigned int step, unsigned int m) 
	{
		for (int j = 0; j < LETTERS; j++)
		{
			if (list->children[j] != NULL)
				findbyendingrecursion(list->children[j], R, a, step + 1, m);
		}
		if (step >= m && list->passing == 0 && endingisfound(list, a, m))
			R->addleaf(list);
	}
	// Проверка окончания слова
	bool endingisfound(leaf *l, string a, unsigned int m)  
	{
		leaf *current1 = l;
		int k = m;
		bool result = 1;
		while (k >= 0)
		{
			if (a[k] != current1->l)
			{
				return 0;
			}
			current1 = current1->ancestor;
			k--;
		}
		return 1;
	}
};

// ИНТЕРФЕЙС ДЛЯ ПРОГРАММЫ
bool lab5interface(TRIE *a)
{
	char i; int k;
	cline();
	output("Trie tree menu");
	output("Insert 0 to end the program");
	output("Insert 1 to add a new word backwards");
	output("Insert 2 to find words ending with...");
	cline();
	cin >> i;
	switch (i)
	{
	case '0': return 0;
	case '1':
	{
			  string s;
			  output("Enter the word to insert:");
			  cline();
			  cin >> s;
			  cline();
			  k = a->addbackwards(s);
			  if (k == 1)
			  {
				  output("Added");
			  }
			  else if (k == 2)
			  {
				  output("Already exists");
			  }
			  else
			  {
				  output("Error");
			  }
			  cline();
			  return 1;
	}
	case '2':
	{
			  string s;
			  output("Enter the ending:");
			  cline();
			  cin >> s;
			  cline();
			  found_by_ending *R = a->findbyending(s);
			  cline();
			  if (R == NULL)
			  {
				  output("Wrong input");
			  }
			  else
			  {
				  R->letters_output();
			  }
			  return 1;
	}
	default:
	{
			   output("Wrong input");
			   return 1;
			   break;
	}
	}
}
void main()
{
	TRIE a;
	while (lab5interface(&a)) {}
}

 
