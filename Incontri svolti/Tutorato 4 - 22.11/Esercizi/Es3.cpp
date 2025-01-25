#include <iostream>
using namespace std;

class C{
    private:
    int i;
    protected:
    int p;
    public:
    C() {cout << "C0 ";}
    C(int x) {cout << "C1 ";}
};

class D: private C{
    private:
    int j;
    public:
    D(): C(2) {cout << "D0 ";}
    D(int x): C(x) {cout << "D1 ";}
};

class E: public C{
    private:
    D d;
    public: 
    int k;
    E(): C(6) {cout << "E0 ";}
};

class F: public D{
    protected:
    E e;
    public:
    F(): D(3.2) {cout << "F0 ";}
    F(float x) {cout << "F1 ";}
};

class G: public E{
    private:
    F f;
    C c;
    public:
    G(): E() {cout << "G0 ";}
    G(char x) {cout << "G1 ";}
};

int main(){
    G g;
}