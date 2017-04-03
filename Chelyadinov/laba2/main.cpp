
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

class hash_tabl {
private:
    int kol_words;

    struct node {
        string word;
        node *next;
    };

    struct hash {
        int count;
        string word;
        hash *next;
    };
    hash *begin[1000];

    int Hash_func(string s) {
        int index = 0;
        for (int i = 0; i < s.length(); i++) {
            index += s[i] - 'a';
        }
        return index;
    }

    bool Check_space(string s) {
        int i = 1;
        while (i < s.length()) {
            if (s[i] == ' ') return true;
            i++;
        }
        return false;

    }

    void Vivod_slovosochetaniy(node *q, string s) {
        node *k;
        if (Check_space(s))
            cout << &s[1] << endl;
        for (k = q; k != NULL; k = k->next) {
            Vivod_slovosochetaniy(k->next, s + ' ' + k->word);

        }

    }




public:
    void GroupANDPrint_words();
    void Vvod_slov();

    hash_tabl() {

        for (int j = 0; j < 1000; j++) {
            begin[j] = NULL;
        }
    }

    void Print() {
        cout << "\nVivod_hash_tablici:\n";
        hash *q;
        for (int j = 0; j < 1000; j++) {
            q = begin[j];
            while (q != NULL) {
                cout << q->word << '-' << q->count << ' ';
                q = q->next;
            }
            if (begin[j])
                cout << endl;
        }
    }

};

int main(int argc, char** argv) {

    hash_tabl A;
    A.Vvod_slov();
    A.Print();
    A.GroupANDPrint_words();
    return 0;
}

void hash_tabl::Vvod_slov() {
    kol_words = 1;
    int index;
    hash *q;
    string s;
    ifstream fin("input.txt");
    if (!fin) {
        cout << "Zadan ne verniu put' k failu";
        exit(0);
    }
    while (!fin.eof()) {
        fin>>s;
        index = Hash_func(s);
        q = begin[index];
        if (q == NULL) {
            hash *h = new hash;
            h->word = s;
            h->count = 1;
            h->next = NULL;
            begin[index] = h;
        } else {
            if (q->word == s) {
                q->count++;
            } else {


                while (q->next) {
                    if (s == q->next->word) {
                        q->next->count++;
                        break;
                    }
                    q = q->next;
                }
                if (q->next == NULL) {
                    hash *h = new hash;
                    h->word = s;
                    h->count = 1;
                    h->next = NULL;
                    q->next = h;
                }
            }
        }
    }
}

void hash_tabl::GroupANDPrint_words() {

    string s;

    hash *q;
    node *begin_node = NULL;
    ;
    for (int j = 0; j < 1000; j++) {
        q = begin[j];
        while (q != NULL) {
            if (q->count > 1) {
                node *c = new node;
                c->word = q->word;
                c->next = begin_node;
                begin_node = c;
            }
            q = q->next;
        }
    }

    if (begin_node != NULL && begin_node->next != NULL) //есть ли в списке более одного слова
    {
        cout << "\nSlovosochetaniya:\n";
        Vivod_slovosochetaniy(begin_node, s);

    } else cout << "\nSlovosochetaniy net.\n";
    
}
