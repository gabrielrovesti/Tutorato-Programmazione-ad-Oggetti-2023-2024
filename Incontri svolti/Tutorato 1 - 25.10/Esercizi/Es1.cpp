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

    int main() { 
        C x, y(1) , z(2) ; const C v(2); 

        z=x.F(y); // (1)
        v.F(y); // (2)
        v.G(y); // (3)
        (v.G(y)).F(x); // (4)
        (v.G(y)).G(x); // (5)
        x.H(v) ; // (6)
        x.H(z.G(y)); // (7)
        x.I(z.G(y)); // (8)
        x.J(z.G(y)); // (9)
        v.J(z.G(y)); // (10)

    return 0;
    }
};