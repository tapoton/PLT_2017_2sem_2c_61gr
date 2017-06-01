// ����� ����� ������� ��������� ���������: ��������� �����, ���, ���������� �����. �� ���������� ������ ����� ��������� ��������.
// ��������� �.�., 2 ���� 61 ������.

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
		cout << "���������� �� �������" << endl;
	else
		cout << "��������� �����: " << pointer->number << "\n���: " << pointer->name << "\n���������� �����: " << pointer->salary << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int count;
	cout << "������� ���-�� �������: ";
	cin >> count;
	cout << "������� ������ ���-�������: ";
	cin >> sizeOfTable;

	createTable();

	int number, salary;
	string name;
	for (int i = 0; i < count; i++) {
		cout << "\n������� ��������� �����: ";
		cin >> number;
		cin.ignore();
		cout << "������� ���: " << endl;
		getline(cin, name);
		cout << "������� ���������� �����: ";
		cin >> salary;

		addElement(number, name, salary);
	}

	bool continueRunning = true;
	int choice;
	while (continueRunning) {
		cout << "\n�������� ��������: " << "\n1. �������� ������\n2. ����� ������ �� ���������� ������\n0. �����" << endl;
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "\n������� ��������� �����: ";
			cin >> number;
			cin.ignore();
			cout << "������� ���: ";
			getline(cin, name);
			cout << "������� ���������� �����: ";
			cin >> salary;
			addElement(number, name, salary);
			break;
		}
		case 2: {
			int number;
			cout << "\n������� ��������� �����: ";
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