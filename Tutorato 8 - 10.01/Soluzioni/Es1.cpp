

#include <iostream>

using namespace std;
class A{
    protected:
        virtual void j() { cout<<" A::j "; }
    public:
        virtual void g() const { cout <<" A::g "; } 
        virtual void f() { cout <<" A::f "; g(); j(); } 
        void m() { cout <<" A::m "; g(); j(); }
        virtual void k() { cout <<" A::k "; j(); m(); }
        virtual A* n() { cout <<" A::n "; return this; }
};

class B: public A{
    public:
        virtual void g() const override { cout <<" B::g "; }
        virtual void m() { cout <<" B::m "; g(); j(); }
        void k() { cout <<" B::k "; A::n(); }
        A* n() override { cout <<" B::n "; return this; }
};

class C: public A {
    private:
        void j() { cout <<" C::j "; }
    public:
        virtual void g() { cout <<" C::g "; } 
        void m() { cout <<" C::m "; g(); j(); } 
        void k() const { cout <<" C::k "; k(); }
};

class D: public B{
    protected:
       void j() { cout <<" D::j "; }
    public:
        B* n() final { cout <<" D::n "; return this; }
        void m() { cout <<" D::m "; g(); j(); } 
};

A* p1 = new D(); A* p2 = new B(); A* p3 = new C(); B* p4 = new D(); const A* p5 = new C();

int main(){
    p1->g(); // B::g
    p1->k(); // B::k  A::n 
    p2->f(); // A::f  B::g  A::j
    p2->m(); // A::m  B::g  A::j
    p3->k(); // A::k  C::j  A::m  A::g  C::j
    p3->f(); // A::f  A::g  C::j 
    p4->m(); // D::m  B::g  D::j
    p4->k(); // B::k  A::n
    p5->g(); // A::g 
    (p3->n())->m(); // A::n  A::m  A::g  C::j 
    (p3->n())->n()->g(); // A::n  A::n  A::g 
    (p4->n())->m(); // D::n  A::m  B::g  D::j
    //(p5->n())->g(); // non compila (dovuto al const su this)
    (dynamic_cast<B*>(p1))->m(); //  D::m  B::g  D::j 
    //(static_cast<C*>(p2))->k(); // errore run time (chiamata infinita di k() in c)

    (dynamic_cast<B*>(p3->n()))->g(); cout << endl; // A::n A::g
}

/*
Logica generale cosa stampa:
- Guardo prima tipo statico e tipo dinamico
- Devo sempre vedere se la classe base/superclasse ridefinisce il metodo
- Se non corrisponde nessun metodo, guardo se esiste qualcosa nel resto della gerarchia

Casi particolari:
- dynamic_cast --> converte dinamicamente il tipo e rende TS = tipo a cui convertiamo e il tipo dinamico
resta lo stesso
    - tendenzialmente questo va sempre bene; se possibile convertiamo al tipo richiesto,
    altrimenti per overriding guardiamo cosa c'è più in basso
- static_cast --> converte il tipo del puntatore prima che vada in esecuzione
    - come nel caso dell'ultima stampa; ritorna uno *this che è di tipo A, vede che può andare verso B
    ma rimane in A (essendo che B rimane sempre un A)
    - va sempre bene se dalla classe sopra andiamo alla classe sotto

Altri casi da segnalare:
    - errore runtime
        - caso metodo che si chiama ricorsivamente
    - non compila
        - puntatore costante e ritorno this (che non è costante)
*/

/*
Motivi dell'ultima stampa come A::n A::g
- Direi che l'idea è che noi siamo tipo statico A e tipo dinamico C. Stiamo cercando di convertire staticamente a B, che è sullo stesso livello di C.
Il cast statico funziona subito a livello di compilazione, ma se andassimo da A verso B.

- Provando la stessa stampa sul dynamic_cast, quindi (dynamic_cast<B*>(p3->n()))->g() stampa solo A::n, ma poi essendoci due tipi sullo stesso livello della gerarchia, 
non sa quale scegliere e si ferma lì con la stampa

- Se la conversione andasse subito in porto, avremmo subito B::n e B::g 
(cosa che accadrebbe ad esempio con (static_cast<B*>(p2->n()))->g(); 
che ha tipo statico A e tipo dinamico B)

- Quindi di base il motivo è che è che C non vede B, vede solo A. 

*/