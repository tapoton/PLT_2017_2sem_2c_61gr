#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

// Размер хеш-таблицы
const unsigned int sizeOfHashtable = 64;

// Структура данных в хеш-таблице
struct Node {
    string key;
    int count;
    Node *next;
};
Node *hashTable[sizeOfHashtable];

// Функции работы с хеш-таблицей
void hashtableInit(Node **hashtable); // инициализация  хеш-таблицы
int hashFunction(string key); // хеш-функция
bool hashtableAdd(Node **hashtable, string key); // добавление слова key в хеш-таблицу
Node* hashtableSearch(Node **hashtable, string key); // поиск слова key в хеш-таблице
void clearHashtable(Node **hashtable); // очистка хеш-таблицы

// Функция считывания входных данных из файла
bool readDataFromFile(string fileName);

// Функция добавления слова в линейный список
void addNode(Node *words, string key, int count);

int main() {
    hashtableInit(hashTable);

    // Считываем все слова из файла input.txt
    bool readedFromFile = readDataFromFile("input.txt");

    if (!readedFromFile)
        cout << "Error reading from file" << endl;
    else {
        Node *words = new Node;

        // Просматриваем всю таблицу, находим слова, которые повторяются > 5 раз и добавляем в линейный список
        for (int i = 0; i < sizeOfHashtable; i++) {
            for (Node *node = hashTable[i]; node != NULL; node = node->next) {
                if (node->count > 5)
                    addNode(words, node->key, node->count);
            }
        }

        // Выводим полученный линейный список
        Node *ptr = words->next;
        while (ptr) {
            cout << "Word: " << ptr->key << endl;
            cout << "Count: " << ptr->count << endl;
            ptr = ptr->next;
        }
    }

    clearHashtable(hashTable);
    system("Pause");
    return 0;

}

void hashtableInit(Node **hashTable) {
    for (int i = 0; i < sizeOfHashtable; i++)
        hashTable[i] = NULL;
}

int hashFunction(string key) {
    int hash = 0;

    for (int i = 0; i < key.length(); i++)
        hash = 31 * hash + (unsigned char)key[i];

    hash = hash % sizeOfHashtable;
    return hash;
}

bool hashtableAdd(Node **hashTable, string key) {
    int index = hashFunction(key);
    Node *searchNode = hashtableSearch(hashTable, key);

    if (searchNode == NULL) {
        Node *node = new Node;
        node->key = key;
        node->next = hashTable[index];
        node->count = 1;
        hashTable[index] = node;

        return  true;
    }
    else
        searchNode->count++;

    return false;
}

Node *hashtableSearch(Node **hashTable, string key) {
    int index = hashFunction(key);

    for (Node *node = hashTable[index]; node != NULL; node = node->next)
        if (node->key == key)
            return node;

    return NULL;
}

void clearHashtable(Node **hashTable) {
    for (int i = 0; i < sizeOfHashtable; i++) {
        Node *head = hashTable[i];
        if (head != NULL) {
            Node *prev = NULL;
            while (head) {
                prev = head;
                head = head->next;
                prev->next = NULL;
                delete prev;
            }
        }
        hashTable[i] = head;
    }
}

bool readDataFromFile(string fileName) {
    ifstream inputFile;
    inputFile.open(fileName);

    string key;

    if (inputFile) {
        while (!inputFile.eof()) {
            inputFile >> key;

            bool isAdded = hashtableAdd(hashTable, key);
        }
        return true;
    }

    return false;
}

void addNode(Node *words, string key, int count) {
    Node *newNode = new Node;
    newNode->key = key;
    newNode->count = count;
    newNode->next = NULL;

    Node *ptr = words;
    if (!ptr)
        words = newNode;
    else {
        while (ptr->next != NULL)
            ptr = ptr->next;

        ptr->next = newNode;
    }
}