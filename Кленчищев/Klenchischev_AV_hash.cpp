// Задан набор записей следующей структуры: табельный номер, ФИО, заработная плата. По табельному номеру найти остальные сведения.
// Кленчищев А.В., 2 курс 61 группа.

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>

using namespace std;


int sizeOfTable;

struct hashTable {
	int number;
	string name;
	int salary;
	hashTable *next;
} **table;


void createTable() {
	table = new hashTable*[sizeOfTable];
	for (int i = 0; i < sizeOfTable; i++)
		table[i] = NULL;
}

int hashFunction(int number) {
	int sum = 0;
	while (number > 0) {
		sum += number % 10;
		number /= 10;
	}
	return (sum % sizeOfTable);
}

void addElement(int number, string name, int salary) {
	hashTable *element = new hashTable;
	hashTable *pointer;
	int hash = hashFunction(number);
	pointer = table[hash];
	table[hash] = element;
	element->next = pointer;
	element->number = number;
	element->name = name;
	element->salary = salary;
}

void findElement(int number) {
	hashTable *pointer;
	pointer = table[hashFunction(number)];

	while (pointer && pointer->number != number)
		pointer = pointer->next;

	if (!pointer)
		cout << "Совпадений не найдено" << endl;
	else
		cout << "Табельный номер: " << pointer->number << "\nФИО: " << pointer->name << "\nЗаработная плата: " << pointer->salary << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int count;
	cout << "Введите кол-во записей: ";
	cin >> count;
	cout << "Введите размер хеш-таблицы: ";
	cin >> sizeOfTable;

	createTable();

	int number, salary;
	string name;
	for (int i = 0; i < count; i++) {
		cout << "\nВведите табельный номер: ";
		cin >> number;
		cin.ignore();
		cout << "Введите ФИО: " << endl;
		getline(cin, name);
		cout << "Введите заработную плату: ";
		cin >> salary;

		addElement(number, name, salary);
	}

	bool continueRunning = true;
	int choice;
	while (continueRunning) {
		cout << "\nВыберите операцию: " << "\n1. Добавить запись\n2. Найти запись по табельному номеру\n0. Выход" << endl;
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "\nВведите табельный номер: ";
			cin >> number;
			cin.ignore();
			cout << "Введите ФИО: ";
			getline(cin, name);
			cout << "Введите заработную плату: ";
			cin >> salary;
			addElement(number, name, salary);
			break;
		}
		case 2: {
			int number;
			cout << "\nВведите табельный номер: ";
			cin >> number;
			findElement(number);
			break;
		}
		default: {
			continueRunning = false;
			break;
		}
		}
	}

    return 0;
}