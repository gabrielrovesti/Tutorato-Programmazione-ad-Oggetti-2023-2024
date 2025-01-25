#include <iostream>

using namespace std;

class A{
public:
    virtual ~A();
    // se non lo mettiamo, dà errore base class is not polymorphic
};

class B: public A{
public:
    virtual void method() = 0; // astratto - virtuale puro
};

class C: public B{
public:
    virtual void method(){}; // concreto
};

// permette solo la costruzione 
// dei suoi sottooggetti
class D{
    protected:
    D d;
    // ovviamente no public,
    // private dice "se fornisco i get(), le mie cose si vedono all'esterno"
};

class E: public D{
    private:
    int x;
    // assegnazione come quella standard
    public:
    E& operator=(const E& e){
        // deriva da D e assegnazione come quella standard
        // aka = costruire il sottooggetto con D

        D::operator=(e); //richiamo operator=
        x = e.x; // assegno tutti i campi

        // non mi serve fare //if (this != &e)
        // perché l'ereditarietà già costruisce il sottooggetto
        // anche il delete

        return *this; 
        // puntatore al contesto di invocazione
    }
};