#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

using Clause = vector<int>;
using CNF = vector<Clause>;

int p(int i){ return 3*i + 1;}
int q(int i){ return 3*i + 2;}
int r(int i){ return 3*i + 3;}
int c(int i){ return 15 + i + 1;}

int main(){

    CNF formula;

    for(int i = 0; i < 4; i++){
        // p(i+1) <=> -p(i)
        formula.push_back({-p(i+1), -p(i)});
        formula.push_back({p(i+1), p(i)});

        // q(i+1) <=> (p(i) <=> r(i))
        formula.push_back({q(i+1), p(i), r(i)});
        formula.push_back({q(i+1), -p(i), -r(i)});
        formula.push_back({-q(i+1), -p(i), r(i)});
        formula.push_back({-q(i+1), p(i), -r(i)});

        // r(i+1) <=> p(i) \/ q(i)
        formula.push_back({r(i+1), -p(i)});
        formula.push_back({r(i+1), -q(i)});
        formula.push_back({-r(i+1), p(i), q(i)});
    }

    // Pocetno stanje
    formula.push_back({-p(0)});
    formula.push_back({-q(0)});
    formula.push_back({-r(0)});

    Clause target;
    for(int i = 0; i <= 4; i++){
        // c(i) <=> stanje Si jeste (0, 1, 0)
        formula.push_back({-c(i), -p(i)});
        formula.push_back({-c(i), q(i)});
        formula.push_back({-c(i), -r(i)});
        formula.push_back({c(i), p(i), -q(i), r(i)});
        target.push_back(c(i));
    }
    formula.push_back(target);

    cout << "p cnf 20 " << formula.size() << endl;
    for(const Clause& c : formula){
        for(const int var : c)
            cout << var << " ";
        cout << 0 << endl;
    }    

    return 0;
}
