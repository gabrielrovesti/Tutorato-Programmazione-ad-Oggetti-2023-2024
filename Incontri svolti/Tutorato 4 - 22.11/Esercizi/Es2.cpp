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
    d = c; 
    C& rc=d; 
    D& rd=e; 
    pc->f(); 
    pc = pe; 
    rd.f();  
    c.f();   
    pc->f(); 
}