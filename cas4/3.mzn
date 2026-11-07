include "globals.mzn";

int: n = 4;

array [1..n, 1..n] of var 1..n*n: x;

constraint all_different(x);
constraint forall(i in 1..n)(sum(j in 1..n)(x[i, j]) = 34);
constraint forall(j in 1..n)(sum(i in 1..n)(x[i, j]) = 34);
constraint sum(i in 1..n)(x[i, i]) = 34;
constraint sum(i in 1..n)(x[i, n - i + 1]) = 34;

constraint x[1, 1] < x[1, n] /\ x[1, 1] < x[n, 1] /\ x[1, 1] < x[n, n] /\ x[1, n] < x[n, 1];

solve satisfy;