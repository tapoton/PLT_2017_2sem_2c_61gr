#include <iostream>
#include <fstream>

using namespace std;

struct queue {
    int vertex;
    queue *next;
};
queue *head = NULL;
queue *tail = NULL;

void pushVertex(int vertex) {
    queue *newVertex = new queue;
    newVertex->vertex = vertex;
    newVertex->next = NULL;

    if (head != NULL) {
        tail->next = newVertex;
        tail = newVertex;
    }
    else
        head = tail = newVertex;
}

int popVertex() {
    if (head != NULL) {
        queue *tmp = head;
        int vertex = tmp->vertex;
        head = head->next;
        delete tmp;
        return vertex;
    }
    return -1;
}

int** initAndReadGraph(int &count, int &start, int &finish) {
    ifstream f;
    f.open("input.txt");

    if (f) {
        f >> count;
        int **graph = new int*[count];
        for (int i = 0; i < count; i++)
            graph[i] = new int[count];

        for (int i = 0; i < count; i++)
            for (int j = 0; j < count; j++)
                f >> graph[i][j];

        f >> start >> finish;

        return graph;
    }

    return NULL;
}

void printGraph(int **graph, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++)
            cout << graph[i][j] << ' ';
        cout << endl;
    }
}

bool findPath(int **graph, bool *checked, int *pathLength, int *parent, int count, int finish) {
    int length = 0;
    while (head != NULL) {
        int currentVertex = popVertex();
        if (currentVertex == -1)
            return 0;

        length++;
        for (int i = 0; i < count; i++) {
            if (graph[currentVertex][i] == 1 && checked[i] == 0) {
                checked[i] = 1;
                pathLength[i] = length;
                parent[i] = currentVertex + 1;
                if (i == finish - 1)
                    return 1;
                pushVertex(i);
            }
        }
    }
    return 0;
}

void printPath(int *pathLength, int *parent, int start, int finish) {
    int length = pathLength[finish - 1];
    int *path = new int[length];
    int i = finish, j = length - 1;
    path[j] = i;

    while (i != 0) {
        i = parent[i - 1];
        path[--j] = i;
    }

    cout << "Path length from " << start << " to " << finish << " = " << length << endl;
    cout << "Path: " << start;

    for (i = 0; i < length; i++)
        cout << " -> " << path[i];
    cout << endl;
}

int main() {
    int count, start, finish;

    int **graph = initAndReadGraph(count, start, finish);

    if (graph) {
        if ((start >= 1 || start <= count) && (finish >= 1 || finish <= count)) {
            if (start != finish) {
                cout << "Initial graph:" << endl;
                printGraph(graph, count);
                cout << "Start in " << start << endl << "Finish in " << finish << endl;

                bool *checked = new bool[count];
                int *pathLength = new int[count];
                int *parent = new int[count];
                for (int i = 0; i < count; i++) {
                    checked[i] = 0;
                    pathLength[i] = 0;
                    parent[i] = 0;
                }
                checked[start - 1] = 1;

                pushVertex(start - 1);

                bool isPath = findPath(graph, checked, pathLength, parent, count, finish);
                if (isPath)
                    printPath(pathLength, parent, start, finish);
                else
                    cout << "There is no path between " << start << " and " << finish << endl;
            }
            else
                cout << "Path length = 0" << endl;
        }
        else
            cout << "Wrong input data" << endl;
    }
    else
        cout << "Problem with opening input file" << endl;

    system("pause");
    return 0;
}