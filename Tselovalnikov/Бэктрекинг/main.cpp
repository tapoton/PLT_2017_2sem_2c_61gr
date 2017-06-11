#include <iostream>
#include <fstream>

using namespace std;

// Функция инициализации матрицы, хранящей значения путей
int** initMatrix(int count) {
    int **matrix = new int*[count];
    for (int i = 0; i < count; i++)
        matrix[i] = new int[count];

    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            matrix[i][j] = 0;

    return matrix;
}

// Чтение значений из файла
int** readMatrixFromFile(int &count, int &start, int &finish) {
    ifstream f;
    f.open("input.txt");

    if (f) {
        f >> count;
        int **matrix = initMatrix(count);

        for (int i = 0; i < count; i++)
            for (int j = 0; j < count; j++)
                f >> matrix[i][j];

        f >> start >> finish;

        return matrix;
    }

    return NULL;
}

// Вывод матрицы, хранящей значения путей
void printMatrix(int **matrix, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
}

// "Блокирование" для дальнейшего использования в поиске пути заданного множества вершин
void unusedVertexes(int *checked, int count) {
    ifstream f;
    f.open("input.txt");

    int tmp;
    f >> tmp;
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            f >> tmp;
    f >> tmp >> tmp;

    while (!f.eof()) {
        f >> tmp;
        checked[tmp - 1] = -1;
    }
}

// Поиск пути из пункта from до пункта to (поиск в глубину)
void findPath(int **matrix, int *parent, int *checked, int from, int to, int count, int path, int &length) {
    for (int i = 0; i < count; i++)
        if (matrix[from][i] == 1 && checked[i] == 0) {
            checked[i] = 1;
            parent[i] = from + 1;
            if (i == to)
                length = path;
            if (length == 0)
                findPath(matrix, parent, checked, i, to, count, path + 1, length);
        }
}

// Вывод найденного пути
void printPath(int *parent, int length, int from, int to) {
    int *path = new int[length + 1];
    for (int j = 0; j <= length; j++)
        path[j] = 0;

    int tmp = to, i = length;
    while (tmp != from) {
        path[i] = tmp + 1;
        tmp = parent[tmp] - 1;
        i--;
    }
    path[0] = from + 1;

    cout << "Path from (" << from + 1 << ") to (" << to + 1 << "): " << path[0];
    for (int j = 1; j <= length; j++)
        cout << " -> " << path[j];
    cout << endl;
}

int main() {
    int count, start, finish;
    int **matrix = readMatrixFromFile(count, start, finish);

    if (matrix != NULL) {
        cout << "Matrix:" << endl;
        printMatrix(matrix, count);

        int *checkedVertexes = new int[count];
        for (int i = 0; i < count; i++)
            checkedVertexes[i] = 0;

        int *parent = new int[count];
        int *checked = new int[count];

        for (int i = 0; i < count; i++) {
            parent[i] = 0;
            checked[i] = 0;
        }

        checked[start - 1] = 1;

        unusedVertexes(checked, count);

        int length = 0;
        findPath(matrix, parent, checked, start - 1, finish - 1, count, 1, length);

        printPath(parent, length, start - 1, finish - 1);
    }
    else
        cout << "Problem with opening input file" << endl;

    system("pause");
    return 0;
}