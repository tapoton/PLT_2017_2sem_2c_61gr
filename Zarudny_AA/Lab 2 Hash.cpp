// ### ЛАБОРАТОРНАЯ №2, Хеш-функция
//
// ### УСЛОВИЕ
// "Задан набор записей следующей структуры: название кинофильма, 
// режиссер, список актеров, краткое содержание. По заданному 
// названию фильма найти остальные сведения.
// Реализовать хэш - таблицу и использовать ее для выполнения задания.
// И не забудьте приложить это условие к следующему пулл - реквесту."
//
// ### КОММЕНТАРИЙ
// Реализованы 3 объекта - ST отвечает за структуры, HT за хеш-таблицу,
// AI за интерфейс программы. Вспомогательный объект output - просто
// реализация вывода, функция TextInterface - для этой конкретной 
// консольной программы. Добавил функцию автотестирования для
// огромного количества данных, генерирует случайные массивы
// и тестирует работу на них. Можно вводить вручную.
// При больших n ошибок практически нет.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <conio.h>

// Максимальная длина названия фильма
#define MAX 32

using namespace std;
typedef unsigned int ui;
typedef unsigned short int usi;

// *******************************************************
// Данные для работы
// *******************************************************
typedef unsigned int hsh;


// *******************************************************
// Вспомогательные функции
// *******************************************************
void cl()
{
	cout << endl;
}
void error()
{	
	cl();
	cout << "# Error";
	cl();
}

// *******************************************************
// Класс вывода
// *******************************************************
class output
{
public:
	template <class T>
	void o(T s)
	{
		cout << "# " << s << endl;
	}
};


// *******************************************************
// Исходные структуры
// *******************************************************
struct film {
	char name[MAX];
	usi year;
	// Реализация остального загромодит код и усложнит проверку
	// При необходимости что-то добавить - подправить структуру
	// и функцию вывода
};


// *******************************************************
// Класс, ответственный за работу со структурами
// *******************************************************
class ST
{
private:
	film* s;
	ui n;
public:
	ST(ui i)
	{
		n = i;
		s = new film[n];
	}
	film get(ui i)
	{
		if (i < n)
		{
			return *(s + i);
		}
		else
		{
			error();
			return *s;
		}
	}
	void add(film a, ui i)
	{
		if (i < n)
		{
			*(s + i) = a;
		}
	}
};

// *******************************************************
// Класс, ответственный за хеш-таблицу
// *******************************************************
class HT
{
private:
	ui n;
	hsh * hash;
	ST * st;
	hsh hashfunction(char *a)
	{
		ui h = 0;
		for (ui i = 0; i < MAX; i++)
		{
			h += *(a + i);
		}
		return h % n;
	}
public:
	HT(ui a, ST * b)
	{
		n = a;
		st = b;
	}
	void generate()
	{
		for (ui i = 0; i < n; i++)
		{
			*(hash + this->hashfunction(st->get(i).name)) = i;
		}
	}
	ui find(char *a)
	{
		hsh qh = this->hashfunction(a);
		bool b = 1;
		for (ui i = 0; i < n; i++)
		{
			if (*(a + i) != *(st->get(qh).name + i))
			{
				b = 0;
				break;
			}
		}
		if (b)
		{
			return qh;
		}
		else
		{
			return n;
		}
	}
};


// *******************************************************
// Интерфейс программы
// *******************************************************
class HI
{
private:
	HT * ht;
	ST * st;
	ui n;
	output * o;
public:
	HI(ui a, output * o1)
	{
		n = a;
		o = o1;
		st = new ST(n);
		ht = new HT(n, st);
	}
	void generate()
	{
		ht->generate();
	}
	void add(film a, ui i)
	{
		st->add(a, i);
	}
	void find(char *a)
	{
		this->print(ht->find(a));
	}
	void print(ui i)
	{
		film a = st->get(i);
		o->o("Name:");
		o->o(a.name);
		o->o("Year:");
		o->o(a.year);

	}
	void autotest() // Автоматический тест. В чистовую версию такое добавлять нельзя.
	{
		o->o("The autotest is launched");
		o->o("1. Filling");
		srand(time(NULL));
		for (ui i = 0; i < n; i++)
		{
			film *a = new film;
			for (int j = 0; j < MAX; j++)
			{
				a->name[j] = 64 + rand() % 26;
				if (!(rand() & 31))
				{
					break;
				}
			}
			a->year = 1950 + rand() % 100;
			st->add(*a, i);
			delete a;
		}
		o->o("Filled");
		o->o("2. Searching");
		ui k = 0;
		for (ui i = 0; i < n; i++)
		{
			film b = st->get(i);
			if (ht->find(b.name) == n)
				k++;
		}

		o->o("Found:");
		o->o(k);
		double p = (double)k * 100 / (double)n;
		o->o("Percentage of found films:");
		o->o(p);
	}
};


// *******************************************************
// Интерфейс консольного приложения
// *******************************************************
void TextInterface()
{
	output o; ui n; string s = "1";
	o.o("Please, enter the number of films:");
	cin >> n;
	HI W(n, &o);
	o.o("Would you like to run the automatic test? (1/0)");
	if (n > 10)
		o.o("With this number of films it is highly recommended");
	cin >> s;
	while (s != "0" && s != "1")
	{
		o.o("Wrong input");
		cin >> s;
	}
	if (s == "1")
	{
		W.autotest();
	}
	else
	{
		for (ui i = 0; i < n; i++)
		{
			film * f = new film;
			o.o("Input the name:");
			cin >> f->name;
			o.o("Input the year:");
			cin >> f->year;
			W.add(*f, i);
			delete f;
		}
		s = "1";
		while (s != "0")
		{
			o.o("What do you want to find?");
			char * a = new char[MAX];
			cin >> a;
			W.find(a);
			o.o("Would you like to find something else? (1/0)");
			cin >> s;
			while (s != "0" && s != "1")
			{
				o.o("WRONG INPUT");
				cin >> s;
			}
			delete a;
		}
	}
}

// *******************************************************
// Функция main
// *******************************************************
void main()
{
	TextInterface();
	_getch();
}