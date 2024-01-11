#include <iostream>
using namespace std;

class C{
    private:
    int i;
    protected:
    int p;
    public:
    C() {cout << "C0 ";}
    C(int x) {cout << "C1 ";}
};

class D: private C{
    private:
    int j;
    public:
    D(): C(2) {cout << "D0 ";}
    D(int x): C(x) {cout << "D1 ";}
};

class E: public C{
    private:
    D d;
    public: 
    int k;
    E(): C(6) {cout << "E0 ";}
};

class F: public D{
    protected:
    E e;
    public:
    F(): D(3.2) {cout << "F0 ";}
    F(float x) {cout << "F1 ";}
};

class G: public E{
    private:
    F f;
    C c;
    public:
    G(): E() {cout << "G0 ";}
    G(char x) {cout << "G1 ";}
};

int main(){
    G g;
}

/*
Motivo della stampa passo passo (partendo dalla fine):

- Il G deve costruire oggetti di tipo C ed F che sono i campi della classe (quindi stampa F0, C0) e in ultimo il proprio G0

- La classe G ha un campo di tipo E che viene costruito; questo è un E, che ha anche un D (D0), che viene costruito; sia D che E vengono costruiti con un C (C(2) e C(6), da cui i due C1 C1 prima di D0 ed E0 che vengono costruiti con quelli

- Sullo stesso livello c'è D, che viene costruito con un C (C(1), quindi avrà C1 D1

- le prime stampe sono date dal fatto di dover costruire, come detto, i campi di default delle classi, quindi siccome sullo stesso livello della gerarchia abbiamo E, prendiamo anche i campi necessari per costruire quella, quindi il campo D, che è anche un C e viene stampato un C1, quindi costruisce un oggetto di tipo D (D0) che ha bisogno ache di un C (C1) e quindi il default di E (E0)
*/

/*
C1 C1 D0 E0 C1 D1 C1 C1 D0 E0 F0 C0 G0 

Motivo della stampa doppia di "C1"
Per costruire le variabili di una classe base, serve:
1) Costruire uno spazio in memoria per creare l'oggetto di tipo C
2) Costruire il C effettivo 
Per costruire lo spazio in memoria, serve un temporaneo anonimo, che successivamente verrà gettato via. 

Questo accade il primo giro (per tutte le sottoclassi), dato che sia D che E vengono costruite con un C;
successivamente, costruisce gli oggetti finali, scendendo nelle sottoclassi e infine gli oggetti di G.

Più dettagliatamente:
1 -Stampa due volte C1 perché D e F ereditano privatamente da C, quindi non possono accedere al costruttore di C.
Di conseguenza, il costruttore di D e F chiama il costruttore di C con un argomento, che è C1.
2 - Stampa D0 per ordine di costruzione dentro la classe E, dove viene visto D
3 - Stampa C1 per il costruttore di E
4 - Stampa D1 per permettere la costruzione di F
5 - Stampa C1 per il costruttore di F, che richiede un D, il quale viene costruito di nuovo con un C
6 - Stampa C0 per il costruttore di G, che richiede un E, il quale richiede un C, che viene costruito con C0
7 - Infine, stampa G0 per il costruttore di G
*/

