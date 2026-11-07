int: w = 2;
int: players = 16;
int: groups = 4;
int: group_size = 4;
array[1..w,1..players] of var 1..groups: grp;

constraint forall(t in 1..w, g in 1..groups)(
 sum(p in 1..players)(bool2int(grp[t,p]=g)) = group_size
);

constraint forall(p,q in 1..players where p<q)(
 sum(t in 1..w)(bool2int(grp[t,p]=grp[t,q])) <= 1
);

constraint forall(p in 1..players)(grp[1,p] = (p-1) div group_size+1);
constraint forall(t in 2..w)(grp[t,1]=1);

solve satisfy;

output [concat(["Nedelja "++show(t)++":\n" ++
 concat(["  Grupa "++show(g)++": " ++
 concat([show(p)++" " | p in 1..players where fix(grp[t,p])=g]) ++ "\n"
 | g in 1..groups]) | t in 1..w])];