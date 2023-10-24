 #include<iostream>
 using std::cout;
 class A {
 private:
    int x;
 public:
    A(int k = 5): x(k) {cout << k << " A01 ";}
    A(const A& a): x(a.x) {cout << "Ac ";}
    A g() const {return *this;}
 };

 class B {
 private:
    A ar[2];
    static A a;
 public:
    B() {ar[1] = A(7); cout << "B0 ";}
    B(const B& b) {cout << "Bc ";}
 };
 A B::a = A(9);

 A Fun(A* p, const A& a, B b) {
    *p = a;
    a.g();
    return *p;
 };
 int main() {
    cout << "ZERO\n";
    A a1; cout << "UNO\n";
    A a2(3); cout << "DUE\n";
    A* p = &a1; cout << "TRE\n";
    B b; cout << "QUATTRO\n";
    a1 = Fun(p,a2,b); cout << "CINQUE\n";
    A a3 = Fun(&a1,*p,b); cout << "SEI";
 }

 /*
    9 A01 ZERO
    5 A01 UNO
    3 A01 DUE
    TRE
    5 A01 5 A01 7 A01 B0 QUATTRO
    5 A01 5 A01 Bc Ac Ac CINQUE
    5 A01 5 A01 Bc Ac Ac SEI
 */