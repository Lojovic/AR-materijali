#include<iostream>
#include<vector>

using namespace std;

using Clause = vector<int>;
using CNF = vector<Clause>;

int k;

int p(int i, int j) { return (i - 1)*k + j; }

int main(){

    int V, E;
    cin >> V >> E >> k;

    CNF formula;
    
    // Svaki cvor mora imati bar neku boju
    for(int i = 1; i <= V; i++){
        Clause c;
        for(int j = 1; j <= k; j++)
            c.push_back(p(i, j));
        formula.push_back(c);
    }

    // Svaki cvor mora imati tacno jednu boju
    for(int i = 1; i <= V; i++){
        for(int j = 1; j <= k; j++)
            for(int l = j+1; l <= k; l++) 
                formula.push_back({-p(i, j), -p(i, l)});
    }

    // Susedni cvorovi ne smeju biti iste boje
    for(int i = 0; i < E; i++){
        int u, v;
        cin >> u >> v;

        for(int j = 1; j <= k; j++)
            formula.push_back({-p(u, j), -p(v, j)});
    }

    cout << "p cnf " << V * k << " " << formula.size() << endl; 
    for(const auto& c : formula){
        for(const auto& v : c)
            cout << v << " ";
        cout << 0 << endl;
    }
    return 0;
}