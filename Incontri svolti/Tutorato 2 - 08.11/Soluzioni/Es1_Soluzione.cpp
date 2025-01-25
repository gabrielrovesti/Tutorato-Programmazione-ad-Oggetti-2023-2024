#include <iostream>
using namespace std;

class S{
    public:
        string s;
        S(string t): s(t) {}
};

class N{
    private:
        S x;
    public:
        N* next;
        N(S t, N* p): x(t), next(p) 
        {cout << "N2 ";}

        ~N() {
            if(next) 
            delete next; 
            cout << x.s + "~N ";
        }
};

class C{
    N* pointer;
    public:
        C(): pointer(0) {}
        ~C() {delete pointer; cout << "~C ";}
        void F(string t1, string t2 = "pippo"){
            pointer = new N(S(t1), pointer);
            pointer = new N(t2, pointer);
        }
};

int main(){
    C* p = new C; cout << "UNO\n";
    p->F("pluto, paperino"); 
    p->F("topolino"); cout << "DUE\n";
    delete p; cout << "TRE\n";
}

/*
UNO - non traccia nulla di utile
N2 N2 N2 N2 DUE - deve costruire tramite n ogni stringa, da pluto a topolino, compreso l'oggetto di creazione
pluto, paperino~N pippo~N topolino~N pippo~N ~C TRE - cancello tutti i valori in ordine e stampo
*/

/*
Commento sull'ultima stampa:

Di fatto, l'oggetto viene costruito con "pluto/paperino/topolino" come stringhe (e grazie al costruttore relativo, si inserisce anche pippo nello step "p->F("topolino");"

Quindi: 
- p->F("pluto, paperino");  (metto pluto e paperino come stringhe)

- p->F("topolino"); (mette topolino e grazie al metodo F —>    void F(string t1, string t2 = "pippo"){
diventa qui "topolino/pippo"

Il delete poi fa cancellare tutti gli oggetti nello stesso ordine (if next/delete next), quindi parte dall'inizio e cancella tutto ciò che vede

Di fatto, si vedono quelle stampe date le stringhe costruite con questa logica e poi il fatto che stampa "x.s", che sarebbe l'oggetto puntato (tipo S quindi stringa) e il corpo della cancellazione (x.s), da cui le stampe che vedi
*/