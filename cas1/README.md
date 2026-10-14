# Uvod u iskaznu logiku i SAT modelovanje

Iskazna logika bavi se proučavanjem iskaza i formula nad njima. Iskaze označavamo iskaznim promenljivama, na primer `p`, `q`, `r`.

Primeri iskaza:

- `p`: Nebo je plavo.
- `q`: Temperatura je 23.4 stepena Celizijusa.
- `r`: Zemlja je ravna.

Pored iskaza, u formulama iskazne logike figurišu i logičke konstante `T` (tačno) i `F` (netačno). Takođe, u iskaznim formulama koristimo veznike:

- unarni veznik `~` (negacija)
- binarne veznike `/\` (konjunkcija), `\/` (disjunkcija), `=>` (implikacija) i `<=>` (ekvivalencija)

## Iskazne formule

Iskazne formule gradimo rekurzivno, na sledeći način:

- iskazna promenljiva `p` je iskazna formula
- logička konstanta (`T` ili `F`) je iskazna formula
- ako je `A` iskazna formula, tada je i `~A` iskazna formula
- ako su `A` i `B` iskazne formule, tada su i `A /\ B` (čitamo `A` i `B`), `A \/ B` (čitamo `A` ili `B`), `A => B` (čitamo `A` povlači `B`) i `A <=> B` (čitamo `A` ekvivalentno sa `B`) iskazne formule
- ako je `A` iskazna formula, tada je i `(A)` iskazna formula

## Valuacija

Kako bismo rezonovali o značenju iskazne formule, potrebno je da definišemo pojam valuacije. Valuacija je funkcija koja iskaznim promenljivama dodeljuje istinitosnu vrednost.

Na primer, jedna moguća valuacija `v` za formulu `F = ~p => (q \/ ~r)` je:

- `p -> 1`
- `q -> 0`
- `r -> 1`

Interpretacija formule izračunava njenu istinitosnu vrednost pri datoj valuaciji. U prethodnom primeru:

```text
Iv(F) = ~1 => (0 \/ ~1) = 0 => 0 = 1
```

Za valuaciju `v1`:

- `p -> 0`
- `q -> 0`
- `r -> 1`

```text
Iv1(F) = ~0 => (0 \/ ~1) = 1 => 0 = 0
```

Dakle, u zavisnosti od valuacije, formula se može interpretirati kao tačna ili netačna. Ukoliko postoji valuacija u kojoj se formula interpretira kao tačna, kažemo da je formula zadovoljiva. Ukoliko je formula tačna u svakoj valuaciji, kažemo da je tautologija.

## KNF i SAT

Problem SAT bavi se ispitivanjem da li je formula u posebnom obliku zvanom konjunktivna normalna forma (KNF) zadovoljiva. KNF predstavlja konjunkciju klauza, pri čemu je svaka klauza disjunkcija literala ili logičkih konstanti. Literal je iskazna promenljiva ili njena negacija.

Na primer:

```text
(p \/ ~q) /\ (~p \/ r \/ F) /\ (~r \/ T)
```

je iskazna formula u KNF-u.

Klauze koje sadrže `T` su trivijalno uvek zadovoljene, dok se konstanta `F` može izbrisati iz svih klauza ne menjajući značenje. Shodno tome, možemo smatrati da su elementi klauze zapravo isključivo literali. Takođe, smatramo da je prazna klauza trivijalno nezadovoljena, dok je prazan skup klauza trivijalno zadovoljen.

## DIMACS format

Programi koji rešavaju problem SAT za datu KNF formulu se nazivaju SAT rešavači. Oni na ulazu primaju formulu u specijanom DIMACS formatu za zapisivanje KNF formula.

Na primer, jedan DIMACS fajl izgleda ovako:

```dimacs
p cnf 3 4
1 2 0
-1 3 0
-1 2 -3 0
-3 0
```

Prva linija predstavlja zaglavlje, pri čemu se nakon `p cnf` navode broj promenljivih i broj klauza u formuli. Nakon toga, svaka linija označava klauzu, pri čemu su pozitivnim brojevima označene iskazne promenljive, a negativnim njihove negacije. Kraj svake klauze označava se brojem `0`.

## MiniSAT

SAT rešavač koji koristimo na vežbama se naziva MiniSAT i može se jednostavno instalirati pomoću bilo kog menadžera paketa (npr. `apt-get install minisat`).

Pokretanjem sledeće komande:

```bash
minisat 1.cnf model.out
```

minisat učitava formulu iz DIMACS fajla `1.cnf`, proverava da li je zadovoljiva i ispisuje statistike rešavanja na standardni izlaz. Ukoliko je formula zadovoljiva, ispis se završava sa `SATISFIABLE`, a u suprotnom sa `UNSATISFIABLE`.

Takođe, u slučaju zadovoljive formule, fajl `model.out` će sadržati jednu valuaciju koja zadovoljava polaznu formulu. Na primer, za ranije navedeni DIMACS fajl, ispis u `model.out` mogao bi da bude:

```text
SAT
-1 2 -3 0
```

Što znači da je iskazna promenljiva 2 tačna, dok su iskazne promenljive 1 i 3 netačne.

# Rešenja zadataka

## Zadatak 1

Uvodimo iskazne promenljive:

- `a`: Ana je vitez
- `b`: Boris je vitez
- `c`: Cane je vitez

Ako je osoba vitez, onda je izjava koju je dala tačna. Ako je osoba lažov, onda je izjava koju je dala netačna. Zbog toga za svaku osobu formiramo ekvivalenciju između toga da je osoba vitez i istinitosti njene izjave.

Ana kaže da je Boris lažov, pa imamo:

```text
a <=> ~b
```

Ekvivalenciju prvo možemo zapisati preko dve implikacije:

```text
(a => ~b) /\ (~b => a)
```

Zatim koristimo pravilo da je `A => B` isto što i `~A \/ B`. Zato dobijamo:

```text
(~a \/ ~b) /\ (~~b \/ a)
```

Pošto je `~~b` isto što i `b`, dobijamo KNF:

```text
(~a \/ ~b) /\ (a \/ b)
```

Boris kaže da su Ana i Cane iste vrste. To znači da su ili oboje vitezovi ili oboje lažovi, odnosno da važi `a <=> c`. Zato Borisovu izjavu zapisujemo kao:

```text
b <=> (a <=> c)
```

Ovu formulu posmatramo slično, preko dve implikacije:

```text
(b => (a <=> c)) /\ ((a <=> c) => b)
```

Prvi deo kaže: ako je Boris vitez, onda Ana i Cane moraju biti iste vrste. To znači:

```text
b => ((a => c) /\ (c => a))
```

Kada implikacije prebacimo u disjunkcije, iz ovog dela dobijamo:

```text
~b \/ ~a \/ c
~b \/ ~c \/ a
```

Drugi deo kaže: ako su Ana i Cane iste vrste, onda je Boris vitez:

```text
(a <=> c) => b
```

Koristimo da je:

```text
a <=> c = (a /\ c) \/ (~a /\ ~c)
```

pa drugi smer postaje:

```text
((a /\ c) \/ (~a /\ ~c)) => b
```

Kada implikaciju prebacimo u disjunkciju, dobijamo:

```text
~((a /\ c) \/ (~a /\ ~c)) \/ b
```

Primenom De Morganovih pravila:

```text
(~(a /\ c) /\ ~(~a /\ ~c)) \/ b
```

odnosno:

```text
((~a \/ ~c) /\ (a \/ c)) \/ b
```

Disjunkciju sa `b` raspodeljujemo po konjunkciji, pa dobijamo:

```text
~a \/ ~c \/ b
a \/ c \/ b
```

Ukupno, u KNF-u dobijamo klauze:

```text
(b \/ a \/ c)
(b \/ ~a \/ ~c)
(~b \/ a \/ ~c)
(~b \/ ~a \/ c)
```

Cane kaže da je Ana lažov, pa imamo:

```text
c <=> ~a
```

Analogno prvom iskazu, KNF je:

```text
(~c \/ ~a) /\ (c \/ a)
```

Kada sve ove klauze pošaljemo SAT rešavaču, dobijamo model:

```text
1 -2 -3 0
```

Dakle, Ana je vitez, dok su Boris i Cane lažovi.

Za proveru jedinstvenosti rešenja dodajemo klauzu koja zabranjuje baš ovu valuaciju:

```text
~a \/ b \/ c
```

Kako nakon dodavanja ove klauze SAT rešavač vraća `UNSATISFIABLE`, zaključujemo da je rešenje jedinstveno.

## Zadatak 2

Neka graf ima `V` čvorova i neka želimo da proverimo da li se može pravilno obojiti sa najviše `k` boja.

Uvodimo promenljive:

```text
p(i, j): čvor i je obojen bojom j
```

Broj promenljive u DIMACS formatu možemo računati pomoću funkcije:

```text
p(i, j) = (i - 1) * k + j
```

U delu pod a) dovoljno je obezbediti da svaki čvor ima bar jednu boju. Za svaki čvor `i` dodajemo klauzu:

```text
p(i, 1) \/ p(i, 2) \/ ... \/ p(i, k)
```

Zatim, za svaku granu `(u, v)` i svaku boju `j` dodajemo uslov da susedni čvorovi ne mogu biti obojeni istom bojom:

```text
~p(u, j) \/ ~p(v, j)
```

Ako SAT rešavač vrati `SATISFIABLE`, graf je moguće obojiti sa najviše `k` boja. Ako vrati `UNSATISFIABLE`, takvo bojenje ne postoji.

U delu pod a) ne moramo da zahtevamo da čvor ima najviše jednu boju. Za ispitivanje zadovoljivosti dovoljno je da svaki čvor ima bar jednu boju i da susedni čvorovi nemaju zajedničku boju. Ako neki čvor u modelu dobije više boja, možemo izabrati jednu od njih, jer zbog uslova za grane nijedan njegov sused nema tu boju.

U delu pod b), ako želimo da model direktno predstavlja konkretno bojenje, dodajemo i uslov da svaki čvor ima najviše jednu boju. Za svake dve različite boje `j` i `l` dodajemo:

```text
~p(i, j) \/ ~p(i, l)
```

Tada svaki čvor ima tačno jednu boju: bar jednu zbog prve grupe klauza, a najviše jednu zbog ove grupe klauza.

Najmanji broj boja možemo odrediti linearnom strategijom. Pokrećemo SAT rešavač redom za:

```text
k = 1, 2, 3, ...
```

Prvo `k` za koje formula bude zadovoljiva predstavlja najmanji broj boja potreban za pravilno bojenje grafa.

Možemo koristiti i binarnu strategiju. Prvo odredimo interval u kom se nalazi rešenje, na primer od `1` do `V`, jer se svaki graf sa `V` čvorova može obojiti sa najviše `V` boja. Zatim proveravamo sredinu intervala. Ako je graf obojiv sa `k` boja, pokušavamo sa manjim brojem boja. Ako nije obojiv sa `k` boja, moramo pokušati sa većim brojem boja. Ovo radi zato što važi: ako je graf obojiv sa `k` boja, onda je obojiv i sa svakim brojem boja većim od `k`.

## Zadatak 3

Predavanja označavamo na sledeći način:

- `1`: Logika
- `2`: Algoritmi
- `3`: Veštačka inteligencija
- `4`: Baze podataka

Termine označavamo brojevima:

- `1`: 9 časova
- `2`: 10 časova
- `3`: 11 časova
- `4`: 12 časova

Uvodimo promenljive:

```text
p(i, j): predavanje i se održava u terminu j
```

Broj promenljive možemo računati formulom:

```text
p(i, j) = (i - 1) * 4 + j
```

Svako predavanje mora biti održano u nekom terminu, pa za svako predavanje `i` dodajemo:

```text
p(i, 1) \/ p(i, 2) \/ p(i, 3) \/ p(i, 4)
```

Predavanje ne može biti održano u dva termina istovremeno, pa za svako predavanje `i` i termine `j` i `l`, gde je `j != l`, dodajemo:

```text
~p(i, j) \/ ~p(i, l)
```

Takođe, u jednom terminu se ne mogu održavati dva predavanja. Zato za svaka dva različita predavanja `i` i `l` i termin `j` dodajemo:

```text
~p(i, j) \/ ~p(l, j)
```

Uslov da se Logika održava pre Algoritama možemo zapisati po slučajevima. Za svaki mogući termin Logike navodimo u kojim terminima onda mogu biti Algoritmi:

```text
p(1, 1) => (p(2, 2) \/ p(2, 3) \/ p(2, 4))
p(1, 2) => (p(2, 3) \/ p(2, 4))
p(1, 3) => p(2, 4)
~p(1, 4)
```
Odnosno u KNF obliku:

```text
~p(1, 1) \/ p(2, 2) \/ p(2, 3) \/ p(2, 4)
~p(1, 2) \/ p(2, 3) \/ p(2, 4)
~p(1, 3) \/ p(2, 4)
~p(1, 4)
```

Veštačka inteligencija se ne održava u prvom ni u poslednjem terminu:

```text
~p(3, 1)
~p(3, 4)
```

Baze podataka se održavaju neposredno nakon Logike ili neposredno nakon Veštačke inteligencije. Ovo takođe zapisujemo po slučajevima, u zavisnosti od toga u kom terminu su Baze podataka.

Ako su Baze podataka u četvrtom terminu, onda Logika ili Veštačka inteligencija moraju biti u trećem terminu:

```text
p(4, 4) => (p(1, 3) \/ p(3, 3))
```

U KNF-u to postaje:

```text
~p(4, 4) \/ p(1, 3) \/ p(3, 3)
```

Analogno dobijamo i ostale klauze:

```text
~p(4, 4) \/ p(1, 3) \/ p(3, 3)
~p(4, 3) \/ p(1, 2) \/ p(3, 2)
~p(4, 2) \/ p(1, 1) \/ p(3, 1)
~p(4, 1)
```

Algoritmi se ne održavaju neposredno nakon Baza podataka. To znači da treba zabraniti parove susednih termina u kojima su prvo Baze podataka, a odmah zatim Algoritmi:

```text
~p(4, 1) \/ ~p(2, 2)
~p(4, 2) \/ ~p(2, 3)
~p(4, 3) \/ ~p(2, 4)
```

Logika se ne održava u poslednjem terminu:

```text
~p(1, 4)
```

SAT rešavač za ovu formulu vraća model:

```text
1 -2 -3 -4 -5 6 -7 -8 -9 -10 11 -12 -13 -14 -15 16 0
```

To znači da je jedan raspored:

- Logika u 9 časova
- Algoritmi u 10 časova
- Veštačka inteligencija u 11 časova
- Baze podataka u 12 časova

Za proveru jedinstvenosti dodajemo klauzu koja zabranjuje dobijeni raspored:

```text
~p(1, 1) \/ ~p(2, 2) \/ ~p(3, 3) \/ ~p(4, 4)
```

Kako je nova formula zadovoljiva, postoji bar još neki raspored.

Ako se poslednji uslov promeni tako da se Logika održava u bilo kom terminu sem od 9 časova, tada umesto klauze:

```text
~p(1, 4)
```

dodajemo klauzu:

```text
~p(1, 1)
```

Nakon toga SAT rešavač vraća odgovor `UNSATISFIABLE`, pa je skup rešenja prazan.

## Zadatak 4

U svakom trenutku `i` imamo tri promenljive:

```text
p_i, q_i, r_i
```

Prelaz između dva susedna stanja opisujemo formulom `T_i`.

Pošto važi:

```text
p_{i+1} = ~p_i
```

dobijamo:

```text
p_{i+1} <=> ~p_i
```

U KNF-u:

```text
(~p_{i+1} \/ ~p_i) /\ (p_{i+1} \/ p_i)
```

Za drugi registar važi:

```text
q_{i+1} = p_i xor q_i
```

Odnosno:

```text
q_{i+1} <=> (p_i xor q_i)
```

U KNF-u dobijamo:

```text
(q_{i+1} \/ p_i \/ ~q_i)
(q_{i+1} \/ ~p_i \/ q_i)
(~q_{i+1} \/ ~p_i \/ ~q_i)
(~q_{i+1} \/ p_i \/ q_i)
```

Za treći registar važi:

```text
r_{i+1} = p_i /\ q_i
```

Odnosno:

```text
r_{i+1} <=> (p_i /\ q_i)
```

U KNF-u:

```text
(r_{i+1} \/ ~p_i \/ ~q_i)
(~r_{i+1} \/ p_i)
(~r_{i+1} \/ q_i)
```

Da bismo proverili ponašanje kola nakon četiri takta, formiramo formulu:

```text
T_0 /\ T_1 /\ T_2 /\ T_3
```

Početno stanje je `(0, 1, 0)`:

```text
 I = ~p_0 /\ q_0 /\ ~r_0
```

Da bismo dokazali da se kolo nakon četiri takta vraća u početno stanje, koristimo dokazivanje pobijanjem.

Tvrdnja koju želimo da dokažemo je:

```text
ako je stanje_0 = (0, 1, 0), onda je stanje_4 = (0, 1, 0)
```

Odnosno, dokazujemo da je sledeća formula tautologija:

```text
(I /\ T_0 /\ T_1 /\ T_2 /\ T_3) => (~p_4 /\ q_4 /\ ~r_4)
```

Dokazivanje pobijanjem podrazumeva da formulu iznad negiramo i proverimo da li je `UNSATISFIABLE`. Ukoliko jeste, znači da je polazna formula bila tautologija.

Ukupna formula je zato:

```text
I /\ T_0 /\ T_1 /\ T_2 /\ T_3 /\ (p_4 \/ ~q_4 \/ r_4)
```

Kako SAT rešavač za ovu formulu vraća `UNSATISFIABLE`, negacija polazne tvrdnje nije moguća, pa je polazna tvrdnja uvek tačna.

Za početno stanje `(0, 0, 0)` nakon četiri takta dobija se `(0, 0, 1)`, pa tvrđenje ne važi za proizvoljno početno stanje.

## Zadatak 5

Ponovo uvodimo promenljive:

```text
p_i, q_i, r_i
```

Prelaz između stanja `i` i stanja `i + 1` opisujemo formulom `T_i`.

Za prvi registar važi:

```text
p_{i+1} = ~p_i
```

pa je KNF ista kao u prethodnom zadatku:

```text
(~p_{i+1} \/ ~p_i) /\ (p_{i+1} \/ p_i)
```

Za drugi registar važi:

```text
q_{i+1} = p_i <=> r_i
```

Zato dodajemo klauze:

```text
(q_{i+1} \/ p_i \/ r_i)
(q_{i+1} \/ ~p_i \/ ~r_i)
(~q_{i+1} \/ ~p_i \/ r_i)
(~q_{i+1} \/ p_i \/ ~r_i)
```

Za treći registar važi:

```text
r_{i+1} = p_i \/ q_i
```

Odnosno:

```text
r_{i+1} <=> (p_i \/ q_i)
```

U KNF-u:

```text
(~r_{i+1} \/ p_i \/ q_i)
(r_{i+1} \/ ~p_i)
(r_{i+1} \/ ~q_i)
```

Početno stanje je `(0, 0, 0)`, pa dodajemo:

```text
~p_0 /\ ~q_0 /\ ~r_0
```

Da bismo dokazali da se stanje `(0, 1, 0)` ne može dostići tokom prva četiri takta, ponovo koristimo dokazivanje pobijanjem, slično kao u prethodnom zadatku.

Tvrdnja koju želimo da dokažemo je:

```text
polazeći od (0, 0, 0), stanje (0, 1, 0) se ne pojavljuje u trenucima 0, 1, 2, 3, 4
```

Umesto toga, SAT rešavaču postavljamo suprotno pitanje: da li postoji izvršavanje koje kreće iz `(0, 0, 0)`, prati sva pravila prelaza i u nekom od trenutaka `0, 1, 2, 3, 4` dostiže stanje `(0, 1, 0)`?

Zato formiramo formulu:

```text
T_0 /\ T_1 /\ T_2 /\ T_3
```

i dodajemo uslov da se cilj pojavi u nekom od trenutaka `0, 1, 2, 3, 4`.

Uslov:

```text
(~p_0 /\ q_0 /\ ~r_0)
\/ (~p_1 /\ q_1 /\ ~r_1)
\/ (~p_2 /\ q_2 /\ ~r_2)
\/ (~p_3 /\ q_3 /\ ~r_3)
\/ (~p_4 /\ q_4 /\ ~r_4)
```

nije u KNF-u, jer imamo disjunkciju konjunkcija. Jedan način da to rešimo je da u kodu uvedemo pomoćne promenljive:

```text
c_t: u trenutku t dostignuto je stanje (0, 1, 0)
```

Zatim tražimo da cilj važi u bar jednom od trenutaka:

```text
c_0 \/ c_1 \/ c_2 \/ c_3 \/ c_4
```


Za svako `t` od 0 do 4 dodajemo klauze koje kažu da je `c_t` ekvivalentno tome da je stanje u trenutku `t` baš `(0, 1, 0)`:

```text
~c_t \/ ~p_t
~c_t \/ q_t
~c_t \/ ~r_t
p_t \/ ~q_t \/ r_t \/ c_t
```

Ukupna formula za proveru dostižnosti tokom prva četiri takta je:

```text
I /\ T_0 /\ T_1 /\ T_2 /\ T_3
/\ (c_0 \/ c_1 \/ c_2 \/ c_3 \/ c_4)
/\ za svako t od 0 do 4:
   (~c_t \/ ~p_t)
   /\ (~c_t \/ q_t)
   /\ (~c_t \/ ~r_t)
   /\ (p_t \/ ~q_t \/ r_t \/ c_t)
```

Kako SAT rešavač za ovu formulu vraća `UNSATISFIABLE`, to znači da je pretpostavka koju smo dodali nemoguća. Dakle, ne postoji izvršavanje koje kreće iz `(0, 0, 0)`, poštuje pravila prelaza i tokom prva četiri takta dostiže stanje `(0, 1, 0)`.

Da bismo proverili da li je stanje ikada dostižno, koristimo činjenicu da kolo ima samo tri jednobitna registra. Zbog toga postoji samo 2^3 = 8 mogućih stanja. 

Ako se neko stanje ponovi, dalje ponašanje kola se ponavlja ciklično. Zato je dovoljno proveriti dostižnost stanja `(0, 1, 0)` u najviše 7 prelaza. Ako se stanje ne dostigne u prvih 7 prelaza, neće se dostići nikada. SAT formula se pravi na isti način kao za četiri takta, samo se uvedu pomoćne promenljive `c_0, c_1, ..., c_7` i razviju prelazi do trenutka 7.

Polazeći od `(0, 0, 0)`, dobijamo redom:

```text
(0, 0, 0)
(1, 1, 0)
(0, 0, 1)
(1, 0, 0)
(0, 0, 1)
...
```

Pošto se stanje `(0, 0, 1)` ponavlja, ulazimo u ciklus. Stanje `(0, 1, 0)` se ne pojavljuje, pa zaključujemo da ono nikada nije dostižno iz početnog stanja `(0, 0, 0)`.
