#include "iostream"

using namespace std;

class C { 
    public: 
        int a; 
        void fC() { a=2; }
};
class D: public C { 
    public: 
        double a; 
        void fD() { a=3.14; C::a=4; }
};
class E: public D { 
    public: 
        char a; 
        void fE() { a='*'; C::a=5; D::a=6.28; }
};
int main() { 
    C c; D d; E e; 
    c.fC(); 
    d.fD(); 
    e.fE(); 
    D* pd = &d; 
    E& pe = e; 
    cout << pd->a << " " << pe.a << endl; 
    cout << pd->a << " " << pd->D::a << " " << pd->C::a << endl; 
    cout << pe.a << " " << pe.D::a << " " << pe.C::a << endl; 
    cout << e.a << " " << e.D::a << " " << e.C::a << endl;
}

/*
3.14 * - stampa questo in quanto chiama il suo valore locale 3.14, mentre "e" chiama solo "*"
3.14 3.14 4 - stessa cosa per la prima stampa, la seconda con scoping e la terza assegna 4 con scoping dentro il tipo D
* 6.28 5 - * per la prima stampa essendo un oggetto di tipo "e", poi usa lo scoping per D dentro E e infine lo scoping di C dentro E
* 6.28 5 - stessa cosa della stampa precedente
*/
