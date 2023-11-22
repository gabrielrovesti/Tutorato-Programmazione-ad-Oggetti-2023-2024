#include "iostream"

using namespace std;

class C { 
    public: 
        void f() {cout << "C::f" << endl;}
};
class D: public C { 
    public: 
        void f() {cout << "D::f" << endl;}
};
class E: public D { 
    public:
        void f() {cout << "E::f" << endl;}
};
int main() { 
    C c; D d; E e;
    C* pc = &c; 
    E* pe = &e; 
    c = d; 
    c = e; 
    d = e; 
    //d = c;  NON COMPILA QUA - da sopra non possiamo andare sotto; il contrario è legale (costruzione per sottooggetti)
    C& rc=d; 
    D& rd=e; 
    pc->f(); // C::f
    pc = pe; 
    rd.f();  // D::f
    c.f();   // C::f
    pc->f(); // C::f
}