#include <iostream>

using namespace std;

class A{
    public:
    virtual ~A() =0;
};

A::~A()=default;

class B: public A{
    public:
        ~B()=default;
};
class C: virtual public B{};
class D: virtual public B{};
class E: public C, public D{};


int fun(const A& x, B* y){
    A* p=const_cast<B*>(dynamic_cast<const B*>(&x));
    auto q=dynamic_cast<const C*>(&x);

    if(dynamic_cast<E*>(y)){
        if(!p || q) return 1;
        else return 2;
    }

    if(dynamic_cast<C*>(y)) return 3;
    if(q) return 4;
    if(p && typeid(*p)!=typeid(D)) return 5;

    return 6;

}

B b; C c; D d; E e;

int main()
{
    //6544233241
    std::cout<<fun(d,&d)<<fun(b,&d)<<fun(c,&d)<<fun(e,&d)
    <<fun(d,&e)<<fun(c,&c)<<fun(e,&c)<<fun(b,&e)<<fun(c,&b)<<fun(c,&e);
}
/*

Spiegazione stampe:

- 6 = Sappiamo che deve stampare questo numero e non entriamo nelle altre
due condizioni. Le prime due righe dicono:
- *p è un B
- q è un const C*

Sappiamo che:
- non entra nell'if quindi, "y" non può essere di tipo E
- non entra nel successivo if, quindi "y" non può essere di tipo C
- non entra in if(q); il motivo per cui non succede è che 
"x", la variabile a cui si riferisce "x"
 è un A costante, mentre noi vogliamo entrare se siamo un const C*;
 questo succede solo se siamo un sottotipo di C o C stesso, così facendo siamo un
 C costante
- i successivi if dicono che "p" non è un B e può essere di tipo D

una possibile stampa può essere (d, &d) date tutte le considerazioni

- 5 = valgono le considerazioni di prima, ma entriamo nell'if;
qusto significa che "p" è un b e il suo tipo non è esattamente d, quindi può sia B che E
per quanto riguarda "y", sappiamo dagli if che non può essere né "C" né "E", quindi
può essere di tipo D

- 4 = In questo caso, entriamo nell'if di "q", riferito ad "x", quindi
vuol dire che siamo a tutti gli effetti un "c" per il primo parametro
Similmente per "y", non siamo né C né E, quindi può essere ad esempio di tipo D

- 4 = Per ridare 4 devono valere le stesse condizioni;
nello specifico, significa che per entrare nell'if per "q", per le considerazioni
descritte sopra, siamo un C o un sottotipo di C (dato che deve essere const C* e per ereditarietà questo vale)
Di fatto, quindi, ci prendiamo direttamente (e, &d)

- 2 - Questa volta entriamo nell'if per "y", quindi il secondo parametro
sarà di tipo "e", mentre per quanto riguarda il primo, sappiamo che p vale, quindi
npn può essere di tipo B il primo parametro,, ma neanche di tipo C per l'altra parte della condizione.
Possiamo quindi mettere (d, &e) (va bene anche b, &e)

- 3 - Per stampare "3", siamo sicuri che "y" sia di tipo C, mentre per quanto riguarda X
possiamo affermare che valgano le prime due assegnazioni su "p" e su "q", che dicono rispettivamente
possa essere un B costante oppure un C costante (quindi, può essere esattamente quel tipo o uno dei sottotipi).
Per questo stampiamo (c, &c)

- 3 - Prendiamo per certo "c" per "y", per "x" prendiamo uno dei sottotipi di C, va bene per quanto scritto

- 2 - Sappiamo che entra nell'if per "y", quindi quello sarà di tipo E,
mentre fallisce il primo if innestato, quindi vuol dire che "q" è di tipo B (o sottotipo come E)
e non può essere di tipo C
Per questo, stampa (b, e)

- 4 - Per quanto riguarda questa, sappiamo che "y" non può essere un E e che non può essere C
Sappiamo quindi che basta non essere quel tipo per "y", quindi possiamo mettere ad esempio "B", tipo del parametro "y" passato
e poi un C/E per il primo parametro

- 1: Per entrare nell'if, il secondo parametro deve essere di tipo "e".
Poi, abbiamo le due condizioni, che entrambi non valgono:
- !p specifica che "x", quindi per "p", non sia un B (dato che const B* da cui viene tolto il const)
- q specifica che il parametro "x" deve essere di tipo "const C*".
Stampa corretta: c, &e

*/