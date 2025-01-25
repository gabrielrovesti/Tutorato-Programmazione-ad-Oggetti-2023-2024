#include <typeinfo>

class Abs{
public:
    virtual ~Abs() = 0;
};

template<class T1, class T2>
Fun(T1* t1, T2& t2){
    // typeid
    // dynamic_cast
    if(typeid(T1) == typeid(T2) //punto 1
    && typeid(*t1) == typeid(t2) //punto 2
    && dynamic_cast<Abs*>(&t1)){ //punto 3
        return true;
    }
    // non vado a fare la conversione verso T2
    // in quanto controlliamo già che siano lo stesso tipo dinamico
    // quindi non è necessario andare anche a fare quel controllo
    // (perché se fallisce, vuol dire che non è neanche un T2)
    return false;
}