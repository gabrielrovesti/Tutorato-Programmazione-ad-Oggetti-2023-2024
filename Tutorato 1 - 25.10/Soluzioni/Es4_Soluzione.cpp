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

