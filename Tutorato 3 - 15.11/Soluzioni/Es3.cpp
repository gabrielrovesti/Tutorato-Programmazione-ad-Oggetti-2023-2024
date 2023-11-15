//dichiarazione incompleta
template<class T> class D;

template<class T1, class T2>
class C{
    //amicizia associata
    friend class D<T1>;
    private;
    T1 t1; T2 t2;
};

template <class T>
class D{
    public:
        void m(){C<T, T> c;
            cout << c.t1 << c.t2;
        }
        void n(){C<Tint, T> c;
            cout << c.t1 << c.t2;
        }
        void o(){C<T, int> c;
            cout << c.t1 << c.t2;
        }
        void p(){C<int, int> c;
            cout << c.t1 << c.t2;
        }
        void q(){C<int, double> c;
            cout << c.t1 << c.t2;
        }
        void r(){C<char, double> c;
            cout << c.t1 << c.t2;
        }
};

int main(){
    D<char> d; d.m();
    D<char> d; d.n();
    D<char> d; d.o();
    D<char> d; d.p();
    D<char> d; d.q();
    D<char> d; d.r();
}

/*
Compila
Non compila
Compila
Non compila
Non compila
Compila
*/
