include "globals.mzn";

int: n = 10;
int: cap = 10;

array [1..n] of int: sizes = [4, 8, 1, 4, 2, 1, 10, 3, 5, 2];
array [1..n] of var 1..n: bins;
array [1..n] of var 0..cap: load;

constraint bin_packing_load(load, bins, sizes);

% constraint bins[2] = bins[4];

solve minimize sum(i in 1..n)(bool2int(load[i] > 0));