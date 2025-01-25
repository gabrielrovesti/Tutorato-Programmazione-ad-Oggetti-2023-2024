#include <iostream> //per prendere tutto il resto
#include <fstream> //per ofstream e ifstream
#include <string>

using namespace std;

class Fallimento{
    private:
    string errore;
    public:
    Fallimento(string e): errore(e) {}
};

long Fun(const ios& s){
    if(s.fail()) throw Fallimento("Errore");
    
    ifstream* i=dynamic_cast<ifstream*>(const_cast<ios*>(&s));
    if(!i) return -2; //non è un ifstream
    //Variante se ifstream fosse const (const ifstream)
    //if(!dynamic_cast<const ifstream*>(&s)) return -2;
    if(!i && !i->is_open()) return -1; //non è un ifstream e il file non è aperto
    if(i && i->is_open()) return i->tellg(); //i è istream e ritorna la posizione della cella corrente
    return 0;
}

int main(){
    
}