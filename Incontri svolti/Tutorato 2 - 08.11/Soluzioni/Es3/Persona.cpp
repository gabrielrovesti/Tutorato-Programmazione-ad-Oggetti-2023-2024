/*Definire una classe "Persona" i cui oggetto rappresentano
anagraficamente un personaggio storico caratterizato da nome, anno di nascita
e anno di morte.
Includere opportuni costruttori, metodi di accesso ai campi
ed overloading dell'operatore di output come funzione esterna.
Separare interfaccia ed implementazione della classe.
Si definisca inoltre un esempio di metodo main() che usa tutti i metodi
della classe e l'operatore di output.*/

#include <iostream>
#include "Persona.h"

Persona::Persona(const std::string& name, int n, int m): nome(name), anno_nascita(n), anno_morte(m) {}

std::string Persona::getNome() const{
    return nome;
}

int Persona::getNascita() const{
    return anno_nascita;
}

int Persona::getMorte() const{
    return anno_morte;
}

std::ostream& operator<<(std::ostream& os, const Persona &p){
    return os <<"Nome"<<p.nome<<"Data di nascita: "<<p.anno_nascita<<">Data di morte: "<<p.anno_morte;
}


int main(){
    std::string tommy("tommy");
    Persona p1("Mario", 1980, 2010);

    return 0;
}