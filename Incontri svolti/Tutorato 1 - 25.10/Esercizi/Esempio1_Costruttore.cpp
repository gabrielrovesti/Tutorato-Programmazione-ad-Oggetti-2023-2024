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
        C(): x(z), e(r), p(0);
};