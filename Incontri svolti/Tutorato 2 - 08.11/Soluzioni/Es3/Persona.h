/*Definire una classe "Persona" i cui oggetto rappresentano
anagraficamente un personaggio storico caratterizato da nome, anno di nascita
e anno di morte.
Includere opportuni costruttori, metodi di accesso ai campi
ed overloading dell'operatore di output come funzione esterna.
Separare interfaccia ed implementazione della classe.
Si definisca inoltre un esempio di metodo main() che usa tutti i metodi
della classe e l'operatore di output.*/

#ifndef PERSONA_H
#define PERSONA_H
#include <iostream>

class Persona{
    public:
    explicit Persona(const std::string& nome="", int n=0, int m=0);
    int getNascita() const;
    int getMorte() const;
    std::string getNome() const;
    friend std::ostream& operator <<(std::ostream& os, const Persona&);

    private:
    std::string nome;
    int anno_nascita, anno_morte;
};

#endif