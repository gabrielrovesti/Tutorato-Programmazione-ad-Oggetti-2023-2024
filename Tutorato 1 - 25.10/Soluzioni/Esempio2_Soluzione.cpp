// COSA STAMPA IL SEGUENTE PROGRAMMA: ASSEGNAZIONE DI DEFAULT C++
#include <iostream>
using namespace std;
class Puntatore {
public:
    int* punt; // CLASSE PUNT A INT, NO COSTRUTTORI, NO OPERATORI ASS. (METODI DEFUALT ES. COSTRUTTORE DEFUALT)
};
int main() {
Puntatore x, y;
x.punt = new int(8);
y = x;
cout << "*(y.punt) = " << *(y.punt) << endl;
*(y.punt) = 3; // DATO CHE Y.PUNT PUNTA ALLA STESSA AREA DI MEM X.PUNT, ENTRAMBI AVRANNO LO STESSO VALORE
cout << "*(x.punt) = " << *(x.punt) << endl;
}
