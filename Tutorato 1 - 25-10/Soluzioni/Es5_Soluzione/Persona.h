#include <string>
#include <iostream>

class Persona {
public:
    Persona(const std::string& nome, int annoNascita, int annoMorte);
    
    std::string getNome() const;
    int getAnnoNascita() const;
    int getAnnoMorte() const;
    
private:
    std::string nome;
    int annoNascita;
    int annoMorte;
};

// Dichiarazione della funzione esterna di overloading dell'operatore di output
std::ostream& operator<<(std::ostream& os, const Persona& persona);
