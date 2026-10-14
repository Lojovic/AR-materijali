#include<iostream>
#include<vector>

using namespace std;

using Clause = vector<int>;
using CNF = vector<Clause>;

int main(){

    int a = 1, b = 2, c = 3;

    CNF formula;
    // Ana: Boris je lazov
    formula.push_back({-a, -b});
    formula.push_back({a, b});

    // Boris: Ana i Cane su iste vrste
    formula.push_back({b, a, c});
    formula.push_back({b, -a, -c});
    formula.push_back({-b, a, -c});
    formula.push_back({-b, -a, c});

    // Cane: Ana je lazov
    formula.push_back({-c, -a});
    formula.push_back({c, a});

    // Provera jedinstvenosti
    // formula.push_back({-a, b, c});

    cout << "p cnf 3 " << formula.size() << endl; 
    for(const auto& c : formula){
        for(const auto& v : c)
            cout << v << " ";
        cout << 0 << endl;
    }
    return 0;
}