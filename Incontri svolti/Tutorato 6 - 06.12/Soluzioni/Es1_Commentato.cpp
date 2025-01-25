#include <iostream> 

using namespace std;

// gestione dello stato di fallimento
// (aka, creo classe di tipo Fallimento)

class Fallimento{
    private:
        string s;
    public:
        Fallimento(string msg): s(msg) {};
        string getMessaggio() const{return s;}
};

long Fun(const ios& s){
    // controllo se è un ifstream

    if(s.fail()) throw Fallimento("Stato di errore");

    // due alternative di conversione
    // (1) tolgo il const
    ifstream* i = 
    dynamic_cast<ifstream*>(const_cast<ios*>(&s));
    // (2) tengo il const
    // const ifstream* i = dynamic_cast<const ifstream*>(&s));
    if(!i) return -2; // (a)
    if(!i->isOpen()) return -1; // (b)
    return i->tellg(); // (c)

}