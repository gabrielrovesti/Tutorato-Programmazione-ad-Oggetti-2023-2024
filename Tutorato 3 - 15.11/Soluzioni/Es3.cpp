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

/*
Il fatto che compili dipende essenzialmente dal tipo:
- tu puoi vedere che <char> per la classe D
- la classe C prende le invocazioni dei metodi
- puoi vedere che C è friend della classe T1; quindi, se i tipi di T1 fanno match con C, compila

Tu hai il fatto di "char" che deve compilare a seconda dei due tipi con cui viene chiamata fun. Quindi, compila se <T> o <char> è il primo parametro, mentre se è un tipo diverso, non va.

Esempio: 
<T, T> - compila, perché char va sempre bene per T, a prescindere dal secondo parametro
<int, T> - non compila, perché char non è di tipo int ed essendo tipo diverso non fanno match
<T, int> - compila, stesso motivo della prima
<int, int> - non compila, stesso motivo di <int, T>
<int, double> - non compila, stesso motivo di <int, T>
<char, double> - compila, fa match con char
*/