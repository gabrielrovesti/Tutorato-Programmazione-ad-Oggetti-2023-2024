#include "orario.h"

orario::orario() {sec=0;}      //COSTRUTTORE DEFAULT

orario::orario(int o)          //COSTRUTTORE AD UN PARAMETRO
{
    if(o<0 || o>23) sec=0;
    else sec=o*3600;
}

orario::orario(int o, int m)    //COSTRUTTORE A DUE PARAMENTRI
{
    if(o<0 || o>23 || m<0 || m>59) sec=0;
    else sec=o*3600+m*60;
}

orario::orario(int o, int m, int s)     //COSTRUTTORE A DUE PARAMENTRI
{
    if(o<0 || o>23 || m<0 || m>59 || s<0 || s>59)
        sec=0;
    else sec=o*3600+m*60+s;
}

int orario::Ore() const {return sec/3600;}      //RITORNA ORE
int orario::Minuti() const {return (sec/60)%60;}    //RITORNA MINUTI
int orario::Secondi() const {return sec%60;}        //RITORNA SECONDI

orario orario::UnOraPiuTardi() const    //RITORNA UN ORA PIÙ TARDI
{
    orario aux;
    aux.sec=(sec+3600)%86400;
    return aux;
}

void orario::AvanzaUnOra() {sec=(sec+3600)%86400;}      //AVANZA L'ORARIO DI UN ORA

void orario::StampaSecondi() const {cout<<sec<<endl;}   //STAMPA SECONDI

orario orario::OraDiPranzo() {return orario(13, 15);}   //RITORNA L'ORA DI PRANZO PRESTABILITA

orario orario::operator+(orario o)      //OPERATORE +
{
    orario aux;
    aux.sec=(sec+o.sec)%86400;
    return aux;
}

orario orario::operator-(orario o)      //OPERATORE -
{
    orario aux;
    aux.sec=(sec-o.sec)%86400;
    return aux;
}

bool orario::operator==(const orario& o)    //OPRATORE ==
{
    if(sec==o.sec)
        return true;
    else
        return false;
}

bool orario::operator>(orario o)        //OPERATORE >
{
    if(sec>o.sec)
        return true;
    else
        return false;
}

bool orario::operator<(orario o)    //OPERATORE <
{
    if(sec<o.sec)
        return true;
    else
        return false;
}

ostream& operator<<(ostream& os, const orario& o)   //OPERATORE <<
{
    return os<<o.Ore()<<':'<<o.Minuti()<<':'<<o.Secondi();
}
