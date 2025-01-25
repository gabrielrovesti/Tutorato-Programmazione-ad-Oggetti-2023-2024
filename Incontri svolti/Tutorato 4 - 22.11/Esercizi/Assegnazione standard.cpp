class D: public B {
    private:
        Z y;
    public:
        // assegnazione standard
        D& operator=(const D& d){
            // Alternativa a quella sotto
            // this->B::operator=(d);
            B::operator=(d);

            // assegnazione di tutti i sottocampi
            y = d.y;
            // variabile = riferimento.variabile

            return *this; //puntatore al contesto di invocazione
        }
};

// se ci sono più classi e più campi
class D: public A, public B {
    private:
        Z y;
        int *p;
        double dou;
    public:
        // assegnazione standard
        D& operator=(const D& d){
            //this->A::operator=(d);
            //this->B::operator=(d);
            A::operator=(d);
            B::operator=(d);

            // assegno tutti i campi
            y = d.y;
            p = d.p;
            dou = d.dou;

            return *this;
        }
};

/*
/// assegnazione profonda
class Lista{
    private:
    class Nodo{};

    public:
    Lista& operator=(const Lista& l){
        /// assegno tutti i nodi
        for....
        l.nodo = nodo;
    }
};
*/