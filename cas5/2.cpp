#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

using Clause = vector<int>;
using CNF = vector<Clause>;

int p(int i) { return 3*i + 1; }
int q(int i) { return 3*i + 2; }
int r(int i) { return 3*i + 3; }

int cilj(int i, int k) { return 3*(k + 1) + i + 1; }

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Upotreba: " << argv[0] << " reach|cycle broj_taktova\n";
        return 1;
    }
    string mode = argv[1];
    int k = atoi(argv[2]);
    if ((mode != "reach" && mode != "cycle") || k < 0) {
        cerr << "Neispravan rezim ili broj taktova.\n";
        return 1;
    }

    CNF formula;
    for (int i = 0; i < k; i++) {
        // p(i+1) <=> NOT q(i)
        formula.push_back({-p(i+1), -q(i)});
        formula.push_back({p(i+1), q(i)});

        // q(i+1) <=> (p(i) XOR r(i))
        formula.push_back({q(i+1), p(i), -r(i)});
        formula.push_back({q(i+1), -p(i), r(i)});
        formula.push_back({-q(i+1), -p(i), -r(i)});
        formula.push_back({-q(i+1), p(i), r(i)});

        // r(i+1) <=> (q(i) OR r(i))
        formula.push_back({-r(i+1), q(i), r(i)});
        formula.push_back({r(i+1), -q(i)});
        formula.push_back({r(i+1), -r(i)});
    }

    int variables = 3*(k+1);
    if (mode == "reach") {
        // Pocetno stanje (0,1,0).
        formula.push_back({-p(0)});
        formula.push_back({q(0)});
        formula.push_back({-r(0)});

        // cilj(i) <=> p(i) AND q(i) AND r(i)
        Clause neki_takt;
        for (int i = 0; i <= k; i++) {
            int c = cilj(i, k);
            formula.push_back({-c, p(i)});
            formula.push_back({-c, q(i)});
            formula.push_back({-c, r(i)});
            formula.push_back({c, -p(i), -q(i), -r(i)});
            neki_takt.push_back(c);
        }
        // Cilj se dostize u nekom taktu od 0 do k.
        formula.push_back(neki_takt);
        variables += k + 1;
    } else {
        // Postoji proizvoljno pocetno stanje koje se ponavlja posle k taktova.
        formula.push_back({-p(0), p(k)});
        formula.push_back({p(0), -p(k)});
        formula.push_back({-q(0), q(k)});
        formula.push_back({q(0), -q(k)});
        formula.push_back({-r(0), r(k)});
        formula.push_back({r(0), -r(k)});
    }

    cout << "p cnf " << variables << " " << formula.size() << "\n";
    for (const Clause& c : formula) {
        for (int lit : c) cout << lit << " ";
        cout << "0\n";
    }
    return 0;
}
