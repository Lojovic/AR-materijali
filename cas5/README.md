# Podsetnik za sintaksu

## DIMACS (`.cnf`)

```text
c komentar
p cnf 3 2
1 -2 0
-1 2 3 0
```

```text
p cnf <broj_promenljivih> <broj_klauza>
<literal> <literal> ... 0
```

- Pozitivan literal: `3`; negativan literal: `-2`.
- Svaka klauza se završava nulom `0`.

## TPTP / Vampire (`.tptp`)

```tptp
% komentar
fof(ime_aksiome, axiom, ![X,Y]: (p(X) => q(X,Y))).
fof(ime_cilja, conjecture, ?[X]: p(X)).
```

| Sintaksa | Operator |
|---|---|
| `~p` | negacija |
| `p & q` | konjunkcija |
| `p \| q` | disjunkcija |
| `p => q` | implikacija |
| `p <=> q` | ekvivalencija |
| `p = q` | jednakost |
| `p != q` | nejednakost |
| `![X,Y]: (...)` | za sve |
| `?[X,Y]: (...)` | postoji |

Kvantifikovane promenljive počinju velikim slovom, a konstante malim.

```tptp
fof(a1, axiom, ![X]: (covek(X) => smrtan(X))).
fof(a2, axiom, covek(sokrat)).
fof(cilj, conjecture, smrtan(sokrat)).
```

## SMT-LIB 2 / Z3 (`.smt2`)

```smtlib
; komentar
(set-logic QF_LIA)
(declare-const x Int)
(declare-const b Bool)
(declare-sort T 0)
(declare-fun f (T) T)
(define-fun veci ((a Int) (c Int)) Bool (> a c))
(assert (> x 0))
(check-sat)
(get-model)
(get-value (x))
(exit)
```

| Sintaksa | Operator |
|---|---|
| `(not p)` | negacija |
| `(and p q)` | konjunkcija |
| `(or p q)` | disjunkcija |
| `(=> p q)` | implikacija |
| `(= p q)` | jednakost / ekvivalencija |
| `(distinct x y z)` | međusobna različitost |
| `(ite p a b)` | uslovni izraz |
| `(+ x y)` `(- x y)` `(* x y)` | aritmetika |
| `(div x y)` `(mod x y)` | celobrojno deljenje i ostatak |
| `(< x y)` `(<= x y)` `(> x y)` `(>= x y)` | poređenje |
| `(forall ((x Int)) p)` | za sve |
| `(exists ((x Int)) p)` | postoji |

```smtlib
(declare-const x (_ BitVec 32))
(assert (= x (_ bv42 32)))
; Zapis broja 42 u bitvektoru širine 32
(bvadd x (_ bv1 32))
(bvsub x (_ bv1 32))
(bvslt x (_ bv0 32)) ; signed
(bvult x (_ bv0 32)) ; unsigned
...
```

```smtlib
(minimize (+ x y))
(maximize x)
(check-sat)
(get-objectives)
```

## MiniZinc (`.mzn`)

```minizinc
% komentar
include "globals.mzn";
int: n = 8;
var 1..n: x;
array[1..n] of var 1..n: a;
array[1..n, 1..n] of var 0..1: m;
```

| Sintaksa | Operator |
|---|---|
| `not p` | negacija |
| `p /\ q` | konjunkcija |
| `p \/ q` | disjunkcija |
| `p -> q` | implikacija |
| `p <-> q` | ekvivalencija |
| `=` `!=` `<` `<=` `>` `>=` | poređenje |
| `div` `mod` | celobrojno deljenje i ostatak |
| `abs(x)` | apsolutna vrednost |
| `bool2int(p)` | Bool u 0/1 |

```minizinc
constraint forall(i in 1..n)(a[i] >= 1);
constraint forall(i, j in 1..n where i < j)(a[i] != a[j]);
constraint sum(i in 1..n)(a[i]) >= n;
constraint sum(i in 1..n)(bool2int(a[i] = 1)) = 2;
constraint all_different(a);
constraint all_different([a[i] - a[i+1] | i in 1..n-1])
% all_different očekuje niz kao parametar
```

```minizinc
solve satisfy;
% ili:
solve minimize x;
solve maximize x;

output [show(a) ++ " " ++ show(x)];
```

