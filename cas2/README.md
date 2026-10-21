# Uvod u logiku prvog reda

Logika prvog reda predstavlja proširenje iskazne logike koje nam omogućava da izražavamo svojstva objekata, odnose između objekata i tvrđenja koja važe za sve objekte ili za neke od njih.

Na primer, razmotrimo sledeće tvrđenje:

**Za svaki prirodan broj `x` postoji prirodan broj `y` takav da je `x + y > 50`.**

Ovo tvrđenje matematički zapisujemo kao:

```text
∀x ∈ N ∃y ∈ N (x + y > 50)
```

Kako bismo ovo tvrđenje izrazili u iskaznoj logici, morali bismo da uvedemo zasebnu iskaznu promenljivu za svaku kombinaciju vrednosti `x` i `y`. Na primer:

```text
p_0_0: 0 + 0 > 50
p_0_1: 0 + 1 > 50
p_0_2: 0 + 2 > 50
...
p_1_0: 1 + 0 > 50
...
```

Tada bismo pokušali da izrazimo polazno tvrđenje formulom:

```text
(p_0_0 \/ p_0_1 \/ p_0_2 \/ ...)
/\
(p_1_0 \/ p_1_1 \/ p_1_2 \/ ...)
/\
...
```

Međutim, pošto prirodnih brojeva ima beskonačno mnogo, ovakva formula bi bila beskonačna. Takođe, iskazne promenljive nam ne bi govorile ništa o značenju simbola `+` i `>` koji figurišu u formulama.

Dakle, potreban nam je neki fragment logike koji ima veću ekspresivnost kako bismo rezonovali o ovakvim formulama.

## Signatura

Da bismo definisali jezik logike prvog reda, najpre zadajemo njegovu **signaturu**.

Signatura se sastoji od:

- **Funkcijskih simbola**, koji predstavljaju funkcije nad objektima.
- **Relacijskih (predikatskih) simbola**, koji predstavljaju odnose između objekata.
- **Funkcije arnosti**, koja svakom funkcijskom i relacijskom simbolu pridružuje broj argumenata

Funkcijske simbole arnosti 0 ćemo zvati i konstante, dok relacijski simboli arnosti 0 odgovaraju iskaznim promenljivama koje znamo od ranije.

Važno je napomenuti razliku između funkcijskih i relacijskih simbola. **Funkcijski simboli predstavljaju operacije čiji su rezultati objekti, dok relacijski simboli predstavljaju odnose koji mogu biti tačni ili netačni.**

## Termovi

Termovi su izrazi koji predstavljaju objekte u logici prvog reda.

Definišu se rekurzivno:

- Svaka promenljiva je term.
- Svaki konstantni simbol je term.
- Ako je `f` funkcijski simbol arnosti `n`, a `t1, ..., tn` termovi, onda je i `f(t1, ..., tn)` term.

Termovi sami po sebi nemaju istinitosnu vrednost. Oni predstavljaju objekte nad kojima možemo formirati tvrđenja.

## Atomi

Atomi predstavljaju najjednostavnije formule logike prvog reda.

Ako je `P` relacijski simbol arnosti `n`, a `t1, ..., tn` termovi, onda je:

```text
P(t1, ..., tn)
```

atom.

Za razliku od termova, atomi predstavljaju tvrđenja koja mogu biti tačna ili netačna.

## Formule

Formule logike prvog reda gradimo rekurzivno od atoma, koristeći logičke veznike i kvantifikatore.

- Svaki atom je formula.
- Logičke konstante `T` i `F` su formule.
- Ako je `A` formula, onda je i `~A` formula.
- Ako su `A` i `B` formule, tada su i `A /\ B`, `A \/ B`, `A => B` i `A <=> B` formule.
- Ako je `A` formula, onda su i `∀x A` (čitamo za svako x važi A) i `∃x A` (čitamo postoji x za koje važi A) formule.

Pojavljivanje promenljive nazivamo vezanim ako se nalazi u opsegu odgovarajućeg kvantifikatora. U suprotnom, pojavljivanje je slobodno.


## Interpretacija

Da bismo odredili značenje formule logike prvog reda, potrebno je da definišemo interpretaciju.

Interpretacija `I` sastoji se od:

1. Nepraznog skupa `D`, koji nazivamo domenom interpretacije.
3. Dodele svakom funkcijskom simbolu arnosti `n` funkcije `D^n -> D`.
4. Dodele svakom relacijskom simbolu arnosti `n` relacije nad `D`, odnosno podskupa `D^n`.

Na primer, posmatrajmo signaturu:

```text
Konstantni simboli:
    ana
    boris

Relacijski simboli:
    covek arnosti 1
    voli arnosti 2
```

Možemo definisati interpretaciju sa domenom:

```text
D = {1, 2, 3}
```

Konstantnim simbolima dodeljujemo vrednosti:

```text
ana   -> 1
boris -> 2
```

Relacijske simbole interpretiramo kao skupove:

```text
covek = {1, 2}

voli = {(1, 2), (2, 1), (3, 1)}
```

Ovo znači da su objekti `1` i `2` ljudi, da Ana voli Borisa, Boris voli Anu i da objekat `3` voli Anu.

U ovoj interpretaciji formula:

```text
voli(ana, boris)
```

je tačna, dok je formula:

```text
voli(boris, boris)
```

netačna.

Takođe, formula:

```text
∀x (covek(x) => voli(x, ana))
```

je netačna, jer Ana predstavlja objekat `1`, koji jeste čovek, ali par `(1, 1)` ne pripada relaciji `voli`.

Primetimo da domen interpretacije ne mora da sadrži samo objekte za koje važi predikat `covek`.

## Valuacija

Pored interpretacije, potrebna nam je i **valuacija promenljivih**.

U iskaznoj logici valuacija je dodeljivala iskaznim promenljivama istinitosne vrednosti. U logici prvog reda valuacija promenljivama dodeljuje **elemente domena interpretacije**.

Na primer, za domen:

```text
D = {1, 2, 3}
```

jedna moguća valuacija `v` je:

```text
x -> 1
y -> 2
z -> 3
```

Interpretacija određuje značenje funkcijskih i relacijskih simbola, dok valuacija određuje na koje objekte se odnose promenljive.

Na primer, pod prethodno definisanom interpretacijom i valuacijom formula:

```text
voli(x, y)
```

je tačna, jer je `x = 1`, `y = 2`, a par `(1, 2)` pripada relaciji `voli`.

Sa druge strane, formula:

```text
voli(y, y)
```

je netačna, jer par `(2, 2)` ne pripada relaciji.

### Interpretacija složenih formula

Istinitosna vrednost složenih formula određuje se na osnovu značenja njihovih delova.

Za logičke veznike važe ista pravila kao u iskaznoj logici.

Za kvantifikatore važi:

- `∀x A` je tačna ako je `A` tačna za svaku vrednost promenljive `x` iz domena.
- `∃x A` je tačna ako postoji bar jedna vrednost promenljive `x` iz domena za koju je `A` tačna.

Pri proveri kvantifikovane formule menjamo vrednost kvantifikovane promenljive, dok vrednosti ostalih slobodnih promenljivih ostaju nepromenjene.

Za formule bez slobodnih promenljivih istinitosna vrednost ne zavisi od valuacije, već samo od interpretacije.

Kažemo da je formula **zadovoljiva** ako postoji interpretacija (i valuacija, ako formula ima slobodne promenljive) u kojoj je tačna. Formula je **valjana** ako je tačna u svakoj interpretaciji i pri svakoj valuaciji.

## Automatsko dokazivanje teorema

Automatski dokazivači teorema predstavljaju programe koji pokušavaju da utvrde da li neko tvrđenje logički sledi iz zadatih aksioma.

Na vežbama ćemo koristiti dokazivač **Vampire**, koji podržava automatsko dokazivanje u logici prvog reda.

Osnovni princip na kome se zasniva dokazivanje jeste **dokazivanje pobijanjem**.

Pretpostavimo da imamo skup aksioma:

```text
A1, A2, ..., An
```

i želimo da dokažemo tvrđenje `C`.

Umesto da direktno dokazujemo formulu:

```text
A1 /\ A2 /\ ... /\ An => C
```

možemo da proverimo da li je njena negacija nezadovoljiva:

```text
A1 /\ A2 /\ ... /\ An /\ ~C
```

Ako je ova formula nezadovoljiva, zaključujemo da ne postoji interpretacija u kojoj su sve aksiome tačne, a tvrđenje `C` netačno. Dakle, `C` logički sledi iz aksioma.

Vampire očekuje tvrđenje koje dokazuje zadato u takozvanom TPTP formatu. Detalji o samom formatu biće prikazani kroz naredne zadatke, a mogu se naći i na sledećem [sajtu](https://www.tptp.org/).


# Rešenja zadataka

## Zadatak 1

Uvodimo predikate `covek(X)` i `smrtan(X)`, koji označavaju da je `X` čovek, odnosno da je `X` smrtan. Konstantom `sokrat` označavamo Sokrata.

tvrđenje da su svi ljudi smrtni zapisujemo formulom:

```text
![X]: (covek(X) => smrtan(X))
```

Oznaka `![X]` predstavlja univerzalni kvantifikator, odnosno znači „za svako X”. Činjenicu da je Sokrat čovek zapisujemo kao `covek(sokrat)`.

U TPTP formatu početna teorija izgleda ovako:

```tptp
fof(svi_ljudni_su_smrtni, axiom, ![X]: (covek(X) => smrtan(X))).
fof(sokrat_je_covek, axiom, covek(sokrat)).

fof(sokrat_je_smrtan, conjecture, smrtan(sokrat)).
```

Svaka formula ima ime, ulogu (`axiom` ili `conjecture`) i sadržaj. Ako sačuvamo ove formule u fajl `1.tptp`, proveru možemo pokrenuti komandom:

```bash
./vampire 1.tptp
```

Vampire će za tvrđenje `smrtan(sokrat)` vratiti status `Theorem`. Zaista, iz `covek(sokrat)` i univerzalnog pravila dobijamo `smrtan(sokrat)`.

U delu pod b) ispitujemo sledeće tvrđenje: da li je svaki smrtan čovek ujedno i čovek? Menjamo samo formulu sa ulogom `conjecture`:

```tptp
fof(svi_smrtni_su_ljudi, conjecture, ![X]: (smrtan(X) & covek(X) => covek(X))).
```

Za ovo tvrđenje nam Vampire takođe daje status `Theorem`. Čak i kada bismo uklonili sve aksiome, pošto je tvrđenje oblika `p & q => q`, mogli bismo da dokažemo da je formula valjana.

Dalje, proveravamo da li iz aksioma sledi da Sokrat nije smrtan:

```tptp
fof(sokrat_je_smrtan, negated_conjecture, smrtan(sokrat)).
```

Ovde `negated_conjecture` naznačava Vampire-u da je tvrđenje koje se dokazuje već negirano. Pošto iz aksioma sledi `smrtan(sokrat)`, tvrđenje da Sokrat nije smrtan ne važi, a Vampire nam daje status `Satisfiable`.

U delu pod c) dodajemo tvrđenje da postoji čovek koji nije smrtan. Egzistencijalni kvantifikator označava se sa `?`:

```tptp
fof(postoje_besmrtni, axiom, ?[X]: (covek(X) & ~smrtan(X))).
```

Ovaj aksiom je u suprotnosti sa pravilom da su svi ljudi smrtni. Da bismo proverili konzistentnost, možemo tražiti dokaz kontradikcije:

```tptp
fof(provera_konzistentnosti, conjecture, $false).
```

Vampire može dokazati `$false`, što znači da je skup aksioma nekonzistentan.

## Zadatak 2

Uvodimo sledeće predikate:

- `admin(X)`: `X` je administrator.
- `gost(X)`: `X` je gost.
- `poverljiv(D)`: dokument `D` je poverljiv.
- `ima_pristup(X, D)`: `X` ima pristup dokumentu `D`.
- `moze_da_cita(X, D)`: `X` može da čita dokument `D`.

Bitno je primetiti da razlikujemo **pristup** i **mogućnost čitanja**.

Prvo pravilo kaže da svaki administrator ima pristup svakom dokumentu:

```tptp
fof(ax1, axiom, ![X, Y]: (admin(X) => ima_pristup(X, Y))).
```

Drugo pravilo kaže da iz pristupa dokumentu sledi mogućnost čitanja:

```tptp
fof(ax2, axiom, ![X, Y]: (ima_pristup(X, Y) <=> moze_da_cita(X, Y))).
```

Treće pravilo zabranjuje gostima pristup poverljivim dokumentima:

```tptp
fof(ax3, axiom, ![X, Y]: (gost(X) & poverljiv(Y) => ~ima_pristup(X, Y))).
```

Dodajemo činjenice iz teksta zadatka:

```tptp
fof(h1, hypothesis, admin(ana)).
fof(h2, hypothesis, gost(boris)).
fof(h3, hypothesis, poverljiv(ugovor)).
```

U delu pod b) dokazujemo da Ana može da čita ugovor. Dodajemo:

```tptp
fof(conj1, conjecture, moze_da_cita(ana, ugovor)).
```

Vampire dokazuje ovo tvrđenje: Ana je administrator, ugovor je dokument, pa Ana ima pristup ugovoru. Iz pristupa sledi mogućnost čitanja.

U delu pod c) želimo da proverimo može li se dokazati da Boris ne može da čita ugovor:

```tptp
fof(conj2, conjecture, ~moze_da_cita(boris, ugovor)).
```

Iz aksioma sledi `~ima_pristup(boris, ugovor)`. Međutim, ne postoji pravilo koje garantuje da ako neko nema pristup dokumentu, onda ne može da ga čita, pa Vampire ne uspeva da dokaže tvrđenje.

Isto važi i za deo pod d). tvrđenje:

```tptp
fof(conj3, conjecture, ![X, Y]: (gost(X) & poverljiv(Y) => ~moze_da_cita(X, Y))).
```

nije posledica polaznih pravila iz istih razloga.

Kako bismo dokazali oba prethodna tvrđenja, potrebno je da obezbedimo i drugi smer implikacije, tj. da pristup i mogućnost čitanja budu ekvivalentni:

```tptp
fof(ax2, axiom, ![X, Y]: (ima_pristup(X, Y) <=> moze_da_cita(X, Y))).

```

U delu pod e) dodajemo:

```tptp
fof(h4, hypothesis, gost(ana)).
```

Sada Ana, kao administrator, ima pristup ugovoru, a kao gost nema pristup istom poverljivom dokumentu. Dakle, iz aksioma slede i `ima_pristup(ana, ugovor)` i `~ima_pristup(ana, ugovor)`, pa je teorija nekonzistentna:

```tptp
fof(conj4, conjecture, $false).
```

## Zadatak 3

Uvodimo konstante `agata`, `batler` i `carls`, kao i predikate:

- `zivi(X)`: `X` živi u vili.
- `ubio(X, Y)`: `X` je ubio `Y`.
- `mrzi(X, Y)`: `X` mrzi `Y`.
- `bogatiji(X, Y)`: `X` je bogatiji od `Y`.

Pošto je poznato da je Agatu ubio neko ko živi u vili, uvodimo egzistencijalno tvrđenje:

```tptp
fof(ax1, axiom, ?[X]: (zivi(X) & ubio(X, agata))).
```

Zatim navodimo da tri navedene osobe žive u vili i da je svaki stanovnik jedna od njih. Jednakost u TPTP formatu zapisuje se simbolom `=`:

```tptp
fof(ax2, axiom, zivi(agata) & zivi(carls) & zivi(batler)).
fof(ax3, axiom, ![X]: (zivi(X) => (X = agata | X = batler | X = carls))).
```

Ubica mrzi žrtvu i nije bogatiji od nje:

```tptp
fof(ax4, axiom, ![X, Y]: (ubio(X, Y) => mrzi(X, Y))).
fof(ax5, axiom, ![X, Y]: (ubio(X, Y) => ~bogatiji(X, Y))).
```

Čarls ne mrzi osobe koje Agata mrzi:

```tptp
fof(ax6, axiom, ![X]: (mrzi(agata, X) => ~mrzi(carls, X))).
```

Agata mrzi sve osim batlera:

```tptp
fof(ax7, axiom, ![X]: (mrzi(agata, X) <=> X != batler)).
```

Batler mrzi svakoga ko nije bogatiji od Agate, kao i svakoga koga Agata mrzi:

```tptp
fof(ax8, axiom, ![X]: (~bogatiji(X, agata) => mrzi(batler, X))).
fof(ax9, axiom, ![X]: (mrzi(agata, X) => mrzi(batler, X))).
```

Niko ne mrzi baš svakoga iz domena:

```tptp
fof(ax10, axiom, ![X]: ?[Y]: (~mrzi(X, Y))).
```

Agata i batler nisu ista osoba:

```tptp
fof(ax11, axiom, agata != batler).
```

U delu pod a) proveravamo redom ko je ubica:

```tptp
fof(conj1, conjecture, ubio(carls, agata)).
fof(conj1, conjecture, ubio(batler, agata)).
fof(conj1, conjecture, ubio(agata, agata)).
```

Vampire može dokazati samo treće tvrđenje. Obrazloženje je sledeće:

- Agata mrzi sebe, jer nije batler.
- Čarls zato ne mrzi Agatu, pa nije mogao da je ubije.
- Batler mrzi Agatu i Čarlsa, jer ih Agata mrzi. Ako bi batler ubio Agatu, morao bi da važi `~bogatiji(batler, agata)`, odakle bi sledilo da batler mrzi i sebe. Tada bi mrzeo sve stanovnike vile, što je zabranjeno.
- Pošto Agatu mora ubiti neko od stanovnika, preostaje Agata.

U delu pod b) pitamo da li se može dokazati da Agata mrzi sebe:

```tptp
fof(conj2, conjecture, mrzi(agata, agata)).
```

Odgovor je da, neposredno iz pravila o Agatinoj mržnji i činjenice da Agata živi u vili.

U delu pod c) proveravamo:

```tptp
fof(conj3, conjecture, bogatiji(agata, batler)).
```

Ovo tvrđenje ne možemo dokazati iz datih aksioma. Pravila o ubici i batlerovoj mržnji ne određuju da li je Agata bogatija od batlera. Bez dodatnih pretpostavki o odnosu bogatstva, mogući su modeli u kojima ovo tvrđenje važi i modeli u kojima ne važi.

## Zadatak 4

Za opis skupova uvodimo predikat `el(X, A)`, koji znači da je `X` element skupa `A`. Predikati `unija(A, B, U)`, `presek(A, B, P)` i `razlika(A, B, R)` označavaju da je treći argument rezultat odgovarajuće operacije nad prva dva skupa. Predikat `jednaki(A, B)` izražava jednakost skupova preko pripadnosti elemenata.

Definicije u TPTP formatu su:

```tptp
fof(jednaki_skupovi, axiom, ![A, B]: (jednaki(A,B) <=> ![X]: (el(X, A) <=> el(X, B)))).

fof(unija_skupova, axiom, ![A, B, C]: (unija(A, B, C) <=> 
                          ![X]:(el(X, C) <=> el(X, A) | el(X, B)))).

fof(presek_skupova, axiom, ![A, B, C]: (presek(A, B, C) <=> 
                          ![X]:(el(X, C) <=> el(X, A) & el(X, B)))).

fof(razlika, axiom, ![A, B, C]: (razlika(A, B, C) <=> 
                          ![X]:(el(X, C) <=> el(X, A) & ~el(X, B)))).                                                    
```

Ove definicije govore šta znači da je dati skup rezultat operacije. One same po sebi ne tvrde da rezultujući skup za svaku kombinaciju argumenata mora da postoji. U narednim upitima zato eksplicitno koristimo promenljive za međurezultate i polazimo od pretpostavke da odgovarajuće operacije za njih važe.

U delu pod b) dokazujemo distributivnost razlike u odnosu na uniju:

```text
A \ (B ∪ C) = (A \ B) ∩ (A \ C)
```

Uvode se skupovi `BuC = B ∪ C`, `Levo = A \ BuC`, `ArB = A \ B`, `ArC = A \ C` i `Desno = ArB ∩ ArC`. Formulu zapisujemo ovako:

```tptp
fof(conj1, conjecture,
    ![A, B, C, BuC, ArB, ArC, Levo, Desno]:(
        unija(B, C, BuC) &
        razlika(A, B, ArB) &
        razlika(A, C, ArC) &
        razlika(A, BuC, Levo) &
        presek(ArB, ArC, Desno) =>
        jednaki(Levo, Desno)
    )).
```

Ovo tvrđenje je dokazivo. 

U delu pod c) ispitujemo odnos:

```text
(A \ B) ∩ C = (A ∪ C) \ B
```

Uvodimo `ArB = A \ B`, `Levo = ArB ∩ C`, `AuC = A ∪ C` i `Desno = AuC \ B`. Proveravamo da li je leva strana jednaka desnoj:

```tptp
fof(conj2, conjecture, 
   ![A, B, C, ArB, AuC, Levo, Desno]:
       (
           razlika(A, B, ArB) &
           unija(A, C, AuC) &
           presek(ArB, C, Levo) &
           razlika(AuC, B, Desno)  =>
           jednaki(Levo, Desno)
       )).
```

Ovo tvrđenje ne važi. Za kontraprimer možemo uzeti `A = {1}`, `B = {}` i `C = {}`. Tada je `Levo` prazan skup, a `Desno` je `{1}`, pa `Levo` i `Desno` nisu jednaki.

Da bismo proverili da li važi neki smer inkluzije, uvodimo relaciju `podskup`:

```tptp
fof(podskupovi, axiom, ![A, B]: (podskup(A,B) <=> ![X]: (el(X, A) => el(X, B)))).
```

Zamenom `jednaki(Levo, Desno)` redom sa `podskup(Levo, Desno)` i `podskup(Desno, Levo)`, možemo dokazati da prvi smer inkluzije važi, ali drugi ne.

## Zadatak 5

Grupu predstavljamo pomoću:

- konstante `e` za neutralni element;
- funkcije `mult(X, Y)` za proizvod elemenata `X` i `Y`;
- funkcije `inv(X)` za inverz elementa `X`.

Za razliku od predikata, funkcijski simboli predstavljaju elemente domena. Zato izraz `mult(X, Y)` možemo koristiti kao argument druge funkcije, npr. `mult(mult(X, Y), Z)`.

Aksiome zadate u tekstu zapisujemo ovako:

```tptp
fof(neutral, axiom, ![X]: (mult(e, X) = X)).
fof(inverz, axiom, ![X]: (mult(inv(X), X) = e)).
fof(asoc, axiom, ![X, Y, Z]: (mult(mult(X, Y), Z) = mult(X, mult(Y, Z)))).
```

Dodatni uslov da je kvadrat svakog elementa jednak neutralnom elementu je:

```tptp
fof(h1, hypothesis, ![X]: (mult(X, X) = e)).
```

U delu pod b) želimo da dokažemo da je svaki element jednak svom inverzu:

```tptp
fof(conj1, conjecture, ![X]: (X = inv(X))).
```

Vampire dokazuje ovo tvrđenje.

U delu pod c) dokazujemo komutativnost:

```tptp
fof(conj2, conjecture, ![X, Y]: (mult(X, Y) = mult(Y, X))).
```

Vampire dokazuje i ovo tvrđenje.
