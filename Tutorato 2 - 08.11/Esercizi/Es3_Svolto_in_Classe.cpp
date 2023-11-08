/*Definire una classe 'Persona' i cui oggetti rappresentano anagraficamente un
personaggio storico caratterizzato da nome, anno dI nascita e anno di morte.
Includere opportuni costruttori, metodi di accesso ai campi e l'overloading
dell'operatore di output come funzione esterna. Separare interfaccia ed
implementazione della classe.
Si definisca inoltre un esempio al metodo 'main() che usa tutti i metodi della
classe e l'operatore di output. */

#include <string>

using namespace std;
class Persona{
private:
    std::string nome;
    int annoNascita;
    int annoMorte;

    public:
    //opportuni costruttori
    Persona(std::string n, int aN, int aM): nome(n), annoNascita(aN), annoMorte(aM) {}

    //metodi di accesso ai campi
    std::string getNome() const{return nome;}
    int getNascita() const{return annoNascita;}
    int getMorte() const{return annoMorte;}

    //metodo di impostazione = uguale a fare i costruttori
    /*
        void setNome(string n){
        nome = n; //logica di base (problema = è privato)
        Persona p; //logica comune - definisco l'oggetto e gli assegno il campo
        p.getNome()=n;
    }
    */

   //Separazione interfaccia da implementazione = file separato .h (definizioni) / file separato .cpp metodi
   //file.h --> definiamo il metodo std::string getNome() const;
   //file .cpp --> definiamo il corpo del metodo
   // #include <Persona.h> Persona std::string getNome() const{return nome;}

   //Operatore di output - tipo di ritorno (ostream = flusso di output)

   ostream& operator<<(ostream& os, const Persona& p); 
};

Persona::ostream& operator<<(ostream& os, const Persona& p){
    os << p.getNome() << p.getNascita() << p.getMorte() << endl;
    // cout << variabile.campo1 << variabile.campo2;
}

