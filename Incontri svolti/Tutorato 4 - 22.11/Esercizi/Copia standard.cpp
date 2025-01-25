#include <iostream>
#include <vector>

using namespace std;

class E: public D{
    private:
        vector<double*> v;
        int *p;
        int& ref;
    public:
        // copia come la standard
        E(const E& e): D(e), v(e.v), p(e.p),
        ref(e.ref) {}
};

// con più classi e facendo "le cose per bene"
class E: public C, public D{
    private:
        vector<double*> v;
        int *p;
        int& ref;
    public:
        // copia come la standard
        // tutti i costr. di copia delle superclassi
        // e poi variabile(rif.variabile)
        E(const E& e): C(e), D(e), v(e.v), p(e.p),
        ref(e.ref) {}
        // Fare le cose "meglio" aka 
        // vedere se esistono i puntatori

        // O con gli if
        // O con la condizione ternaria
        // (condizione) ? cond.vera : cond.falsa
        // p == nullptr ? p(0) : p(e.p) {};
};