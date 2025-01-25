#include <iostream>
#include <vector>
using namespace std;

class A{
private:
    virtual void f() const = 0;
    vector<int*>* ptr;
};

class D: virtual public A{
private:
    int z;
    double w;
};

class E: public D{
private:
    vector<double*> v;
    int *p;
    int& ref;
public:
    void f() const {}
    E(): D(), v(), p(), ref() {}
    E(E e): D(e), v(e.v), p(e.p), ref(e.ref) {}
    //ridefinizione del costruttore di copia di E

    /*
    Si considerino le precedenti definizioni. Ridefinire (senza usare
    la keyword "default") nello spazio sottostante il costruttore di copia della classe E
    in modo tale che il suo comportamento coincida con quello del costruttore di copia standard di E.
    */

    // Chiamo la copia della superclasse/delle superclassi
    // e poi copio tutti i campi
    E(const E& e): D(e), v(e.v), p(e.p), ref(e.ref) {}

};
