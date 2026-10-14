#include<iostream>
#include<vector>

using namespace std;

using Clause = vector<int>;
using CNF = vector<Clause>;

int p(int i, int j){ return (i-1)*4 + j; }

int main(){

    CNF formula;

    // Svako predavanje se mora odrzati u nekom od termina
    for(int i = 1; i <= 4; i++){
        Clause c;
        for(int j = 1; j <= 4; j++){
            c.push_back(p(i, j));
        }
        formula.push_back(c);
    }

    for(int i = 1; i <= 4; i++){
        for(int j = 1; j <= 4; j++)
            for(int k = j + 1; k <= 4; k++){
                // Predavanje ne moze biti u 2 termina u isto vreme
                formula.push_back({-p(i, j), -p(i, k)});
                // U jednom terminu se ne mogu odrzavati dva predavanja
                formula.push_back({-p(j, i), -p(k, i)});
            }
    }

    // 1-L 2-A 3-VI 4-BP
    // L pre A
    formula.push_back({-p(1, 1), p(2, 2), p(2, 3), p(2, 4)});
    formula.push_back({-p(1, 2), p(2, 3), p(2, 4)});
    formula.push_back({-p(1, 3), p(2, 4)});
    formula.push_back({-p(1, 4)});
    
    // VI ni u prvom ni u poslednjem terminu
    formula.push_back({-p(3, 1)});
    formula.push_back({-p(3, 4)});

    // BP neposredno nakon L ili VI
    formula.push_back({-p(4, 4), p(1, 3), p(3, 3)});
    formula.push_back({-p(4, 3), p(1, 2), p(3, 2)});
    formula.push_back({-p(4, 2), p(1, 1), p(3, 1)});
    formula.push_back({-p(4, 1)});

    // A nije neposredno posle BP
    formula.push_back({-p(4, 1), -p(2, 2)});
    formula.push_back({-p(4, 2), -p(2, 3)});
    formula.push_back({-p(4, 3), -p(2, 4)});

    // L nije u poslednjem terminu
    formula.push_back({-p(1, 4)});

    // Blokiranje dva resenja
    // formula.push_back({-p(1, 1), -p(2, 2), -p(3, 3), -p(4, 4)});
    // formula.push_back({-p(1, 1), -p(2, 4), -p(3, 3), -p(4, 2)});

    // Dodatni uslov da L nije u prvom terminu
    // formula.push_back({-p(1, 1)});

    cout << "p cnf 16 " << formula.size() << endl; 
    for(const auto& c : formula){
        for(const auto& v : c)
            cout << v << " ";
        cout << 0 << endl;
    }
    return 0;
}