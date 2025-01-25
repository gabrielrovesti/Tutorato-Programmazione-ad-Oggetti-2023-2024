#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Dizionario{
    // operatore di stampa - lo facciamo come funzione esterna
    friend ostream& operator<<(ostream&, const Dizionario<T>);
    private:
        vector<string> keys;
        vector<T> values;
        // Dizionario [string] [T]
    public:
        //metodi "classici" da container
        bool insert(string, const T&);
        bool erase(string);
        T* findValue(string);
        vector<string> findKey(const T&);
        // operatore di indicizzazione
        // subscripting = []
        T* operator[](string);
        // [&] <-- * (stiamo puntando qui e il value è di tipo T) 
        // ci mettiamo "string" perché stiamo puntando la chiave

        //metodo di utility per controllare se non faccio collisione
        int index(string);
};

template <class T>
int Dizionario<T>::index(string key){
    for(int k=0; k<keys.size(); k++){
        if(values[k]==key) return k;
        else return -1;
    }
}

// (1) Inserimento

// dire (dato che definiamo esternamente) che fa parte di template
template<class T>
bool Dizionario<T>::insert(string s, const T& t){
    // controllare se possiamo inserire nell'indice
    // è valido e non fa collisione (che non esiste una chiave o un valore
    // in quella posizione)
    int index_found = index(s);
    // fatto questo, inseriamo

    // se possiamo inserire, lo facciamo
    if(!index_found) return false;
    else{
        // inserire nei vector - usiamo il suo metodo (push_back)
        keys.push_back(s);
        values.push_back(t);
        return true;
    }
}

// (2) Cancellazione
template <class T>
bool Dizionario<T>::erase(string s){
    // Controlliamo se l'indice è valido
    // (cioè, se posso cancellare la chiave)
    int index_found = index(s);
    // In quel caso, cancello
    if(!index_found) return false;
    else{
        // cancelliamo la chiave (usiamo "erase")
        keys.erase(s);
        // s = keys.erase(s); //un pelo meglio, se si controlla che la posizione è valida
    }
}

// (3) trovo il valore
template <class T>
T* Dizionario<T>::findValue(string s){
    // trovo la corrispondenza del valore rispetto alla chiave
    for(int i=0; i < values.size(); ++i){
        if(keys[i] == s){
            return &values[i]; 
            // **values + i
        }
    }
    
}

// (4) trovo la chiave
template <class T>
vector<string> Dizionario<T>::findKey(const T& t){
    vector<string> v;
    for(int i=0; i<keys.size(); i++){
        if(t == values[i])  v.push_back(keys[i]);
    }
    return v;
}

// operatore di stampa
template <class T>
ostream& operator<<(ostream& os, const Dizionario<T>& dict){
    for(int i=0; i<dict.keys.size(); i++){
        os << "Chiave: " << dict.keys[i] 
        << " e valore: " << dict.values[i] << "\n\t";
    }
    return os;
}

// operatore di indicizzazione
template <class T>
T* Dizionario<T>::operator[](string key){
    int indice=index(key); //controlliamo validità indice
    if(indice)   return &values[key];
    // ritorniamo oggetto puntato
    else return 0;

    // comportamento classico
    // return &lista[i]; // **lista + i
}

/*

-- Uso tipico di iterator e const_iterator --

# include <vector>
using namespace std;

vector<int> v;

/// dichiarazione classica

/// esempio masochista (con const)
const vector<const int*> vector;

for(vector<const int*>::const_iterator i = v.begin(); 
i < v.end(); ++i){}

/// esempio normale (senza const)
vector<int> v1;

for(vector<int>::iterator i = v.begin(); i < v.end();
++i){}

/// con inferenza di tipo - trova il tipo lui 
/// (fa parte dello std c++11 in su)
for(auto i = v.begin(); i < v.end(); ++i) {}

/// idealmente arriviamo a questo
/// più conveniente da un punto di vista logico

for(auto i: v) {} // for range-based (C++ 17)

*/

int main(){

}