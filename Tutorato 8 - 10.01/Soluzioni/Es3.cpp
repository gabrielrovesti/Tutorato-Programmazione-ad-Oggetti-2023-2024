/*
Queste definizioni compilano correttamente. Definire una funzione
List<const D *const> fun (const vector<const B*>&)
con il seguente comportamento: in ogni invocazione fun, per tutti i puntatori “q” contenuti nel vector “v”:
(A)	se “q” non è nullo e ha un tipo dinamico esattamente uguale a "C" allora “q” deve essere rimosso da “v”;
a.	se il numero N di puntatori rimossi dal vector v è maggiore di 2 allora viene sollevata un’eccezione di tipo C.
(B)	sul puntatore “q” non nullo deve essere invocata la funzione virtuale pure A* A::f() che ritorna un puntatore che indichiamo qui con “ptr”;
a.	se “ptr” è nullo allora viene sollevata una eccezione std::string(“nullptr”);
b.	“fun” ritorna la lista di tutti e soli questi puntatori “ptr” che: non sono nulli ed hanno un tipo dinamico che è sottotipo di D* e non è sottotipo di E*.
*/

#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>

using namespace std;

class A {
public:
    virtual ~A() {}
    virtual A* f() const = 0;
};

class B : public A {
public:
    virtual ~B() {}
    virtual B* f() const = 0;
};

class C : public B {
public:
    virtual ~C() {}
    virtual C* f() const { return nullptr; }
};

class D : public B {
public:
    virtual ~D() {}
    virtual D* f() const { return nullptr; }
};

class E : public D {
public:
    virtual ~E() {}
    virtual E* f() const { return nullptr; }
};

list<const D *const> fun(vector<const B*>& v) {
    list<const D *const> result;
    int count = 0;

    for (vector<const B*>::iterator it = v.begin(); it != v.end();) {
        const B* q = *it;

        if (q != nullptr && typeid(*q) == typeid(C)) {
            count++;
            if (count > 2) {
                throw C();
            }

            it = v.erase(it); // Rimuovi l'elemento dal vettore
            delete q;         // Libera la memoria dell'oggetto
        } else {
            A* ptr = q->f();
            if(ptr == nullptr){
                throw std::string("nullptr");
            }
            //if(dynamic_cast<D*>(ptr) != nullptr && dynamic_cast<E*>(ptr) == nullptr){ //Completamente equivalente; per const correctness, viene mostrata la seconda soluzione
                //result.push_back(dynamic_cast<D*>(ptr));
            //}

            if(dynamic_cast<const D *const>(ptr) != nullptr && dynamic_cast<const E *const>(ptr) == nullptr){
                result.push_back(dynamic_cast<const D *const>(ptr));
            }

            ++it; // Passa all'elemento successivo solo se non viene rimosso
        }
    }

    return result;
}

