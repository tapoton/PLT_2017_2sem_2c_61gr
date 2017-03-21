
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

class hash_tabl {
private:
    int kol_words;

    struct hash {
        int count = 0;
        string word;
        hash *next;
    };
    hash *begin[];

    void Be_back_hash(hash* begin) {
        hash *q = begin;
        hash *t;
        while (q->next != NULL) {
            if ((q->count)<(q->next->count)) {
                t = q;
                q = q->next;
                t->next = NULL;
            } else if (q->count == q->next->count) {
                q = q->next;
            }
        }
    }

    bool Check_space(string s) {
        int i = 1;
        while (i < s.length()) {
            if (s[i] == ' ') return true;
            i++;
        }
        return false;

    }

    void Vivod_slovosochetaniy(hash *q, string s) {
        hash *k;
        if (Check_space(s))
            cout << &s[1] << endl;
        for (k = q; k != NULL; k = k->next) {
            Vivod_slovosochetaniy(k->next, s + ' ' + k->word);

        }

    }

    void Create_tabl(int i) {

        for (int j = 0; j < i; j++) {
            begin[j] = NULL;
        }
    }

    string Cut_string(string &s) {
        int i = 0;
        string s1;
        while (s[i] != ' ' && i < s.length()) {
            s1 = s1 + s[i++];
        }
        s = &s[i + 1];
        return s1;
    }
public:
    void GroupANDPrint_words();
    void Vvod_slov();

    void Print() {
        cout<<"\nVivod_hash_tablici:\n";
        hash *q;
        for (int j = 0; j < kol_words; j++) {
            q = begin[j];
            while (q != NULL) {
                cout << q->word << '-' << q->count << endl;
                q = q->next;
            }
        }
    }

};

int main(int argc, char** argv) {

    hash_tabl A;
    A.Vvod_slov();
    A.Print();
    A.GroupANDPrint_words();
    A.Print();
    return 0;
}

void hash_tabl::Vvod_slov() {
   kol_words = 1;
    int k;
    hash *q;
    string s, s1;
    ifstream fin("input.txt");
    fin>>s;
    while (!fin.eof()) {
        fin>>s1;
        s = s + ' ' + s1;
        kol_words++;
    }
    Create_tabl(kol_words);
    for (int j = 0; j < kol_words; j++) {
        k = 0;
        q = begin[0];
        s1 = Cut_string(s); 
        while (k < kol_words) {
            if (q == NULL) {
                if (k == kol_words - 1) {
                    hash* h = new hash;
                    h->word = s1;
                    h->count++;
                    h->next = begin[0];
                    begin[0] = h;
                    break;
                }
                k++;
                q = begin[k];
                

            } else {
                if (q->word == s1) {
                    begin[k] = begin[k]->next;
                    q->next = begin[k + 1];
                    begin[k + 1] = q;
                    q->count++;
                    break;
                } else {
                    while (q->next && q->next->word != s1)
                        q = q->next;
                    if (q->next != NULL && q->next->word == s1) {
                        hash *t = q->next;
                        q->next = q->next->next;
                        t->next = begin[k + 1];
                        begin[k + 1] = t;
                        t->count++;
                        break;
                    }
                }
                if (q != NULL)
                q = q->next;
            }
            
        }
    }
}

void hash_tabl::GroupANDPrint_words() {
    hash* t;
    
    for (int k = 1; k < kol_words; k++) {  //объединяем все непустые списки начиная с индекса 1
        if (begin[k] != NULL) {
            hash* q = begin[k];
            while (q->next != NULL) {
                q = q->next;
            }
            k++;
            while (begin[k] == NULL && k < kol_words) {
                k++;
            }
            if (k < kol_words)
                q->next = begin[k];
            k--;
        }
    }
    string s;
    int k = 1;
    while (begin[k] == NULL && k < kol_words) {
        k++;
    }
    if(begin[k]!=NULL&&begin[k]->next!=NULL) //есть ли в списке более одного слова
    {cout<<"\nSlovosochetaniya:\n";
    Vivod_slovosochetaniy(begin[k], s);
    Be_back_hash(begin[k]); //восстановление таблицы
    } else cout<<"\nSlovosochetaniy net.\n";
    
}