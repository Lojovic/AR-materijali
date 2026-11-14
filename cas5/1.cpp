#include<iostream>
#include<vector>

using namespace std;

using Clause = vector<int>;
using CNF = vector<Clause>;

int k;

int p(int i, int j) { return (i - 1) * (k + 1) + j; }

int main(){

    CNF formula;

    cin >> k;

    const int V = 6;

    vector<pair<int, int>> E = {{1, 2}, {1, 3}, {2, 3}, {2, 4}, {3, 4}, {3, 5}, {4, 5}, {4, 6}, {5, 6}};

	// Mora postojati svaki čvor na putanji
    for(int l = 1; l <= k + 1; l++){
        Clause c;
        for(int i = 1; i <= V; i++)
            c.push_back(p(i, l));
        formula.push_back(c);
    }

	// Čvor se ne može pojavljivati dvaput na putanji
    for(int i = 1; i <= V; i++)
        for(int j1 = 1; j1 <= k + 1; j1++)
            for(int j2 = j1 + 1; j2 <= k + 1; j2++)
                formula.push_back({-p(i, j1), -p(i, j2)});

    // Za svaku poziciju j i svaki čvor v prethodnik j-tog čvora u putanji mora imati granu ka v.
    for (int v = 1; v <= V; v++) {
        for (int j = 2; j <= k + 1; j++) {
            Clause c = {-p(v, j)};
            for (auto e : E) {
                if (e.second == v)
                    c.push_back(p(e.first, j - 1));
            }
            formula.push_back(c);
        }
    }

	// Ne mogu dva čvora istovremeno da budu l-ti čvor na putanji
    for(int i = 1; i <= V; i++)
        for(int j = i + 1; j <= V; j++)
            for(int l = 1; l <= k + 1; l++)
                formula.push_back({-p(i, l), -p(j, l)});

	// Početni i kranji čvor
    formula.push_back({p(1, 1)});
    formula.push_back({p(6, k + 1)});

	// Ispis DIMACS formata
    cout << "p cnf " << V * (k + 1) << " " << formula.size() << endl;
    for(auto c : formula){
        for(auto p : c)
            cout << p << " ";
        cout << "0" << endl;
    }

    return 0;
}