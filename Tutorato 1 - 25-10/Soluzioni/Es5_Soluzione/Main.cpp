#include <iostream>
#include "persona.h"

int main() {
    Persona personaggio("Leonardo da Vinci", 1452, 1519);

    std::cout << "Informazioni sul personaggio storico:\n" << personaggio;

    return 0;
}
