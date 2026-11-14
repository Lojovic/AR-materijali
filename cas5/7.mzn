include"globals.mzn";

int: n = 5;

array [1..n] of var 0..n-1: x;

constraint all_different(x);

constraint all_different([abs(x[i] - x[i+1]) | i in 1..n-1]);

constraint x[1] < x[n];

solve satisfy;