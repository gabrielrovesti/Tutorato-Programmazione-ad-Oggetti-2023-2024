// Definire un costruttore di default legale per la classe C.

class E{
    private:
    int x;
    public:
    E(int z=0): x(z) {}
};

class C{
    private:
    int z; 
    E x;
    const E e;
    E& r;
    int* const p;
    public:
    C();
};

// Alcune soluzioni possibili
// 1 - C::C(): z(0), x(0), e(0), r(x), p(new int(0)) {}
// 2 - C::C(): z(0), e(E()), r(x), p(new int(0)) {}