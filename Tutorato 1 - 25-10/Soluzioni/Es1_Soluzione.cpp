#include <iostream>

using namespace std;

class C{
    private:
    int x;

    public:
    C(int n = 0) {x = n;}
    C F(C obj) {C r; r.x = obj.x + x; return r;}
    C G(C obj) const {C r; r.x = obj.x + x; return r;} 
    C H(C& obj) {obj.x += x; return obj;} 
    C I(const C& obj) {C r; r.x = obj.x + x; return r;} 
    C J(const C& obj) const {C r; r.x = obj.x + x; return r;}

};

  int main() { 
        C x, y(1), z(2); const C v(2); 

        z=x.F(y); // (1) - compila
        v.F(y); // (2) - error: passing 'const C' as 'this' argument discards qualifiers [-fpermissive]
        v.G(y); // (3) - compila
        (v.G(y)).F(x); // (4) - compila
        (v.G(y)).G(x); // (5) - compila
        x.H(v) ; // (6) - error: binding reference of type ‘C&’ to ‘const C’ discards qualifiers
        x.H(z.G(y)); // (7) - error: cannot bind non-const lvalue reference of type ‘C&’ to an rvalue of type ‘C’
        x.I(z.G(y)); // (8) - compila
        x.J(z.G(y)); // (9) - compila
        v.J(z.G(y)); // (10) - compila

        return 0;
    }