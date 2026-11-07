# Uvod u CSP i MiniZinc

Na prethodnim časovima upoznali smo se sa SAT i SMT rešavačima, koji nam omogućavaju da ispitujemo zadovoljivost logičkih formula. Iako pomoću njih možemo modelovati veliki broj problema, zapisivanje složenijih ograničenja često zahteva uvođenje velikog broja promenljivih i formula.

Osnovna prednost CSP modelovanja je izražajnost jezika za zadavanje ograničenja. Umesto da složene uslove ručno razlažemo na jednostavnije formule, možemo koristiti gotova ograničenja koja direktno izražavaju strukturu problema.

Pored jednostavnijeg modelovanja, mnoga globalna ograničenja imaju specijalizovane algoritme za efikasno zaključivanje tokom rešavanja, pa je i rešavanje problema često brže nego kod SAT ili SMT rešavača.

## CSP problemi

**CSP (Constraint Satisfaction Problem)** je problem zadovoljavanja ograničenja i sastoji se od tri osnovne komponente:

- **Promenljive** — objekti kojima želimo da dodelimo vrednosti.
- **Domeni** — skupovi dozvoljenih vrednosti promenljivih.
- **Ograničenja** — uslovi koje dodeljene vrednosti moraju da zadovolje.

Rešenje CSP problema predstavlja dodelu vrednosti svim promenljivama tako da su sva ograničenja zadovoljena.

Na primer, posmatrajmo tri celobrojne promenljive:

```text
x, y, z ∈ {1, 2, 3}
```

sa ograničenjima:

```text
x != y
y != z
x != z
x < y
```

Jedno rešenje je:

```text
x = 1
y = 2
z = 3
```

Pored problema zadovoljavanja ograničenja, često razmatramo i **probleme optimizacije**, kod kojih želimo da pronađemo rešenje koje minimizuje ili maksimizuje neku funkciju cilja.

Na primer, možemo tražiti dodelu koja zadovoljava sva prethodna ograničenja i minimizuje zbir `x + y + z`.

CSP rešavači koriste različite tehnike za pronalaženje rešenja, među kojima su pretraga sa vraćanjem (*backtracking*) i propagacija ograničenja (*constraint propagation*).

Propagacija podrazumeva uklanjanje vrednosti iz domena promenljivih za koje se može zaključiti da ne mogu učestvovati u rešenju.

## MiniZinc

**MiniZinc** je deklarativni jezik za modelovanje problema zadovoljavanja ograničenja i optimizacije.

Deklarativni pristup podrazumeva da opisujemo **šta rešenje mora da zadovolji**, umesto da navodimo algoritam kojim se do rešenja dolazi.

MiniZinc omogućava da definišemo promenljive, njihove domene, ograničenja i funkciju cilja, dok se pronalaženje rešenja prepušta odgovarajućem rešavaču.

Važno je napomenuti da MiniZinc nije sam po sebi CSP rešavač, već jezik za modelovanje koji podržava različite rešavače.

MiniZinc modele najčešće čuvamo u fajlovima sa ekstenzijom `.mzn`.

### Deklarisanje promenljivih

Promenljive u MiniZinc-u definišemo navođenjem domena i imena promenljive.

Na primer:

```minizinc
var 1..10: x;
var bool: p;
var 0.0..1.0: y;
```

Ovim definišemo:

- `x` — celobrojnu promenljivu čiji je domen `{1, ..., 10}`.
- `p` — logičku promenljivu.
- `y` — realnu promenljivu iz intervala `[0, 1]`.

Ključna reč `var` označava promenljivu čiju vrednost treba da odredi rešavač.

Pored promenljivih, možemo definisati i parametre čije su vrednosti unapred poznate:

```minizinc
int: n = 5;
```

### Nizovi

MiniZinc podržava nizove, što je posebno korisno prilikom modelovanja CSP problema.

Na primer:

```minizinc
int: n = 5;
array[1..n] of var 1..10: x;
```

Ovim definišemo niz od pet promenljivih, pri čemu svaka može imati vrednost između 1 i 10.

Možemo koristiti i višedimenzionalne nizove:

```minizinc
array[1..4, 1..4] of var 1..4: x;
```

### Zadavanje ograničenja

Ograničenja definišemo pomoću ključne reči `constraint`.

Na primer:

```minizinc
var 1..10: x;
var 1..10: y;

constraint x + y = 10;
constraint x < y;

solve satisfy;
```

Komanda `solve satisfy` označava da želimo da pronađemo bilo koju dodelu vrednosti koja zadovoljava sva ograničenja.

Za modelovanje složenijih uslova možemo koristiti logičke operatore:

| Operator |   Značenje    |
|----------|---------------|
| `/\`     | Konjunkcija   |
| `\/`     | Disjunkcija   |
| `not`    | Negacija      |
| `->`     | Implikacija   |
| `<->`    | Ekvivalencija |
| `!=`     | Različitost   |

Na primer:

```minizinc
constraint (x > 5) -> (y < 3);
```

Ovim zahtevamo da, ako je `x > 5`, mora važiti i `y < 3`.

### Kvantifikatori i agregatne funkcije

MiniZinc podržava izraze kojima možemo jednostavno zadavati ograničenja nad većim brojem promenljivih.

Na primer, ako želimo da svi elementi niza `x` budu pozitivni, možemo zapisati:

```minizinc
constraint forall(i in 1..n)(x[i] > 0);
```

Ako želimo da bar jedan element niza bude jednak 5:

```minizinc
constraint exists(i in 1..n)(x[i] = 5);
```

Za računanje zbira elemenata koristimo funkciju `sum`:

```minizinc
constraint sum(i in 1..n)(x[i]) = 20;
```

Slične funkcije postoje i za minimum, maksimum i druge operacije.

### Globalna ograničenja

Jedna od najvažnijih mogućnosti MiniZinc-a jeste korišćenje **globalnih ograničenja**.

Globalna ograničenja omogućavaju da jednim izrazom zadamo složene odnose između većeg broja promenljivih.

Na primer, ograničenje:

```minizinc
include "globals.mzn";

array[1..5] of var 1..5: x;

constraint all_different(x);
```

zahteva da svi elementi niza imaju različite vrednosti.

Bez globalnog ograničenja, isti uslov mogli bismo zapisati kao:

```minizinc
constraint forall(i, j in 1..5 where i < j)(
    x[i] != x[j]
);
```

Iako su ova dva zapisa logički ekvivalentna, globalno ograničenje je jednostavnije za zapisivanje, a neki rešavači za njega koriste specijalizovane algoritme propagacije.

### Problemi optimizacije

Pored pronalaženja bilo kog rešenja, MiniZinc podržava minimizaciju i maksimizaciju funkcije cilja.

Na primer:

```minizinc
var 1..10: x;
var 1..10: y;

constraint x + y >= 12;

solve minimize x + 2*y;
```

U ovom primeru tražimo vrednosti `x` i `y` koje zadovoljavaju ograničenje, a pritom minimizuju izraz `x + 2*y`.

Za maksimizaciju koristimo:

```minizinc
solve maximize x + 2*y;
```

Svaki MiniZinc model treba da sadrži jednu naredbu `solve`, koja može biti oblika `satisfy`, `minimize` ili `maximize`.

### Ispis rešenja

MiniZinc omogućava definisanje formata u kome će pronađeno rešenje biti prikazano.

Za to koristimo komandu `output`.

Na primer:

```minizinc
output [
    "x = ", show(x), "\n",
    "y = ", show(y), "\n"
];
```

Funkcija `show` pretvara vrednost promenljive u tekstualni oblik.

## MiniZinc IDE

**MiniZinc IDE** je razvojno okruženje koje omogućava pisanje, pokretanje i testiranje MiniZinc modela.

MiniZinc se može preuzeti sa zvaničnog sajta:

https://www.minizinc.org/

Standardna distribucija uključuje MiniZinc IDE, kompajler i nekoliko konfigurisanih rešavača.

U okviru MiniZinc IDE-a možemo:

- Pisati i uređivati `.mzn` modele.
- Birati rešavač koji će se koristiti.
- Pokretati modele i pregledati pronađena rešenja.
- Pronaći sva rešenja problema.
- Postaviti vremensko ograničenje rešavanja.
- Pregledati statistike izvršavanja...

### Pokretanje modela

Nakon otvaranja `.mzn` fajla u MiniZinc IDE-u, iz padajućeg menija biramo rešavač koji želimo da koristimo. Na vežbama ćemo prvenstveno koristiti **Gecode**.

Model pokrećemo klikom na dugme **Run** ili prečicom `Ctrl + R`.

U donjem delu okruženja prikazuju se pronađena rešenja i informacije o izvršavanju.

Podrazumevano, kod problema zadovoljavanja ograničenja MiniZinc prikazuje prvo pronađeno rešenje. Ako želimo da pronađemo sva rešenja, u panelu `Show configuration editor` možemo izabrati `user-defined behavior` i ostaviti polje `stop afer this many solutions` neoznačeno.

Ako želimo da vidimo statistike o rešavanju kao što je ukupan broj rešenja, možemo u istom panelu označiti opciju `Output solver statistics`.

### MiniZinc iz komandne linije

Pored korišćenja IDE-a, MiniZinc modele možemo pokretati i iz terminala.

Na primer:

```bash
minizinc model.mzn
```

Za izbor konkretnog rešavača koristimo opciju `--solver`:

```bash
minizinc --solver gecode model.mzn
```

Ako želimo da pronađemo sva rešenja:

```bash
minizinc --solver gecode -a model.mzn
```

Listu dostupnih rešavača možemo dobiti komandom:

```bash
minizinc --solvers
```

# Rešenja zadataka

## Zadatak 1

Neka su `p`, `g` i `k` brojevi glasova koje su dobili Petao, Gavran i Kukavica. Pošto je svaki sudija glasao za tačno jednog takmičara, ukupan broj glasova je `p + g + k`. Svi brojevi glasova su pozitivni celi brojevi.

Detlićevi podaci ne moraju biti tačni, ali se svaki razlikuje od stvarne vrednosti za najviše 15. Zato uslove zapisujemo kao ograničenja nad apsolutnim razlikama:

```minizinc
int: U = 76;

var 1..U: p;
var 1..U: g;
var 1..U: k;
var 46..U: ukupno = p + g + k;

constraint abs(ukupno - 61) <= 15;
constraint abs(p + g - 16) <= 15;
constraint abs(g + k - 18) <= 15;
constraint abs(p + k - 20) <= 15;

solve satisfy;

output ["Petao: ", show(p), "\nGavran: ", show(g),
        "\nKukavica: ", show(k), "\nUkupno: ", show(ukupno)];
```

Gornja granica `U = 76` dobijena je iz podatka o ukupnom broju glasova: `61 + 15 = 76`. Donja granica je `61 - 15 = 46`. Pošto svaki takmičar dobija bar jedan glas, za pojedinačne brojeve glasova postavljamo donju granicu `1`.

### a) Jedan mogući rezultat

Komanda `solve satisfy` traži bilo koju dodelu promenljivih koja zadovoljava sva ograničenja. Na primer, jedno ispravno rešenje je `p = 13`, `g = 11`, `k = 22`, odnosno ukupno `46` glasova. Nije nužno da će rešavač da vrati baš to rešenje.

### b) Svi mogući rezultati

Za nabrajanje svih rešenja ne menjamo ograničenja, već pokrećemo rešavanje ponovo nakon izbora opcije za prikaz svih rešenja u panelu `Show configuration editor`. Za dati model postoji 70 mogućih trojki `(p, g, k)`.

### c) Jednak broj glasova

U postojeći model dodajemo:

```minizinc
constraint p = g /\ g = k;
```

Dobijamo `UNSATISFIABLE`. To možemo videti i bez rešavača. Ako je `p = g = k = t`, onda iz uslova za ukupno glasova sledi `3t >= 46`, pa je `t >= 16`. Međutim, iz `abs(p + g - 16) <= 15` sledi `2t <= 31`, pa je `t <= 15` i dolazimo do kontradikcije.

### d) Najmanji i najveći ukupan broj glasova

Umesto `solve satisfy` koristimo jednu od sledeće dve naredbe:

```minizinc
solve minimize ukupno;
```

ili

```minizinc
solve maximize ukupno;
```

Najmanji mogući ukupan broj glasova je 46, a najveći 49. Iako iz Detlićeve procene ukupnog broja glasova na prvi pogled dopuštamo vrednosti do 76, ograničenja za parove daju znatno strožu granicu. Sabiranjem gornjih granica `p + g <= 31`, `g + k <= 33` i `p + k <= 35` dobijamo `2(p + g + k) <= 99`, pa je ukupan broj glasova najviše 49.

## Zadatak 2

Za šahovsku tablu `n × n` uvodimo niz `q` od `n` promenljivih:

```minizinc
include "data.dzn";
array[1..n] of var 1..n: q;
```

Vrednost `q[i]` predstavlja kolonu u kojoj se nalazi kraljica u redu `i`. Time smo već obezbedili da u svakom redu postoji tačno jedna kraljica. Preostaje da zabranimo napade po kolonama i dijagonalama.

### a) Model bez globalnih ograničenja

Za svaki par redova `i < j` zahtevamo da kraljice nisu u istoj koloni, kao ni na istoj dijagonali:

```minizinc
constraint forall(i, j in 1..n where i < j)(
    q[i] != q[j] /\ abs(q[i] - q[j]) != abs(i - j)
);

solve satisfy;
```

### b) Model pomoću `all_different`

Umesto da pojedinačno upoređujemo sve parove, možemo koristiti globalno ograničenje `all_different`:

```minizinc
include "globals.mzn";
include "data.dzn";

array[1..n] of var 1..n: q;

constraint all_different(q);
constraint all_different([q[i] - i | i in 1..n]);
constraint all_different([q[i] + i | i in 1..n]);

solve satisfy;
```

Prvi poziv obezbeđuje da su kolone različite. Dve kraljice leže na dijagonali jednog smera kada imaju istu vrednost `q[i] - i`, a na dijagonali drugog smera kada imaju istu vrednost `q[i] + i`. Zato i te vrednosti moraju biti međusobno različite.

### c) Rešenja za `n = 8`

U datoteci `data.dzn` postavljamo:

```minizinc
n = 8;
```

Za pronalaženje jednog rešenja pokrećemo model uobičajeno, a za nabrajanje svih rešenja ponovo je potrebno selektovati odgovarajuću opciju pre pokretanja. Za `n = 8` postoji 92 rešenja ako se rotacije i preslikavanja tabli računaju kao različita rešenja. Na primer, niz `[1, 5, 8, 6, 3, 7, 2, 4]` predstavlja jedno ispravno postavljanje osam kraljica.

### d) Poređenje vremena rešavanja

Ako promenimo vrednost parametra `n` na 32 i ponovo pokrenemo rešavanje za oba modela, možemo primetiti da za pronalaženje jednog rešenja modelu koji koristi `all_different` treba manje od sekund, dok drugom modelu treba oko 10 sekundi. Ova razlika bi nastavila da raste ukoliko bismo parametar `n` dodatno povećavali.

Razlog leži u tome što za globalna ograničenja često postoje pametni algoritmi propagacije (filtriranja domena pri pretrazi) koji često modele koji ih koriste čine znatno efikasnijim.

## Zadatak 3

Magični kvadrat predstavljamo matricom `x` dimenzije `4 × 4`, čiji elementi uzimaju vrednosti od 1 do 16:

```minizinc
include "globals.mzn";

int: n = 4;
array[1..n, 1..n] of var 1..n*n: x;

constraint all_different(x);
constraint forall(i in 1..n)(sum(j in 1..n)(x[i, j]) = 34);
constraint forall(j in 1..n)(sum(i in 1..n)(x[i, j]) = 34);
constraint sum(i in 1..n)(x[i, i]) = 34;
constraint sum(i in 1..n)(x[i, n-i+1]) = 34;

solve satisfy;
```

Ograničenje `all_different(x)` obezbeđuje da se svaki broj od 1 do 16 pojavljuje tačno jednom. Dva uslova sa `forall` nameću zbir 34 u svakom redu i svakoj koloni, dok poslednja dva uslova regulišu glavnu i sporednu dijagonalu.

### a) Dopunjavanje zadatog kvadrata

Da bismo rešili delimično popunjeni kvadrat, dodajemo:

```minizinc
constraint x[1,2] = 12 /\ 
           x[2,2] = 8 /\ 
           x[2,3] = 15 /\
           x[3,1] = 7 /\
           x[3,3] = 2 /\
           x[4,1] = 4 /\
           x[4,4] = 11;
```

Dobijamo sledeće rešenje:

```text
13  12   3   6
10   8  15   1
 7   9   2  16
 4   5  14  11
```

### b) Jedinstvenost rešenja

Da bismo proverili jedinstvenost, dovoljno je u konfiguracionom panelu dozvoliti pronalaženje barem 2 rešenja. Ispostavlja se da je za date brojeve rešenje jedinstveno.

### c) Brojanje rešenja i razbijanje simetrija

Ako uklonimo početne brojeve, dobijamo problem pronalaženja svih normalnih magičnih kvadrata dimenzije `4 × 4`. Takvih kvadrata ima 7040.

Mnogi se međusobno razlikuju samo po rotaciji ili preslikavanju. Da bismo iz svake grupe simetričnih kvadrata izabrali jednog predstavnika, dodajemo ograničenja:

```minizinc
constraint x[1,1] < x[1,n] /\
           x[1,1] < x[n,1] /\
           x[1,1] < x[n,n] /\
           x[1,n] < x[n,1];
```

Prva tri uslova zahtevaju da najmanja vrednost među četiri ugla bude u gornjem levom uglu. Na taj način rotacije kvadrata za 0, 90, 180 i 270 stepeni svodimo na jedno rešenje. Dakle, broj rešenja se smanjuje 4 puta. Poslednji uslov razrešava preostalu simetriju preslikavanja u odnosu na glavnu dijagonalu, što prepolovljava broj rešenja. Ukupan broj rešenja se smanjuje na 880.

## Zadatak 4

Golombov lenjir sa `k` oznaka predstavljamo rastućim nizom pozicija `x`. Zahtevamo da prva oznaka bude na poziciji 0 i da su sve udaljenosti između različitih parova oznaka međusobno različite.

### a) Lenjir zadate dužine

Ako su zadati i broj oznaka `k` i dužina `n`, koristimo sledeći model:

```minizinc
include "globals.mzn";

int: k = 4;
int: n = 6;
array[1..k] of var 0..n: x;

constraint x[1] = 0;
constraint x[k] = n;
constraint forall(i in 1..k-1)(x[i] < x[i+1]);
constraint all_different([x[j] - x[i] |
                          i, j in 1..k where i < j]);

solve satisfy;
```

Izraz u uglastim zagradama formira sve razlike `x[j] - x[i]` za `i < j`, a `all_different` zahteva da se nijedna udaljenost ne ponavlja.

Za `k = 4` i `n = 6` model je zadovoljiv: primer lenjira je `[0, 1, 4, 6]`. Za `k = 4` i `n = 5` dobijamo `UNSATISFIABLE`.

### b) Najkraći lenjir

Ukoliko želimo da problem preformulišemo kao optimizacioni, potrebno je da odredimo gornju granicu za dužinu lenjira, a zatim pokušamo da je minimizujemo:

```minizinc
include "globals.mzn";

int: k = 5;
int: u = 2^(k-1) - 1;

array[1..k] of var 0..u: x;

constraint x[1] = 0;
constraint all_different([x[j] - x[i] |
                          i, j in 1..k where i < j]);
constraint forall(i in 1..k-1)(x[i] < x[i+1]);

solve minimize x[k];
```

Pošto je `x[1] = 0`, dužina lenjira `x[k] - x[1]` jednaka je `x[k]`. Zato minimizujemo `x[k]`.

Gornja granica `u = 2^(k-1) - 1` je bezbedna jer postoji jednostavna konstrukcija lenjira sa oznakama `0, 1, 3, 7, ..., 2^(k-1)-1`, u kojoj su sve pozitivne razlike različite (što se može dokazati indukcijom po k). Dakle, optimalni lenjir sigurno nije duži od `u`.

Za `k = 4` optimalna dužina je 6; za `k = 5` optimalna dužina je 11. Primeri optimalnih lenjira su `[0, 1, 4, 6]` i `[0, 1, 4, 9, 11]`.

## Zadatak 5

U Langfordovom problemu treba rasporediti dva pojavljivanja svakog broja od `1` do `n` tako da su pojavljivanja broja `i` na rastojanju `i`. Umesto da direktno definišemo konačni niz, modelujemo pozicije dva pojavljivanja svakog broja.

Za broj `i`, promenljive `first[i]` i `second[i]` predstavljaju poziciju prvog i drugog pojavljivanja:

```minizinc
include "globals.mzn";

int: n = 4;
array[1..n] of var 1..2*n: first;
array[1..n] of var 1..2*n: second;

constraint all_different(first ++ second);
constraint forall(i in 1..n)(second[i] - first[i] = i + 1);

solve satisfy;
```

Izraz `first ++ second` spaja oba niza pozicija. Zahtev `all_different` osigurava da se nijedna pozicija ne koristi dvaput. Razlika između pozicija dva pojavljivanja broja `i` mora biti `i + 1`, tako da se između njih nalazi tačno `i` drugih elemenata.

### a) Modelovanje

Gornji model obuhvata sve uslove. Pošto je svih `2n` pozicija međusobno različito i svaka pripada intervalu `1..2n`, sve pozicije će biti iskorišćene tačno jednom.

### b) Prikaz niza za `n = 4`

Promenljive modela predstavljaju pozicije, a ne same elemente rezultujućeg niza. Zato za svaku poziciju `pos` tražimo koji broj `v` je na njoj:

```minizinc
output [
  show(sum(v in 1..n)(
    v * bool2int(first[v] = pos \/ second[v] = pos)
  )) ++ " "
  | pos in 1..2*n
];
```

### c) Provera drugih vrednosti `n`

Menjamo samo vrednost parametra `n` i ponovo pokrećemo rešavač. Za `n = 3` rešenje postoji, za `n = 5` ne postoji, a za `n = 7` postoji. 

Opštije, Langfordov raspored postoji upravo kada je `n` oblika `4m` ili `4m + 3` za neki nenegativan ceo broj `m` (uz uobičajeno `n >= 1`).

## Zadatak 6

Problem pakovanja u torbe ("Bin packing") zahteva da svakom predmetu dodelimo jednu torbu i da ukupan zbir veličina u torbi ne pređe kapacitet.

U postavci su veličine predmeta:

```minizinc
int: n = 10;
int: cap = 10;
array[1..n] of int: sizes = [4, 8, 1, 4, 2, 1, 10, 3, 5, 2];
```


### a) Model bez globalnog ograničenja

Uvodimo promenljive `bins[i]`, koje predstavljaju broj torbe u kojoj je predmet `i`. Pošto imamo `n` predmeta, `n` torbi je svakako dovoljno, pa vrednosti ograničavamo na `1..n`.

```minizinc
array[1..n] of var 1..n: bins;

constraint forall(b in 1..n)(
    sum(i in 1..n)(sizes[i] * bool2int(bins[i] = b)) <= cap
);

solve minimize sum(b in 1..n)(
    bool2int(exists(i in 1..n)(bins[i] = b))
);
```

Za svaku torbu `b` sabiramo veličine svih predmeta za koje je `bins[i] = b`. Izraz `bool2int` pretvara logički uslov u 0 ili 1. U ciljnoj funkciji brojimo koliko torbi sadrži bar jedan predmet.

Ukupna veličina svih predmeta je `40`, pa su potrebne najmanje četiri torbe kapaciteta 10. Četiri torbe su i dovoljne, na primer:

```text
Torba 1: predmet 7                 (10)
Torba 2: predmeti 2, 5             (8 + 2 = 10)
Torba 3: predmeti 9, 1, 3          (5 + 4 + 1 = 10)
Torba 4: predmeti 4, 8, 10, 6      (4 + 3 + 2 + 1 = 10)
```

Dakle, minimalan broj torbi je 4.

### b) Predmeti 2 i 4 u istoj torbi

Dodajemo:

```minizinc
constraint bins[2] = bins[4];
```

Sa veličinama iz postavke predmet 2 ima veličinu 8, a predmet 4 veličinu 4. Zajedno zauzimaju `8 + 4 = 12`, što premašuje kapacitet 10. Zato dodatni uslov čini problem nezadovoljivim, bez obzira na broj raspoloživih torbi.

### c) Model pomoću `bin_packing_load`

Problem se može još jednostavnije modelovati korišćenjem globalnog ograničenja `bin_packing_load`:

```minizinc
include "globals.mzn";

int: n = 10;
int: cap = 10;
array[1..n] of int: sizes = [4, 8, 1, 4, 2, 1, 10, 3, 5, 2];
array[1..n] of var 1..n: bins;
array[1..n] of var 0..cap: load;

constraint bin_packing_load(load, bins, sizes);

solve minimize sum(b in 1..n)(bool2int(load[b] > 0));
```

`load[b]` predstavlja ukupnu veličinu predmeta raspoređenih u torbu `b`. Ograničenje `bin_packing_load` usklađuje niz dodeljenih torbi, veličine predmeta i opterećenja torbi. Domen `0..cap` ograničava zauzeće svake torbe. Pošto je `load[b] > 0` tačno upravo za neprazne torbe (sve veličine su pozitivne), ciljna funkcija minimizuje broj upotrebljenih torbi.

## Zadatak 7

U problemu društvenih golfera imamo `16` igrača, `4` grupe od po `4` igrača i `w` nedelja. Potrebno je napraviti raspored tako da svaki igrač svake nedelje pripada jednoj grupi, a nijedan par igrača ne bude zajedno više od jednom.

### a) Model za `w` nedelja

Uvodimo matricu `grp`, gde `grp[t,p]` predstavlja broj grupe u koju je igrač `p` raspoređen u nedelji `t`:

```minizinc
int: w = 2;
int: players = 16;
int: groups = 4;
int: group_size = 4;

array[1..w, 1..players] of var 1..groups: grp;

constraint forall(t in 1..w, g in 1..groups)(
    sum(p in 1..players)(bool2int(grp[t,p] = g)) = group_size
);

constraint forall(p, q in 1..players where p < q)(
    sum(t in 1..w)(bool2int(grp[t,p] = grp[t,q])) <= 1
);

solve satisfy;
```

Prvi `forall` garantuje da svaka grupa u svakoj nedelji sadrži tačno četiri igrača. Svaki igrač u datoj nedelji ima jednu vrednost `grp[t,p]`, pa automatski pripada tačno jednoj grupi.

Drugi `forall` prolazi kroz sve neuređene parove igrača. Za dati par prebrojava nedelje u kojima igrači pripadaju istoj grupi i zahteva da taj broj bude najviše 1.

### b) Rasporedi za `w = 2` i `w = 5`

Za `w = 2` moguće je, na primer, koristiti sledeći raspored:

```text
Nedelja 1:
  Grupa 1:  1  2  3  4
  Grupa 2:  5  6  7  8
  Grupa 3:  9 10 11 12
  Grupa 4: 13 14 15 16

Nedelja 2:
  Grupa 1:  1  5  9 13
  Grupa 2:  2  6 10 14
  Grupa 3:  3  7 11 15
  Grupa 4:  4  8 12 16
```

Ni u jednom paru grupa iz različitih nedelja nema više od jednog zajedničkog igrača, pa se nijedan par igrača ne susreće dvaput.

Za `w = 5` takođe postoji rešenje. Štaviše, pet nedelja je najveći mogući broj: svaki igrač se u jednoj nedelji susretne sa tri druga igrača, a ukupno ima samo 15 drugih igrača. Zbog toga `3w <= 15`, odnosno `w <= 5`. 

### c) Razbijanje simetrija

Mnoga rešenja problema se suštinski ne razlikuju: možemo preimenovati grupe unutar iste nedelje ili preimenovati igrače, a da se svojstvo rasporeda ne promeni.

Ukoliko želimo da smanjimo broj ekvivalentnih rešenja, možemo dodati ograničenja za razbijanje simetrija:

```minizinc
constraint forall(p in 1..players)(
    grp[1,p] = (p-1) div group_size + 1
);

constraint forall(t in 2..w)(grp[t,1] = 1);
```

Prvo ograničenje fiksira raspored u prvoj nedelji: igrači 1–4 su u grupi 1, 5–8 u grupi 2 itd. Ovo je dozvoljeno jer igrače možemo preimenovati bez promene suštine problema. Drugo ograničenje zahteva da igrač 1 u svakoj narednoj nedelji pripada grupi označenoj brojem 1. Ovo je dozvoljeno jer su oznake grupa proizvoljne.