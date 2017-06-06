#include <cstdlib>
#include <fstream>
using namespace std;

int countVertex(bool **matrix, bool *visited, int current, int n, int count) {
    visited[current]=1;
    count++;
    for (int i=0;i<n;i++)
        if (matrix[i][current]&&!visited[i])
            count=countVertex(matrix,visited,i,n,count);
    return count;
}
int main() {

    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n,s;
    fin>>n>>s;
    bool **matrix=new bool*[n];
    for (int i=0;i<n;i++)
        matrix[i]=new bool[n];
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            fin>>matrix[i][j];
    bool *visited = new bool[n];
    for(int i=0;i<n;i++)
        visited[i]=0;
    int count=countVertex(matrix,visited,s-1,n,0);
    fout<<count;
    fin.close();
    fout.close();    
    return 0;
}

