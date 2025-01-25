 #include<iostream>
 using std::cout;
 class A {
 private:
    int x;
 public:
    A(int k = 5): x(k) {cout << k << " A01 ";}
    A(const A& a): x(a.x) {cout << "Ac ";}
    A g() const {return *this;}
 };

 class B {
 private:
    A ar[2];
    static A a;
 public:
    B() {ar[1] = A(7); cout << "B0 ";}
    B(const B& b) {cout << "Bc ";}
 };
 A B::a = A(9);

 A Fun(A* p, const A& a, B b) {
    *p = a;
    a.g();
    return *p;
 };
 int main() {
    cout << "ZERO\n";
    A a1; cout << "UNO\n";
    A a2(3); cout << "DUE\n";
    A* p = &a1; cout << "TRE\n";
    B b; cout << "QUATTRO\n";
    a1 = Fun(p,a2,b); cout << "CINQUE\n";
    A a3 = Fun(&a1,*p,b); cout << "SEI";
 }

 /*
    9 A01 ZERO - stampa questo per primo perché è statica e viene inizializzata prima di tutto
    5 A01 UNO - classica costruzione di default di un oggetto
    3 A01 DUE  - costruzione di un oggetto con parametro
    TRE - non stampa nulla perché forma solo il puntatore
    5 A01 5 A01 7 A01 B0 QUATTRO - costruzione del temporaneo anonimo, oggetto di A e sottooggetto di B
    5 A01 5 A01 Bc Ac Ac CINQUE - costruzione del temporaneo anonimo, oggetto di A, B di copia per tutti i parametri di fun e poi il numero
    5 A01 5 A01 Bc Ac Ac SEI - stessa cosa di prima ma con a3
 */

/*
Più nello specifico (dettaglio):

- prima stampa:  viene stampato l'oggetto statico con 9 poi viene chiamato il costruttore di default ridefinito, che sarebbe A(int k=5). L'unico che può chiamare, quindi 9, A01, UNO

- seconda stampa: usa sempre il costruttore di default ridefinito, che non avendo un valore usa quello del default per l'oggetto a1 che viene costruito da zero. Quindi stampa 5, A01, UNO

- terza stampa: ha già un valore che gli viene dato di default, non è una copia, va ad usare il valore che gli viene passato nel default piuttosto di 5, stessa logica: 3, A01, DUE

- quarta stampa: non avviene nulla a parte l'assegnazione di un *A a un A& e non essendo tracciato l'operator= non provoca nulla al di là di TRE

- quinta stampa: l'oggetto di tipo B richiede la costruzione di due elementi dell'array ar[2], da cui il trigger delle due stampe 5 A01 5 A01 (lo statico è sempre costruito prima di tutti). Poi, il corpo del costruttore crea un oggetto di tipo A con valore 7 assegnato ad un elemento di ar e traccia anche 7 A01. Infine, stampa B0, avendo costruito tutto ciò che serviva

- sesta stampa: viene chiamata Fun il cui valore viene assegnato ad un A. Fondamentalmente, qui stiamo assegnando due riferimento dello stesso tipo, dato che chiamiamo "g" che contiene lo *this, quindi è come se facesse la copia (se noti, la logica interna di questa è letteralmente operator=) per questo, dato che usa un riferimento per il discorso detto, triggera la chiamata di due 5 A01 5 A01
dato che deve costruire due oggetti per ar(2) [per il fatto che dentro "fun" esiste un parametro di tipo B che deve esistere e il costruttore di default assegna un valore ad ar(1), quindi deve esistere ar, ecco perché ne fa le due stampe] e poi la copia di B (Bc) comprese le due copie di A (Ac Ac) per i due oggetti del tipo ar[2]

- settima stampa: logica uguale alla precedente: due trigger di 5 A01 5 A01 dato che ti serve crearti i due parametri A invocati dalla creazione dell'oggetto B con default essendo che fa parte del parametro di funzione Fun, da cui il resto e oi di nuovo Bc Ac Ac SEI

*/

