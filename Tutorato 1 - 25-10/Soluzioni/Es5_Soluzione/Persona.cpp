#include "persona.h"

Persona::Persona(const std::string& nome, int annoNascita, int annoMorte)
    : nome(nome), annoNascita(annoNascita), annoMorte(annoMorte) {}

std::string Persona::getNome() const {
    return nome;
}

int Persona::getAnnoNascita() const {
    return annoNascita;
}

int Persona::getAnnoMorte() const {
    return annoMorte;
}

// Implementazione dell'operatore di output
std::ostream& operator<<(std::ostream& os, const Persona& persona) {
    os << "Nome: " << persona.getNome() << "\nAnno di nascita: " << persona.getAnnoNascita()
       << "\nAnno di morte: " << persona.getAnnoMorte() << std::endl;
    return os;
}
