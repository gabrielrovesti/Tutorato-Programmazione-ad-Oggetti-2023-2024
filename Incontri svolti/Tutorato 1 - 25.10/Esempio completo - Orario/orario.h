#ifndef ORARIO_H
#define ORARIO_H
#include <iostream>
using namespace std;

// Separazione interfaccia (.h/definizione nome metodi e variabili)
// da costruzione (.cpp - definizione corpo metodi)
class orario
{
    private:
        int sec;
    public:
        int Ore() const;
        int Minuti() const;
        int Secondi() const;
        orario();
        orario(int);
        orario(int, int);
        orario(int, int, int);
        
        orario UnOraPiuTardi() const;
        void AvanzaUnOra();
        void StampaSecondi() const;
        static orario OraDiPranzo();
        orario operator+(orario);
};

ostream& operator<<(ostream& os, const orario& o);

#endif // ORARIO_H
