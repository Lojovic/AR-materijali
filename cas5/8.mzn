int: n = 7;

int: u = n * (n - 1) div 6;

array [1..3, 1..u] of var 1..n: x;

constraint forall(i in 1..u)(
              x[1, i] < x[2, i] /\ x[2, i] < x[3, i] 
);

constraint forall(i, j in 1..n where i < j)(
                sum(k in 1..u)(
                    bool2int(x[1, k] = i /\ x[2, k] = j \/
                             x[1, k] = i /\ x[3, k] = j \/
                             x[2, k] = i /\ x[3, k] = j)
                ) = 1
);

constraint x[1, 1] = 1 /\ x[2, 1] = 2 /\ x[3, 1] = 3; 

solve satisfy;

output [ show(x[1, i]) ++ " " ++ show(x[2, i]) ++ " " ++ show(x[3, i]) ++ "\n" | i in 1..u];