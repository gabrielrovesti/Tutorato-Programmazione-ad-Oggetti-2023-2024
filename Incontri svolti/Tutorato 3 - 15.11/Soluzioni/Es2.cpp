#include <iostream>
#include <string>


template <class T>
class C{
    template <class V>
    friend void fun(C<V>);
    private:
        T x;
    public:
        C(T y): x(y) {}
};

template<class T>
void fun(C<T> t){
    cout << t.x < " ";
    C<double> c(3.1);
    cout << c.x << endl;
}

int main(){
    C<int> c(4);
    C<std::string> s("blob");
    fun(c);
    fun(s);
}

/*
Stampa: 4 3.1 - istanziazione implicita fun<int>
Stampa: blob 3.1 - istanzazione implicita fun<string>
*/

/*
Sostituisci l'int e quindi diventa (4), poi subito dopo hai C<double> che nuovamente va la stessa chiamata e il template <T> diventa t.x (4) e c.x (altra variabile sostituita con 3.1) e infatti è 4 (prima sostituisci "int") e poi 3.1 (perché <double> è <T>)

La class V semplicemente dice "ti faccio vedere i campi privati di C", quindi il tipo sottostante "int/string" semplicemente sostituisce quel tipo e permette la chiamata della funzione con il semplice "fun"

Appunto:
- c<int> c(4) -> stampa 4 essendo che sostituisce il template
- c.x (è c<double> e stampa 3.1)

Successivamente:
- t.x (diventa <string> e quindi stampa "blob"
- c.x (diventa <double> e nuovamente 3.1)
*/