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
    C c1;
    cout << "UNO" << endl;
    C c2(3);
    cout << "DUE" << endl;
    C c3(c2);
    cout << "TRE" << endl;

return 0;
}