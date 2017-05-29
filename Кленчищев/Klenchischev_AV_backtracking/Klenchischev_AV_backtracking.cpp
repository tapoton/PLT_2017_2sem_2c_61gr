/*
Задан граф. Из графа удалить вершины, недостижимые из заданной.
*/
#include <iostream>
#include <fstream>

using namespace std;

int** initGraph(int count) {
    int **graph = new int*[count];
    for (int i = 0; i < count; i++)
        graph[i] = new int[count];

    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            graph[i][j] = 0;

    return graph;
}

bool readGraphFromFile(int **graph, int count) {
    ifstream f;
    f.open("input.txt");

    if (f) {
        for (int i = 0; i < count; i++)
            for (int j = 0; j < count; j++)
                f >> graph[i][j];

        return true;
    }

    return false;
}

void printGraph(int **graph, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++)
            cout << graph[i][j] << ' ';
        cout << endl;
    }
}

void checkVertexes(int **graph, int *checkedVertexes, int vertex, int count) {
    for (int i = 0; i < count; i++)
        if (graph[vertex][i] == 1 && checkedVertexes[i] == 0) {
            checkedVertexes[i] = 1;
            checkVertexes(graph, checkedVertexes, i, count);
        }
}

int** removeVertexesFromGraph(int **graph, int *checkedVertexes, int &count) {
    int newCount = 0;
    for (int i = 0; i < count; i++)
        if (checkedVertexes[i] == 1)
            newCount++;

    int **newGraph = new int*[newCount];
    for (int i = 0; i < newCount; i++)
        newGraph[i] = new int[newCount];

    int m = 0;
    for (int i = 0; i < count; i++) {
        if (checkedVertexes[i] != 0) {
            int n = 0;
            for (int j = 0; j < count; j++)
                if (checkedVertexes[j] != 0) {
                    newGraph[m][n] = graph[i][j];
                    n++;
                }
            m++;
        }
    }

    count = newCount;
    return newGraph;
}

int main() {
    int count;
    cout << "Input count of vertexes: ";
    cin >> count;

    int **graph = initGraph(count);

    if (readGraphFromFile(graph, count)) {
        cout << "Initial graph:" << endl;
        printGraph(graph, count);

        int *checkedVertexes = new int[count];
        for (int i = 0; i < count; i++)
            checkedVertexes[i] = 0;

        int vertex;
        cout << "Print the number of vertex that you want to check: ";
        cin >> vertex;
        checkedVertexes[vertex-1] = 1;
        checkVertexes(graph, checkedVertexes, vertex-1, count);

        cout << "Next vertexes are not available from selected vertex: ";
        for (int i = 0; i < count; i++)
            if (checkedVertexes[i] == 0)
                cout << i + 1 << ' ';
        cout << endl;

        graph = removeVertexesFromGraph(graph, checkedVertexes, count);
        cout << "Resulting graph:" << endl;
        printGraph(graph, count);
    }
    else
        cout << "Problem with opening input file" << endl;

    system("pause");
    return 0;
}