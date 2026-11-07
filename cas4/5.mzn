include "globals.mzn";

int: n = 7;

array [1..n] of var 1..2*n: first;
array [1..n] of var 1..2*n: second;

constraint all_different(first ++ second);
constraint forall(i in 1..n)(second[i] - first[i] = i + 1);

solve satisfy;

output [ show(sum(v in 1..n)(v * bool2int(first[v] = pos \/ second[v] = pos))) ++ " " | pos in 1..2*n];
