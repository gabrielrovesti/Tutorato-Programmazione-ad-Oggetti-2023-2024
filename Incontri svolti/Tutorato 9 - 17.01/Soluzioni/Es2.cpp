#include <iostream>

using namespace std;

class B{
    public:
    B() {cout << " B() ";}
    virtual ~B() {cout << " ~B() ";}
    virtual void f() {cout << " B::f() "; g(); j();}
    virtual void g() const {cout << " B::g() ";}
    virtual const B* j() {cout << " B::j() "; return this;}
    virtual void k() {cout << " B::k() "; j(); m();}
    void m() {cout << " B::m() "; g(); j();}
    virtual B& n() {cout << " B::n() "; return *this;}
};

class C: virtual public B{
    public:
    C() {cout << " C() ";}
    ~C() {cout << " ~C() ";}
    virtual void g() const override {cout << " C::g() ";}
    void k() override {cout << " C::k() "; j(); m();}
    virtual void m() {cout << " C::m() "; g(); j();}
    B& n() override {cout << " C::n() "; return *this;}
};

class D: virtual public B{
    public:
    D() {cout << " D() ";}
    ~D() {cout << " ~D() ";}
    virtual void g() {cout << " D::g() ";}
    const B* j() {cout << " D::j() "; return this;}
    void k() const {cout << " D::k() "; k();}
    void m() {cout << " D::m() "; g(); j();}
};

class E: public C, public D{
    public:
    E() {cout << " E() ";}
    ~E() {cout << " ~E() ";}
    virtual void g() const {cout << " E::g() ";}
    const E* j() {cout << " E::j() "; return this;}
    void m() {cout << " E::m() "; g(); j();}
    D& n() final {cout << " E::n() "; return *this;}
};

class F: public E{
    public:
    F() {cout << " F() ";}
    ~F() {cout << " ~F() ";}
    F(const F& x): B(x) {cout << " Fc ";}
    void k() {cout << " F::k() "; g(); }
    void m() {cout << " F::m() "; j();}
};  

B* p1 = new E(); B* p2 = new C(); B* p3 = new D(); C* p4 = new E();
const B* p5 = new D(); const B* p6 = new E(); const B* p7 = new F(); F f;

int main(){
    cout << "1: " << endl;  C* ptr = new F(f); 
    cout << "2: " << endl; p1->m(); 
    //(p1->j())->k(); error: passing 'const B' as 'this' argument discards qualifiers [-fpermissive]
    cout << "4: " << endl; (dynamic_cast<const F*>(p1->j()))->g();
    cout << "5: " << endl; p2->m();
    cout << "6: " << endl; (p2->j())->g();
    cout << "7: " << endl; p3->k();
    cout << "8: " << endl; (p3->n()).m();
    cout << "9: " << endl; (dynamic_cast<D&>(p3->n())).g(); 
    cout << "10: " << endl; p4->f(); 
    cout << "11: " << endl; p4->k(); 
    cout << "12: " <<  endl; (p4->n()).m(); 
    //(p5->n()).g(); error: passing 'const B' as 'this' argument discards qualifiers [-fpermissive]
    //(dynamic_cast<E*>(p6))->j(); error: cannot 'dynamic_cast' 'p6' (of type 'const class B*') to type 'class E*' (conversion casts away constness)
    cout << "15: " << endl; (dynamic_cast<C*>(const_cast<B*>(p7)))->k(); 
    cout << "16: " << endl; delete p7;
}

/*
1) C()  D()  E()  Fc 
2) B::m()  E::g()  E::j() 
3) Non compila 
4) UB - Darebbe E::j() ma poi dà errore dovuto al const
5) B::m()  C::g()  B::j()
6) B::j()  C::g()
7) B::k()  D::j()  B::m()  B::g()  D::j()
8) B::n()  B::m()  B::g()  D::j()
9) B::n()  D::g()
10) B::f()  E::g()  E::j()
11) C::k() B::n()
12) E::n()  B::m()  E::g()  E::j()
13) Non compila
14) Non compila
15) F::k()  E::g()
16) ~F()  ~E()  ~D()  ~C()  ~B()
*/