# Uvod u SMT i SMT-LIB 2

Na prethodnim časovima upoznali smo se sa iskaznom logikom, logikom prvog reda i automatskim dokazivanjem teorema. Sada ćemo razmotriti problem **SMT (Satisfiability Modulo Theories)**, koji omogućava ispitivanje zadovoljivosti logičkih formula uzimajući u obzir značenje određenih matematičkih operacija i relacija.

Podsetimo se primera sa prethodnog časa:

**Za svaki prirodan broj `x` postoji prirodan broj `y` takav da je `x + y > 50`.**

U logici prvog reda ovo tvrđenje zapisujemo kao:

```text
∀x ∈ N ∃y ∈ N (x + y > 50)
```

Videli smo da ovo tvrđenje ne možemo neposredno izraziti konačnom formulom iskazne logike, jer se odnosi na beskonačan skup prirodnih brojeva. Logika prvog reda omogućava nam da pomoću kvantifikatora izrazimo tvrđenje u konačnom obliku.

Međutim, postoji još jedan problem. U opštoj logici prvog reda funkcijski simbol `+` i relacijski simbol `>` nemaju unapred određeno značenje. Njihovo značenje zavisi od interpretacije.

Na primer, možemo posmatrati formulu:

```text
x + y > 50
```

U opštoj logici prvog reda `+` možemo tretirati kao binarni funkcijski simbol, a `>` kao binarni relacijski simbol, bez pretpostavke da predstavljaju standardno sabiranje i poređenje brojeva.

Ako želimo da rezonujemo o standardnoj aritmetici, potrebno je da nekako obezbedimo da ovi simboli imaju odgovarajuće značenje.

Jedan pristup bio bi da definišemo aksiome kojima opisujemo njihovo ponašanje. Međutim, za složenije matematičke strukture takav pristup može biti nepraktičan.

SMT nam upravo omogućava da određene matematičke teorije budu ugrađene u sam proces rešavanja. SMT problem se bavi ispitivanjem zadovoljivosti formule logike prvog reda, pri čemu je zadata teorija, tj. aksiome koje moraju da važe i najčešće služe da fiksiraju interpretaciju određenih simbola.

Na primer, SMT rešavač koji podržava aritmetiku celih brojeva već poznaje značenje operacija sabiranja, oduzimanja, množenja konstantom i poređenja celih brojeva.

Zato možemo zapisati ograničenja poput:

```text
x + y > 50
x >= 0
y >= 0
```

i od SMT rešavača tražiti da proveri da li postoje vrednosti promenljivih koje ih zadovoljavaju.

Za razliku od SAT rešavača, koji promenljivama dodeljuju istinitosne vrednosti, SMT rešavači mogu raditi sa promenljivama različitih tipova, kao što su celi brojevi, realni brojevi, bitvektori i nizovi.

## SMT rešavači

**SMT rešavač** je program koji ispituje zadovoljivost logičke formule u odnosu na jednu ili više unapred definisanih teorija.

Neke od često korišćenih teorija su:

- **Aritmetika celih brojeva** — sabiranje, oduzimanje i poređenje celih brojeva.
- **Aritmetika realnih brojeva** — operacije i poređenja nad realnim brojevima.
- **Neinterpretirane funkcije** — funkcijski simboli bez unapred zadatog značenja, uz poštovanje jednakosti.
- **Bitvektori** — operacije nad brojevima fiksne širine, uključujući prekoračenje.
- **Nizovi (Arrays)** — čitanje i upisivanje elemenata indeksiranih struktura.

SMT rešavači kombinuju tehnike SAT rešavanja sa posebnim algoritmima za rezonovanje unutar odgovarajućih teorija.

Pojednostavljeno, jedan čest pristup funkcioniše na sledeći način:

1. SAT komponenta razmatra moguće kombinacije istinitosnih vrednosti logičkih uslova.
2. Specijalizovani algoritmi proveravaju da li su te kombinacije saglasne sa pravilima odgovarajuće teorije.
3. Ako kombinacija nije moguća, informacija o konfliktu koristi se za odbacivanje takvih kombinacija.
4. Postupak se nastavlja dok se ne pronađe rešenje ili dokaže da ono ne postoji.

Na primer, razmotrimo formulu:

```text
x > 10 /\ x < 5
```

Ako uslove `x > 10` i `x < 5` posmatramo kao nezavisne iskazne promenljive, njihova konjunkcija može biti zadovoljena dodeljivanjem vrednosti `true` obema promenljivama.

Međutim, SMT rešavač koji poznaje aritmetiku prepoznaje da ne postoji broj `x` koji istovremeno zadovoljava oba uslova.

Zato zaključuje da je formula nezadovoljiva.

Na vežbama ćemo koristiti SMT rešavač **Z3**, koji podržava veliki broj teorija i omogućava ispitivanje zadovoljivosti, pronalaženje modela i dokazivanje svojstava. Može se instalirati jednostavno pomoću menadžera paketa (`sudo apt-get install z3`).

## SMT-LIB 2 format

**SMT-LIB 2** je standardizovani jezik za zapisivanje SMT problema i komunikaciju sa SMT rešavačima.

Slično kao što smo za SAT rešavače koristili DIMACS format, za SMT rešavače koristićemo SMT-LIB 2.

Međutim, SMT-LIB 2 je znatno izražajniji od DIMACS formata. Omogućava nam da definišemo promenljive i funkcije, zapisujemo logičke i aritmetičke izraze, postavljamo ograničenja i tražimo modele.

SMT-LIB 2 koristi sintaksu zasnovanu na S-izrazima, u kojoj se operator navodi pre svojih argumenata.

Na primer, matematički izraz:

```text
x + 2*y > 50
```

u SMT-LIB 2 formatu zapisujemo kao:

```smtlib
(> (+ x (* 2 y)) 50)
```

Operator `>` primenjuje se na dva argumenta: izraz `(+ x (* 2 y))` i konstantu `50`.

Slično tome:

```text
x >= 0
```

zapisujemo kao:

```smtlib
(>= x 0)
```

a konjunkciju dva uslova:

```text
x >= 0 /\ y >= 0
```

zapisujemo kao:

```smtlib
(and (>= x 0) (>= y 0))
```

### Deklarisanje promenljivih

Pre korišćenja promenljive potrebno je da navedemo njen tip.

Za deklarisanje konstanti koristimo komandu `declare-const`.

Na primer:

```smtlib
(declare-const x Int)
(declare-const y Real)
(declare-const p Bool)
```

Ovim definišemo:

- `x` kao promenljivu tipa `Int` (ceo broj).
- `y` kao promenljivu tipa `Real` (realan broj).
- `p` kao promenljivu tipa `Bool` (istinitosna vrednost).

Pored ovih tipova, SMT-LIB 2 podržava i druge tipove, kao što su bitvektori i nizovi.

### Zadavanje ograničenja

Ograničenja zapisujemo pomoću komande `assert`.

Na primer, razmotrimo sledeći sistem:

```text
x + y = 10
x > y
x >= 0
y >= 0
```

U SMT-LIB 2 formatu zapisujemo:

```smtlib
(declare-const x Int)
(declare-const y Int)

(assert (= (+ x y) 10))
(assert (> x y))
(assert (>= x 0))
(assert (>= y 0))
```

Svaka komanda `assert` dodaje novo ograničenje koje mora biti zadovoljeno.

Sva ograničenja dodata na ovaj način posmatraju se kao konjunkcija.

### Provera zadovoljivosti

Za proveru zadovoljivosti koristimo komandu:

```smtlib
(check-sat)
```

SMT rešavač može vratiti jedan od sledećih odgovora:

- `sat` — postoji model koji zadovoljava sva postavljena ograničenja.
- `unsat` — ne postoji model koji zadovoljava sva ograničenja.
- `unknown` — rešavač nije uspeo da utvrdi zadovoljivost.

Ako je formula zadovoljiva, možemo zatražiti model komandom:

```smtlib
(get-value (x y))
```

### Izbor teorije pomoću `set-logic`

U SMT-LIB 2 formatu možemo navesti koju logiku, odnosno kombinaciju teorija, želimo da koristimo. To radimo pomoću komande `set-logic`.

Na primer:

```smtlib
(set-logic QF_LIA)
```

Ova komanda označava da ćemo koristiti **linearnu aritmetiku celih brojeva bez kvantifikatora**.

Neke od često korišćenih logika su:

| Logika | Značenje |
|---|---|
| `QF_UF` | Neinterpretirane funkcije bez kvantifikatora |
| `QF_LIA` | Linearna aritmetika celih brojeva bez kvantifikatora |
| `QF_LRA` | Linearna aritmetika realnih brojeva bez kvantifikatora |
| `QF_NIA` | Nelinearna aritmetika celih brojeva bez kvantifikatora |
| `QF_NRA` | Nelinearna aritmetika realnih brojeva bez kvantifikatora |
| `QF_BV` | Bitvektori bez kvantifikatora |
| `QF_AUFLIA` | Nizovi, neinterpretirane funkcije i linearna aritmetika celih brojeva bez kvantifikatora |
| `LIA` | Linearna aritmetika celih brojeva sa kvantifikatorima |

Prefiks `QF` (*Quantifier-Free*) označava da formule ne sadrže kvantifikatore `forall` i `exists`.

Oznake `LIA` i `LRA` odnose se na linearnu aritmetiku, dok `NIA` i `NRA` dozvoljavaju i nelinearne izraze, kao što je množenje dve promenljive.

Na primer, sledeći program koristi linearnu aritmetiku celih brojeva:

```smtlib
(set-logic QF_LIA)

(declare-const x Int)
(declare-const y Int)

(assert (= (+ (* 2 x) (* 3 y)) 10))
(assert (> x y))

(check-sat)
(get-value (x y))
```

Komanda `set-logic` nije obavezna u Z3, jer rešavač može automatski odabrati odgovarajuće postupke rešavanja. Ipak, njeno korišćenje može pomoći rešavaču da izabere odgovarajuće algoritme.

Važno je da zadate formule pripadaju izabranoj logici. Na primer, ako koristimo `QF_LIA`, ne možemo dodavati kvantifikatore niti nelinearno množenje promenljivih.

### Logički operatori

SMT-LIB 2 koristi sledeće osnovne logičke operatore:

| Operator | Značenje |
|---|---|
| `(not A)` | Negacija |
| `(and A B)` | Konjunkcija |
| `(or A B)` | Disjunkcija |
| `(=> A B)` | Implikacija |
| `(= A B)` | Jednakost |
| `(distinct A B)` | Različitost |

Na primer:

```smtlib
(assert (or (> x 5) (< y 3)))
```

zahteva da važi bar jedan od dva navedena uslova.

### Kvantifikatori

SMT-LIB 2 podržava i kvantifikatore logike prvog reda.

Univerzalni kvantifikator zapisujemo pomoću `forall`, a egzistencijalni pomoću `exists`.

Vratimo se sada našem početnom primeru:

```text
∀x ∈ N ∃y ∈ N (x + y > 50)
```

Pošto SMT-LIB 2 koristi tip `Int` za cele brojeve, uslov da su brojevi prirodni možemo izraziti dodatnim ograničenjima da su nenegativni.

Tada tvrđenje zapisujemo kao:

```smtlib
(assert
    (forall ((x Int))
        (=>
            (>= x 0)
            (exists ((y Int))
                (and
                    (>= y 0)
                    (> (+ x y) 50)
                )
            )
        )
    )
)
```

Formula kaže da za svaki nenegativan ceo broj `x` postoji nenegativan ceo broj `y` takav da je njihov zbir veći od 50.

Međutim, moramo razlikovati **zadovoljivost** od **valjanosti**.

Ako izvršimo:

```smtlib
(check-sat)
```

i dobijemo `sat`, to samo po sebi ne predstavlja dokaz da je formula valjana.

Da bismo dokazali da tvrđenje važi, možemo koristiti dokazivanje pobijanjem, kao na prethodnom času.

Zato postavljamo negaciju tvrđenja:

```smtlib
(assert
    (not
        (forall ((x Int))
            (=>
                (>= x 0)
                (exists ((y Int))
                    (and
                        (>= y 0)
                        (> (+ x y) 50)
                    )
                )
            )
        )
    )
)

(check-sat)
```

Z3 vraća:

```text
unsat
```

To znači da ne postoji kontraprimer za polazno tvrđenje, odnosno da za svaki prirodan broj `x` zaista postoji prirodan broj `y` takav da je `x + y > 50`.

Treba imati na umu da je automatsko rezonovanje sa kvantifikatorima znatno složenije nego rešavanje formula bez kvantifikatora i da SMT rešavači ne garantuju završavanje za sve takve probleme.

### Definisanje funkcija

SMT-LIB 2 omogućava i definisanje funkcija pomoću komande `define-fun`.

Na primer, funkciju koja vraća apsolutnu vrednost celog broja možemo definisati kao:

```smtlib
(define-fun abs_val ((x Int)) Int
    (ite (>= x 0) x (- x))
)
```

Komanda `ite` predstavlja uslovni izraz:

```text
ite(uslov, vrednost_ako_je_tacno, vrednost_ako_je_netacno)
```

Sada možemo koristiti funkciju `abs_val` u ograničenjima:

```smtlib
(declare-const x Int)

(assert (= (abs_val x) 5))

(check-sat)
(get-model)
```

Rešavač može pronaći model u kojem je `x = 5` ili `x = -5`.

## Pokretanje Z3 rešavača

SMT-LIB 2 formule najčešće čuvamo u tekstualnim fajlovima sa ekstenzijom `.smt2`.

Na primer, ako se program nalazi u fajlu `primer.smt2`, Z3 možemo pokrenuti komandom:

```bash
z3 primer.smt2
```

Rešavač izvršava komande redom i ispisuje rezultate provera zadovoljivosti i zahteva za modelima.

U SMT-LIB 2 fajlovima možemo pisati i komentare. Komentar počinje simbolom `;` i traje do kraja reda.

# Rešenja zadataka

## Zadatak 1

Posmatramo neinterpretirane funkcije `f` i `g`. U prevodu, za njih ne zadajemo konkretan način izračunavanja, znamo samo da jednake argumente moraju preslikavati u jednake rezultate. Sve konstante i funkcije rade nad istim, nepraznim domenom `S`.

```smt2
(set-logic UF)
(declare-sort S 0)
(declare-const a S)
(declare-const b S)
(declare-const c S)
(declare-fun f (S) S)
(declare-fun g (S) S)
```

Svaki primer radimo zasebno: odgovarajuća tvrđenja prosleđujemo rešavaču pomoću `assert`, a zatim pozivamo `(check-sat)`.

### a) `a = b`, `f(a) != f(b)`

```smt2
(assert (= a b))
(assert (distinct (f a) (f b)))
(check-sat)
```

Dobijamo `unsat`. Ako `a` i `b` predstavljaju isti objekat, primena iste funkcije mora dati isti rezultat. Prema tome, nije moguće da istovremeno važe `a = b` i `f(a) != f(b)`.

### b) `f(a) = f(b)`, `a != b`

```smt2
(assert (= (f a) (f b)))
(assert (distinct a b))
(check-sat)
```

Dobijamo `sat`. Neinterpretirana funkcija ne mora biti injektivna: različiti argumenti mogu imati istu sliku. Na primer, domen može sadržati dva različita elementa, a funkcija `f` oba može preslikavati u isti element.

### c) `a = b`, `g(f(a)) != g(f(b))`

```smt2
(assert (= a b))
(assert (distinct (g (f a)) (g (f b))))
(check-sat)
```

Dobijamo `unsat`. Iz `a = b` najpre sledi `f(a) = f(b)`, a zatim `g(f(a)) = g(f(b))`. Dakle, jednakost se čuva i pri kompoziciji funkcija.

### d) Ciklus dužine tri

```smt2
(assert (= (f a) b))
(assert (= (f b) c))
(assert (= (f c) a))
(assert (distinct a b c))
(check-sat)
```

Dobijamo `sat`. Uslovi zapravo opisuju ciklus `a -> b -> c -> a`. Dovoljno je konstantama `a`,`b` i `c` dodeliti različite vrednosti iz domena, a zatim interpretirati `f` tako da zadovolji prve 3 jednakosti. 

### e) Injektivnost funkcije

Sada dodatno pretpostavljamo da je `f` injektivna:

```smt2
(assert
    (forall ((x S) (y S))
        (=> (= (f x) (f y)) (= x y))
    )
)
```

Želimo da dokažemo da iz `f(f(a)) = f(f(b))` sledi `a = b`. Kao i kod dokazivanja pobijanjem, dodajemo pretpostavku i negaciju zaključka:

```smt2
(assert (= (f (f a)) (f (f b))))
(assert (distinct a b))
(check-sat)
```

Rešavač vraća `unsat`. Injektivnost prvo primenjujemo na argumente `f(a)` i `f(b)` i dobijamo `f(a) = f(b)`. Ponovnom primenom injektivnosti dobijamo `a = b`, što je u suprotnosti sa dodatim uslovom `a != b`.

## Zadatak 2

Posmatramo linearni sistem:

```text
2x + 3y - z = 7
x - y + 2z >= 7
3x + 2y + z >= 10
0 <= x, y, z <= 10
```

U SMT-LIB-u prvo biramo tip promenljivih. U delu pod a) koristimo `Real`, a od dela pod b) `Int`. Ograničenja zatim zapisujemo direktno pomoću aritmetičkih operatora.

### a) Realna rešenja

```smt2
(set-logic QF_LRA)
(declare-const x Real)
(declare-const y Real)
(declare-const z Real)

(assert (<= 0 x 10))
(assert (<= 0 y 10))
(assert (<= 0 z 10))
(assert (= (+ (* 2 x) (* 3 y) (- z)) 7))
(assert (>= (+ x (- y) (* 2 z)) 7))
(assert (>= (+ (* 3 x) (* 2 y) z) 10))

(check-sat)
(get-value (x y z))
```

Dobijamo `sat`: na primer, `x = 21/5`, `y = 0`, `z = 7/5` zadovoljava sve uslove. 

### b) Celobrojna rešenja

Za celobrojno rešavanje menjamo logiku u `QF_LIA` i deklaracije u `Int`. Ostala ograničenja ostaju ista:

```smt2
(set-logic QF_LIA)
(declare-const x Int)
(declare-const y Int)
(declare-const z Int)
```

I ovde dobijamo `sat`, jer je, na primer, `(5, 0, 3)` celobrojno rešenje sistema.

### c) Dodatno ograničenje zbira

Na početni celobrojni sistem dodajemo:

```smt2
(assert (<= (+ x y z) 6))
(check-sat)
```

Dobijamo `unsat`. Dakle, početni sistem sa celobrojnim promenljivama nema rešenje čiji je zbir najviše 6.

### d) Najmanja vrednost zbira

Za optimizaciju koristimo `minimize`. Nakon svih ograničenja početnog sistema dodajemo:

```smt2
(minimize (+ x y z))
(check-sat)
(get-value (x y z))
(get-objectives)
```

Minimalna vrednost je 8, a postiže se za `x = 5`, `y = 0`, `z = 3`. Analogno, `(maximize (+ x y z))` nalazi najveću vrednost zbira. Za početni celobrojni sistem maksimum je 18. Komande `minimize` i `get-objectives` predstavljaju proširenje koje podržava Z3 i nije zagarantovano standardom da će postojati u svakom SMT rešavaču.

## Zadatak 3

U svako polje sudokua dimenzije `4 x 4` upisujemo ceo broj od 1 do 4. Promenljiva `xij` predstavlja vrednost u redu `i`, koloni `j`.

### a) Pravila sudokua

Deklarišemo 16 celobrojnih promenljivih:

```smt2
(set-logic QF_LIA)
(declare-const x11 Int)
(declare-const x12 Int)
(declare-const x13 Int)
(declare-const x14 Int)
(declare-const x21 Int)
(declare-const x22 Int)
(declare-const x23 Int)
(declare-const x24 Int)
(declare-const x31 Int)
(declare-const x32 Int)
(declare-const x33 Int)
(declare-const x34 Int)
(declare-const x41 Int)
(declare-const x42 Int)
(declare-const x43 Int)
(declare-const x44 Int)
```

Svako polje ima vrednost od 1 do 4. Sledeći uslov zapisujemo za svih 16 polja:

```smt2
(assert (<= 1 x11 4))
; ... isti uslov za x12, x13, ..., x43
(assert (<= 1 x44 4))
```

U svakom redu brojevi su međusobno različiti:

```smt2
(assert (distinct x11 x12 x13 x14))
(assert (distinct x21 x22 x23 x24))
(assert (distinct x31 x32 x33 x34))
(assert (distinct x41 x42 x43 x44))
```

Isto zahtevamo za kolone:

```smt2
(assert (distinct x11 x21 x31 x41))
(assert (distinct x12 x22 x32 x42))
(assert (distinct x13 x23 x33 x43))
(assert (distinct x14 x24 x34 x44))
```

I za četiri bloka dimenzije `2 x 2`:

```smt2
(assert (distinct x11 x12 x21 x22))
(assert (distinct x13 x14 x23 x24))
(assert (distinct x31 x32 x41 x42))
(assert (distinct x33 x34 x43 x44))
```

Operator `distinct` se može primeniti na proizvoljan broj vrednosti, pa pošto četiri različita cela broja biramo iz skupa `{1, 2, 3, 4}`, svaki red, kolona i blok nužno sadrži sva četiri broja.

### b) Zadate vrednosti i rešenje

Dodajemo četiri poznate vrednosti:

```smt2
(assert (= x11 1))
(assert (= x24 2))
(assert (= x32 4))
(assert (= x43 3))
(check-sat)
```

Jedno rešenje je:

```text
1 2 | 4 3
4 3 | 1 2
----+----
3 4 | 2 1
2 1 | 3 4
```

Vrednosti svih polja možemo dobiti komandom `get-value`, kao ranije.

### c) Jedinstvenost rešenja

Da bismo proverili postoji li drugo rešenje, dodajemo uslov da se bar jedno polje razlikuje od pronađene matrice:

```smt2
(assert
    (or
        (distinct x11 1) (distinct x12 2)
        (distinct x13 4) (distinct x14 3)
        (distinct x21 4) (distinct x22 3)
        (distinct x23 1) (distinct x24 2)
        (distinct x31 3) (distinct x32 4)
        (distinct x33 2) (distinct x34 1)
        (distinct x41 2) (distinct x42 1)
        (distinct x43 3) (distinct x44 4)
    )
)
(check-sat)
```

Dobijamo `unsat` što znači da zadati sudoku ima jedinstveno rešenje. 

### d) Zbir glavne dijagonale

Za zahtev da zbir elemenata glavne dijagonale bude 10, dodajemo:

```smt2
(assert (= (+ x11 x22 x33 x44) 10))
(check-sat)
```

Dobijamo `sat`: za jedinstveno rešenje dijagonala sadrži `1, 3, 2, 4`, pa joj je zbir svakako 10.

## Zadatak 4

Funkcija `abs_diff(x, y)` računa apsolutnu razliku dva celobrojna argumenta. Najpre je modelujemo nad matematičkim celim brojevima (`Int`), što odgovara uobičajenom matematičkom značenju apsolutne vrednosti.

### a) Definicija funkcije

```smt2
(set-logic QF_LIA)
(declare-const x Int)
(declare-const y Int)

(define-fun abs_diff ((a Int) (b Int)) Int
    (ite (>= a b) (- a b) (- b a))
)
```

Izraz `ite` predstavlja uslovni izraz: ako je prvi argument tačan, uzima se drugi, a u suprotnom treći. Parametri funkcije su `a` i `b`, pa unutar definicije koristimo njih, a ne spolja deklarisane `x` i `y`.

### b) Nenegativnost

Želimo da dokažemo `abs_diff(x, y) >= 0`. Zato pitamo da li postoji kontraprimer:

```smt2
(assert (< (abs_diff x y) 0))
(check-sat)
```

Dobijamo `unsat`. Kada je `x >= y`, razlika `x - y` je nenegativna; u drugom slučaju nenegativna je `y - x`.

### c) Simetričnost

Tvrdnju `abs_diff(x, y) = abs_diff(y, x)` proveravamo negiranjem:

```smt2
(assert (distinct (abs_diff x y) (abs_diff y x)))
(check-sat)
```

Rezultat je `unsat`, dakle zamena mesta argumenata ne menja apsolutnu razliku.

### d) Nula ako i samo ako su argumenti jednaki

Negiramo ekvivalenciju `(x = y) <=> (abs_diff(x, y) = 0)`:

```smt2
(assert
    (distinct (= x y) (= (abs_diff x y) 0))
)
(check-sat)
```

Rezultat je `unsat`. Operator `distinct` ovde poredi dve logičke vrednosti i traži da budu različite, što je tačno negacija ekvivalencije.

### Napomena

Kada bismo želeli da zaista modelujemo navedenu funkciju zapisanu u programskom jeziku poput jezika C++, trebalo bi da koristimo tip fiksne širine (za razliku od tipa `Int` koji predstavlja skup celih brojeva i besonačan je). U te svrhe možemo koristiti tip bitvektora koji zadajemo sa `(_ BitVec širina)`, pri čemu je odgovarajuća logika `QF_BV`. Standardne operacije i relacije nad brojevima imaju svoje pandane nad bitvektorima:

- `+` - `bvadd`
- `-` - `bvsub`
- `*` - `bvmul`
- `/` - `bvdiv`
- `<` - `bvslt/bvult` (označeno i neoznačeno poređenje)
- `<=` - `bvsle/bvule`
- `>` - `bvsgt/bvugt`
- `>=` - `bvsge/bvuge`

Modifikovano rešenje postaje:

```smt2
(set-logic QF_BV)
(declare-const x (_ BitVec 32))
(declare-const y (_ BitVec 32))

(define-fun abs_diff ((a (_ BitVec 32)) (b (_ BitVec 32))) (_ BitVec 32)
    (ite (bvsge a b) (bvsub a b) (bvsub b a))
)

 (assert (bvslt (abs_diff x y) (_ bv0 32)))
; (assert (distinct (abs_diff x y) (abs_diff y x)))
; (assert (distinct (= x y) (= (abs_diff x y) 0)))

```

Sa ovom ispravkom simetričnost i svojstvo da je rezultat nula tačno kada su argumenti jednaki ostaju tačni, ali nenegativnost u označenom 32-bitnom smislu ne važi uvek. O uzroku više u sledećem zadatku. 

## Zadatak 5

U ovom zadatku koristimo osmobitne **neoznačene** brojeve. Vrednosti pripadaju skupu `{0, ..., 255}`, a sabiranje se računa modulo 256. Zato koristimo teoriju bitvektora.

### a) Definicija funkcije `is_greater`

```smt2
(set-logic QF_BV)
(declare-const x (_ BitVec 8))
(declare-const y (_ BitVec 8))

(define-fun is_greater ((a (_ BitVec 8)) (b (_ BitVec 8))) Bool
    (bvuge (bvadd a b) a)
)
```

### b) Da li funkcija uvek vraća `true`?

Tražimo ulaz za koji funkcija vraća `false`:

```smt2
(assert (not (is_greater x y)))
(check-sat)
(get-value (x y))
```

Dobijamo `sat`. Jedan kontraprimer je `x = 255`, `y = 1`. Zbir matematički iznosi 256, ali u osmobitnoj aritmetici postaje 0, pa proveravamo `0 >= 255`, što je netačno.

### c) Detekcija prekoračenja

Prekoračenje pri neoznačenom sabiranju nastaje kada matematički zbir pređe 255. To možemo prepoznati uslovom `y > 255 - x`:

```smt2
(define-fun overflow ((a (_ BitVec 8)) (b (_ BitVec 8))) Bool
    (bvult (bvsub (_ bv255 8) a) b)
)
```

Kako bismo dokazali da ako je došlo do prekoračenja, `is_greater` vraća `false`**, i obratno, zadajemo uslov:

```smt2
(assert
    (=
        (overflow x y)
        (is_greater x y)
    )
)
(check-sat)
```
Dobijamo `unsat`. Dakle, važi tvrđenje: `is_greater` vraća `false` **ako i samo ako** nastane prekoračenje. 

## Zadatak 6

Funkcija `sum(n)` računa zbir `1 + 2 + ... + n` za `n >= 0`. Želimo da za ulaze `0 <= n <= 5` proverimo tvrđenje:

```text
sum(n) = n * (n + 1) / 2
```

Petlju modelujemo **razvijanjem (unrolling)**: za svaku iteraciju uvodimo posebne promenljive `i0, i1, ...` i `s0, s1, ...`, koje opisuju vrednosti brojača i zbira posle određenog broja koraka.

### a) Početno stanje i prelazna relacija

Početno stanje je `i0 = 0`, `s0 = 0`, a granice ulaza su `0 <= n <= 5`:

```smt2
(set-logic QF_NIA)
(declare-const n Int)
(declare-const i0 Int)
(declare-const s0 Int)
(assert (= i0 0))
(assert (= s0 0))
(assert (<= 0 n 5))
```

Jednu iteraciju opisujemo pomoću dve funkcije:

```smt2
(define-fun next_i ((i Int)) Int
    (ite (< i n) (+ i 1) i)
)

(define-fun next_s ((i Int) (s Int)) Int
    (ite (< i n) (+ s i 1) s)
)
```

Ako je `i < n`, petlja povećava `i` za jedan i dodaje novu vrednost brojača u zbir. Ako uslov nije ispunjen, stanje ostaje nepromenjeno. Zadržavanje stanja nakon završetka petlje omogućava da modelujemo isti broj koraka za različite vrednosti `n`.

### b) Provera razvijene petlje

U zadatku je dozvoljeno najviše pet iteracija. Dakle, potrebne su nam promenljive `i1`, ..., `i5` i `s1`, ..., `s5` koje će predstavljati vrednosti originalnih promenljivih `i` i `s` kroz iteracije:

```smt2
(declare-const i1 Int)
(declare-const i2 Int)
(declare-const i3 Int)
(declare-const i4 Int)
(declare-const i5 Int)
(declare-const s1 Int)
(declare-const s2 Int)
(declare-const s3 Int)
(declare-const s4 Int)
(declare-const s5 Int)

(assert (= i1 (next_i i0)))
(assert (= i2 (next_i i1)))
(assert (= i3 (next_i i2)))
(assert (= i4 (next_i i3)))
(assert (= i5 (next_i i4)))

(assert (= s1 (next_s i0 s0)))
(assert (= s2 (next_s i1 s1)))
(assert (= s3 (next_s i2 s2)))
(assert (= s4 (next_s i3 s3)))
(assert (= s5 (next_s i4 s4)))
```

Pošto je `n <= 5`, u stanju `(i5, s5)` petlja je sigurno završena. Željenu jednakost proveravamo pobijanjem, odnosno tražimo ulaz za koji ona ne važi:

```smt2
(assert (distinct (* 2 s5) (* n (+ n 1))))
(check-sat)
```

Dobijamo `unsat`, odnosno ni za jedan `n` od 0 do 5 rezultat ne odstupa od formule `n(n + 1)/2`. Umesto deljenja sa 2 koristimo ekvivalentnu jednakost `2 * s5 = n * (n + 1)`, što izbegava potrebu za operacijom celobrojnog deljenja. Potrebno je uključiti logiku `QF_NIA`, pošto ograničenja nisu više isključivo linearna (`n * (n + 1)`).

**Ograničenje ovog dokaza:** rezultat potvrđuje svojstvo samo za zadati konačan skup ulaza `0 <= n <= 5`. Ne predstavlja dokaz za sve nenegativne cele brojeve. Za opšti dokaz možemo koristiti, na primer, invarijantu petlje `2*s = i*(i+1)` i matematičku indukciju.


