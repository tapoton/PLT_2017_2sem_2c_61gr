
//Для заданного текста подсчитать колво слов состоящих только из согласных букв, используя trie деревья

#include <set>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class TRIE_TREE {
private:
    set<char> Vowels;
    int kol;

    struct TRIE {
        bool end_word = false;
        TRIE *Liter[26];
    };
    TRIE *begin;

    void ObNULLenie(TRIE *q) {
        for (int i = 0; i < 26; i++) {
            q->Liter[i] = NULL;
        }
    }

    void Delete_trie(TRIE* q) {
        for (int i = 0; i < 26; i++)
 {
            if (q->Liter[i] != NULL) {
                Delete_trie(q->Liter[i]);
            }
        }
        TRIE *p = q;
        delete p;
    }
public:

    int GetKol() {
        return kol;
    }

    ~TRIE_TREE() {
        Delete_trie(begin);
    }

    TRIE_TREE() {
        Vowels.insert('a');
        Vowels.insert('e');
        Vowels.insert('u');
        Vowels.insert('i');
        Vowels.insert('o');
        Vowels.insert('y');

        kol = 0;
        begin = new TRIE;
        ObNULLenie(begin);
    }
    void Add_words(string);
    void Without_vowels(TRIE*);
    void Vivod_trie_tree(TRIE*, int);

    TRIE* GetTrie() {
        return begin;
    }
};

int main() {

    TRIE_TREE A;
    string s;
    cout << "Vvedite slova cherez probel: \n";
    getline(cin, s);
    A.Add_words(s);
    cout << "Vivod dereva:\n";
    A.Vivod_trie_tree(A.GetTrie(), 0);
    A.Without_vowels(A.GetTrie());
    cout << "Kolichestvo slov bez glasnih= ";
    cout << A.GetKol();
    return 0;
}

void TRIE_TREE::Vivod_trie_tree(TRIE* q, int a) {
    for (int i = 0; i < 26; i++) {

        if (q->Liter[i] != NULL) {
            for (int j = 0; j < a; j++)
                cout << ' ';

            cout << (char) ('a' + i);
            if (q->Liter[i]->end_word) cout << ' ' << "(end)";
            cout << endl;
            Vivod_trie_tree(q->Liter[i], a + 1);
        }
    }
}

void TRIE_TREE::Add_words(string s) {
    int i = 0;
    TRIE *q = begin;
    while (i < s.length()) {
        if (s[i] == ' ') {
            q->end_word = true;
            q = begin;
        } else {
            if (q->Liter[s[i] - 'a'] == NULL) {
                q->Liter[s[i] - 'a'] = new TRIE;
                q = q->Liter[s[i] - 'a'];
                ObNULLenie(q);

            } else {
                q = q->Liter[s[i] - 'a'];
            }

        }
        i++;
    }
    q->end_word = true;
}

void TRIE_TREE::Without_vowels(TRIE* q) {
    if (q->end_word) {
        kol++;
    }
    for (int i = 0; i < 26; i++) {

        if (q->Liter[i] != NULL)

            if (!Vowels.count('a' + i)) {
                Without_vowels(q->Liter[i]);
            }
    }
}
