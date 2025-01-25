#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;
 
template<class Functor>
vector<int> find_template(const vector<int>& v, Functor t) {
    vector<int> r;
    for(auto it = v.begin(); it != v.end(); it++) {
        if(t(*it))
            r.push_back(*it);
        
    }
    return r;
}
 
unsigned int find_1(const vector<int>& v, int k) {
    vector<int> w = find_template(v, [v,k] (int n) {return n>k;} );
    return w.size();
}
 
vector<int> find_2(const vector<int>& v) {
    cout<<"dim"<<v.size()<<endl;
    return find_template(v, [v] (int n) {return n<v.size();});
}
 
int main() {
    vector<int> v1 = {3,6,4,6,2,5,-2,4,2}; 
    vector<int> v2 = {-2,-6,4,4,2,5,0,4,2,3,2,0};
 
    cout << find_1(v1, 2); cout << endl; //6 --> tutti gli elementi più grandi di 2 (tolti gli unsigned e quindi i negativi)
    cout << find_1(v2, 2); cout << endl; //5 --> tutti gli elementi più grandi di 2
    cout << find_2(v1).size(); cout << endl; //dim9 8
    cout << find_2(v2).size(); cout << endl; //dim12 10
    //di fatto, le due funzioni non considerano i negativi perché non sono unsigned
    //find_1 considera gli elementi maggiori di k, find_2 considera gli elementi minori di v.size()
    //e i negativi fanno fallire la condizione.
    /*
    Il problema è che, in questo codice, la dimensione del vettore è ottenuta tramite v.size() e la dimensione di un vettore è sempre un valore non negativo. Pertanto, quando n è un numero negativo, l'espressione n < v.size() avrà sempre valore falso.
    */
}

/*
La riga vector<int> w = find_template(v, [v,k] (int n) {return n>k;} ); 
utilizza un'espressione lambda del C++11 per creare un funtore anonimo 
(una classe con un operatore() overloaded) che viene passato alla funzione find_template 
come secondo argomento.

L'espressione lambda [v,k] (int n) {ritorno n>k;} prende due catture v e k, 
che sono rispettivamente gli argomenti const vector<int>& e int passati alla 
funzione find_1. L'espressione lambda prende un argomento int n e restituisce n > k, 
il che significa che la lambda sta verificando se l'argomento int dato è maggiore 
dell'argomento int k.

La funzione find_template prende come argomenti 
un const vector<int>& e un Functor e restituisce un vettore<int> 
contenente tutti gli elementi del vettore di input per i quali il functor restituisce true.
In questo caso, il funtore è l'espressione lambda definita in precedenza, 
quindi la funzione find_template restituisce un vettore<int> contenente 
tutti gli elementi di v che sono maggiori di k.

Quindi, la riga vector<int> w = find_template(v, [v,k] (int n) {return n>k;} ); utilizza 
la funzione find_template per trovare tutti gli elementi di v che 
sono maggiori di k e memorizza il risultato in w.

*/

/*
La funzione lambda prende un argomento, 
"n", che è ogni elemento del vettore "v", 
mentre il ciclo all'interno di "find_template" itera 
attraverso gli elementi di "v". Lo scopo della funzione 
lambda è definire la condizione da verificare per ogni elemento 
del vettore, ovvero se l'elemento è maggiore di "k" (nel primo caso, k è uguale a 2). 
Se la condizione è vera, l'elemento corrente di "v" viene aggiunto al vettore "r" 
all'interno di "find_template". Infine, la dimensione del vettore "r" 
viene restituita dalla funzione "find_template" e assegnata alla 
variabile "w", che viene poi utilizzata per produrre il risultato 
nella riga "cout << find_1(v1, 2); cout << endl;".

*/
