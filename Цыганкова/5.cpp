
/*

*/
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

struct M{
    int N;
    int inf;
};

int SumFL (int *mas, int n) {
    return (mas[0]+mas[n-1]);
}

/*Cортировка двухпутевым двухфазным простым слиянием*/
void SimpMergSort (M *mas, int kol){
    fstream f;
    f.open("f.txt", ios::out);
    for(int i=0; i<kol; i++) {
        f << mas[i].inf << ' ' <<  mas[i].N << ' ';
    }
    f.close();
    M a1,a2;
    int k=1;
    while (k<kol){
        fstream f1;
        fstream f2;
        f.open("f.txt", ios::in);
        f1.open("f1.txt", ios::out);
        f2.open("f2.txt", ios::out);
        if ( !f.eof() ) {
            f >> a1.inf >> a1.N;
        }
        while (!f.eof()){                            //Разбиение
            for (int i=0; i<k && !f.eof(); i++ ){
                f1 << a1.inf << ' ' << a1.N << ' ';
                f >> a1.inf >> a1.N;
            }
            for (int j=0; j<k && !f.eof(); j++ ){
                f2 << a1.inf << ' ' << a1.N << ' ';
                f >> a1.inf >> a1.N;
            }
        }
        f.close();
        f1.close();
        f2.close();
        f.open("f.txt", ios::out);
        f1.open("f1.txt", ios::in);
        f2.open("f2.txt", ios::in);
        if ( !f1.eof() ){
            f1 >> a1.inf >> a1.N;
        }
        if ( !f2.eof() ){
            f2 >> a2.inf >> a2.N;
        }
        while (!f1.eof() && !f2.eof()){               //Слияние
            int i=0,j=0;
            while ( i<k && j<k && !f1.eof() && !f2.eof()) {
                if ( a1.inf < a2.inf ) {
                    f << a1.inf << ' ' << a1.N << ' ';
                    f1 >> a1.inf >> a1.N;
                    i++;
                }
                else {
                    f << a2.inf << ' ' << a2.N << ' ';
                    f2 >> a2.inf >> a2.N;
                    j++;
                }
            }
            while ( i<k && !f1.eof() ) {
                f << a1.inf << ' ' << a1.N << ' ';
                f1 >> a1.inf >> a1.N;
                i++;
            }
            while ( j<k && !f2.eof() ) {
                f << a2.inf << ' ' << a2.N << ' ';
                f2 >> a2.inf >> a2.N;
                j++;
            }
        }
        while ( !f1.eof() ) {
            f << a1.inf << ' ' << a1.N << ' ';
            f1 >> a1.inf >> a1.N;
        }
        while ( !f2.eof() ) {
            f << a2.inf << ' ' << a2.N << ' ';
            f2 >> a2.inf >> a2.N;
        }
        f.close();
        f1.close();
        f2.close();
        k *= 2;
    }
}


int main(){
    remove("result.txt");
    remove("f.txt");
    int m,n;
    int c,b;
    cout<<"Введите число строк в матрице =  ";
    cin>>n;
    cout<<"Число столбцов =  ";
    cin>>m;
    cout<<"Введите диапозон чисел(два числа): "<<endl;
    cin>>c>>b;
    ofstream fout("start.txt");
    for(int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            fout << (c + rand() % (b - c + 1)) << " ";
        }
        fout << "\r\n";
    }
    fout.close();
    int matr[m][n];
    ifstream fin("start.txt");
    for(int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            fin >> matr[i][j];
        }
    }
    fin.close();
    M S[m];
    for(int i=0; i<m; i++) {
        S[i].N = i;
        S[i].inf = SumFL (matr[i], n);
    }

    SimpMergSort  (S, m);

    int k,l;
    fstream f;
    f.open("f.txt", ios::in);
    ofstream f2out("result.txt");
    for(int i=0; i<m; i++) {
        f >> k >> l;
        for(int j=0; j<n; j++){
            f2out << matr[l][j] <<' ';
        }
        f2out << "\r\n";
    }
    f.close();
    f2out.close();

    system("PAUSE");
    return EXIT_SUCCESS;
}
