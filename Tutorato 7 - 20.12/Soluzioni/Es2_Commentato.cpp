class E: virtual public B{
    public: 
    Z ez;
    // assegnazione standard
    E& operator=(const E& e){
        // standard
        B::operator=(e);
        ez = e.ez;
        return *this;
    }
};

class F: public D, public E{
    private:
    Z *fz;
    public:
    F(const F& f): D(f), E(f), 
    fz(new F*(this)) {}

    ~F(){
        if(fz) delete fz;
    }

    virtual F* clone() {
        return new F(*this);
    }
};

