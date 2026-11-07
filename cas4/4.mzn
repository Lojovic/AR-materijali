include "globals.mzn";

int: k = 5;
int: u = 2^(k-1) - 1;

array [1..k] of var 0..u: x;

constraint x[1] = 0;
constraint all_different([x[j] - x[i] | i, j in 1..k where i < j]);
constraint forall(i in 1..k-1)(x[i] < x[i+1]);

solve minimize x[k];