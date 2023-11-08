// Cosa stampa?

#include <iostream>
using namespace std;

class D {
    private:
        int z;
    public:
        D(int x=0): z(x) { cout << "D01 "; }
        D(const D& a): z(a.z) { cout << "Dc "; }
};

class C {
    private:
        D d;
    public:
        C() : d(D(5)) { cout << "C0 ";}
        C(int a) : d(5) { cout << "C1 ";}
        C(const C& c) : d(c.d) { cout << "Cc ";}
};

int main() {
    C c1; // 1- CHIAMATO COSTRUTTORE DEFAULT (R.19) 2- CHIAMA COSTRUTTORE D (R.11)
    cout << "UNO" << endl; //D01 Dc C0 UNO -- POTREBBE NON STAMPARE Dc PER UN DISCORSO DI OTTIMIZZAZIONE DEI COSTRUTTORI DI COPIA
    C c2(3); // 1- CHIAMA COSTRTUTTORE C (R.20) 2- CHIAMA COSTRUTTORE D(R.11)
    cout << "DUE" << endl; // D01 C1 DUE
    C c3(c2); // 1- CHIAMA COSTRUTTORE COPIA C (R.21) 2- CHIAMA COSTRUTTORE COPIA D (R. 12)
    cout << "TRE" << endl; // Dc Cc TRE

return 0;
}