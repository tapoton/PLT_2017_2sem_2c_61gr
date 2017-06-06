
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

/*
 * 
 */
class sort_file {
public:
    void merge_sort();

   
    sort_file(string IFile) {
        ofstream fin(&IFile[0], ios::app);

        if (!fin) {
            cout << "File not found";
            return;
        }
        fin << '\r' << '\n';
        InputFile = IFile;
        string NewFile = IFile + '1';
        CopyFile(&IFile[0], &NewFile[0], true);
        fin.close();
        make_input_sum();


    }
private:
    string InputFile;

    bool of2_is_empty();
    void merge();
    void make_input_sum();
};

void sort_file::make_input_sum() {
    ifstream fin(&InputFile[0]);
    ofstream fin_sum("input_sum.txt");

    int sum;
    char c[20];
    while (!fin.eof()) {
        int j = -1;

        while (c[j] != ' ' && c[j] != '\n') {
            fin.get(c[++j]);
        }
        if (fin.eof()) break;
        sum = atoi(&c[0]);
        j = -1;
        while (c[j] != '\n' && !fin.eof()) {
            fin.get(c[++j]);
            if (c[j] == ' ')
                j = -1;
        }
        sum = sum + atoi(&c[0]);
        fin_sum << ' ' << sum;

    }

    fin.close();
    fin_sum.close();

}

void sort_file::merge_sort() {
    ifstream fin(&InputFile[0]);
    ifstream fin_sum("input_sum.txt");
    ofstream of1("f1.txt");
    ofstream of2("f2.txt");
    ofstream of1_sum("f1_sum.txt");
    ofstream of2_sum("f2_sum.txt");
    int a;
    bool choose_file = true;
    int b = -10000;
    char c;
    while (!fin_sum.eof()) {
        c = 0;
        fin_sum>>a;
        if (b > a)
            choose_file = !choose_file;
        if (choose_file) {
            of1_sum << ' ' << a;
            while (c != '\n') {

                fin.get(c);
                if (fin.eof()) break;
                of1 << c;
            }
        } else {
            of2_sum << ' ' << a;
            while (c != '\n') {
                if (fin.eof()) break;
                fin.get(c);
                of2 << c;
            }
        }

        b = a;
    }
    fin.close();
    fin_sum.close();
    of1_sum.close();
    of2_sum.close();
    of1.close();
    of2.close();
    merge();
}

void sort_file::merge() {

    int o1, o2;
    if (of2_is_empty()) {
        rename("f1.txt", "output.txt");
        remove(&InputFile[0]);
        remove("f1_sum.txt");
        remove("f2_sum.txt");
        remove("f2.txt");
        rename(&(InputFile + '1')[0], &InputFile[0]);
        return;
    }
    ofstream fin(&InputFile[0]);
    ofstream fin_sum("input_sum.txt");
    ifstream of1("f1.txt");
    ifstream of1_sum("f1_sum.txt");
    ifstream of2_sum("f2_sum.txt");
    ifstream of2("f2.txt");
    of2_sum>>o2;
    of1_sum>>o1;

    char c;

    while (true) {
        c = 0;
        if (o1 < o2) {
            while (c != '\n') {
                of1.get(c);
                if (!of1.eof())
                    fin << c;
                else break;
            }
            fin_sum << ' ' << o1;
            if (!of1_sum.eof())
                of1_sum >> o1;
            else {
                while (!of2.eof()) {
                    of2.get(c);
                    if (!of2.eof())
                        fin << c;
                    else break;
                }
                fin_sum << ' ' << o2;
                while (!of2_sum.eof()) {
                    of2_sum>>o2;
                    fin_sum << ' ' << o2;
                }
                break;
            }
        } else {
            while (c != '\n') {
                of2.get(c);
                if (!of2.eof())
                    fin << c;
                else break;

            }
            fin_sum << ' ' << o2;
            if (!of2_sum.eof())
                of2_sum >> o2;
            else {
                while (true) {
                    of1.get(c);
                    if (!of1.eof())
                        fin << c;
                    else break;
                }
                fin_sum << ' ' << o1;
                while (!of1_sum.eof()) {
                    of1_sum>>o1;
                    
                        fin_sum << ' ' << o1;
                    
                }
                break;
            }
        }

    }
    fin.close();
    of1_sum.close();
    of2_sum.close();
    of1.close();
    of2.close();
    fin_sum.close();
    merge_sort();
}

bool sort_file::of2_is_empty() {
    char c = '*';
    ifstream of2("f2.txt");
    of2>>c;
    if (c == '*')
        return true;
    else return false;


}

int main() {
    string input = "input.txt";
    sort_file A(input);
    A.merge_sort();
    return 0;
}

