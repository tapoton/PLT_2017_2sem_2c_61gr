// ### ЛАБОРАТОРНАЯ №2: Хеш-функция, условие ниже
//
// ### УСЛОВИЕ
// "Задан набор записей следующей структуры: название кинофильма, 
// режиссер, список актеров, краткое содержание. По заданному 
// названию фильма найти остальные сведения.
// Реализовать хэш - таблицу и использовать ее для выполнения задания.
// И не забудьте приложить это условие к следующему пулл - реквесту."
//
// ### КОММЕНТАРИЙ
// Реализованы 2 класса: для работы с исходными данными и для хэширования
// Все параметры, кроме названия, опущены: код гибок и позволяет
// оптимизировать под нужные типы. Для изменения информации достаточно
// отредактировать структуру и функцию вывода. Весь вывод / ввод производится
// через само консольное приложение.
//
// AdHocInterface - Интерфейс для работы с заданными структурами, можно оптимизировать под конкретную память
// HashTable - класс для работы с хэшированием, неразрывно связан с AdHocInterface
// TextInterface - реализация конкретно этой консольной программы, обеспечивает работу с человеком
//

#include "stdafx.h"
#include <iostream>

// Максимальная длина названия фильма
#define MAX 32

using namespace std;

// Тип хешированных данных
typedef unsigned short int hsh;

// Вспомогательные функции
void cl()
{
	cout << "#" << endl;
}
void error()
{
	cl();
	cout << "_      FATAL ERROR!      _";
	cl();
}

// Заданная структура
struct A {
	char film[MAX];
	// Реализация остального загромодит код и усложнит проверку
	// При необходимости что-то добавить - подправить структуру
	// и функцию вывода OutputOfFound(int i);
};


// AdHocInterface - Интерфейс для работы с заданными структурами, можно оптимизировать под конкретную память
class AdHocInterface
{
private:
	int N;
	A* structures;
public:
	AdHocInterface(int n)
	{
		N = n;
		structures = new A[N];
	}
	char * ReturnAddressOfName(int i)
	{
		return (structures + i)->film;
	}
	char ReturnLetterOfName(int i, int j) // i - номер записи, j - номер буквы.
	{
		return (structures + i)->film[j];
	}
	void OutputOfFound(int i) // Вывести найденное куда бы то ни было
	{
		if (i < N)
		{
			cout << "# Found: " << (structures + i)->film << endl;
			// Здесь можно настраивать вывод
		}
		else
		{
			cout << "# Nothing found" << endl;
		}
	}
	void add(A* added, int i)
	{
		*(structures + i) = *added;
	}
};

// HashTable - класс для работы с хэшированием, неразрывно связан с AdHocInterface
class HashTable
{
private:
	int N;
	unsigned short int * hash;
	AdHocInterface* summoner;

	void generate()
	{
		hash = new hsh[N];
		for (int i = 0; i < N; i++)
		{
			*(hash + i) = this->hashfunction(summoner->ReturnAddressOfName(i));
		}
	}

	hsh hashfunction(char *s) // Простейший хеш суммированием
	{
		hsh r = 0;
		int j = 0;
		for (j = 0; j < MAX; j++)
		{
			if (*(s + j))
				r += *(s + j);
			else
				break;
		}
		return r;
	}

public:
	HashTable(int n, AdHocInterface* a)
	{
		// Количество структур
		N = n;
		summoner = a;
		// Сгенерировать хеш-массив
		this->generate();
	}

	void findbyhash(char *q)
	{
		int i, j; // Счётчики
		hsh qh = this->hashfunction(q); // Хеширование самого запроса
		bool b = 0; // Показатель совпадения запроса и результата
		bool c = 0; // Было ли вообще что-либо найдено
		for (i = 0; i < N; i++) // Проход всей таблицы с хешами
		{
			if (qh == *(hash+i)) // Если хеши запроса и одного из результатов совпали
			{
				b = 1; // Показатель полного совпадения запроса и результата
				for (j = 0; j < MAX; j++)
				{
					if (q[j] != summoner->ReturnLetterOfName(i, j)) // Сравнение имени полностью
					{
						b = 0;
						break;
					}
				}
				if (b)
				{
					summoner->OutputOfFound(i); // Вывести найденный результат
					c = 1;
					break;
				}
			}
		}
		if (!c)
		{
			summoner->OutputOfFound(N + 1); // Ничего не найдено
		}
	}
};

// TextInterface - реализация конкретно этой консольной программы, обеспечивает работу с человеком
void TextInterface() 
{
	cl();
	cout << "# Lab 2: Hash" << endl;
	cout << "# Input the number of films:" << endl;
	int n, i, j;
	cin >> n;
	AdHocInterface AHI = AdHocInterface(n);
	A res; // Переменная для работы (current)
	for (i = 0; i < n; i++) // Ручной ввод
	{
		cl(); // Вывести линию
		cout << "# Input the name:" << endl;
		char * added = new char[MAX];
		cin >> added;
		for (j = 0; j < MAX; j++)
		{
			res.film[j] = added[j];
		}
		// Остальное опущено, здесь можно добавить ввод любых других полей
		AHI.add(&res, i);
		delete added;
	}

	cl(); // Вывести линию // ХЭШ
	cout << "# Generating hash table..." << endl;
	HashTable HT = HashTable(n, &AHI);
	cout << "# Done" << endl;

	bool b = 1;
	while (b)
	{
		char *q = new char[MAX];
		cl(); // Вывести линию
		cout << "# What do you want to find?" << endl;
		cin >> q;
		HT.findbyhash(q);

		cl(); // Вывести линию
		cout << "# Would you like to find something else?" << endl;
		cout << "# 1 = Yes" << endl;
		cout << "# 0 = No (quit)" << endl;
		cin >> b;
		delete q;
	}
}


void main()
{
	TextInterface();
}
