#include <iostream>

using namespace std;



class B {
public:
    B() {cout<<"B() ";}
	virtual ~B() {cout<<"~B() ";}
    virtual void f() {cout << "B::f "; g(); j();}
    virtual void g() const {cout <<"B::g ";}
    virtual const B* j() {cout<<"B::j " ; return this;}
    virtual void k() {cout<<"B::k "; j(); m(); }
    void m() {cout <<"B::m "; g(); j();}
    virtual B& n() { cout<<"B::n "; return *this;}
};

class C: virtual public B {
public:
	C() {cout<<"C() ";}
	~C() {cout<<"~C() ";}
	virtual void g() const override {cout << "C::g ";}
	virtual void m() {cout <<"C::m "; g(); j();}
	void k() override {cout <<"C::k "; B::n();}
	B& n() override {cout <<"C::n "; return *this; }
};


class D: virtual public B {
public:
	D() {cout<<"D() ";}
	~D(){ cout<<"~D() ";}
	virtual void g(){cout <<"D::g ";}
	const B* j() {cout <<"D::j "; return this;}
	void k() const {cout <<"D::k "; k();}
    void m() {cout<<"D::m "; g(); j(); }
};


class E: public C, public D {
public:
	E() {cout<<"E() ";}
	~E(){cout<<"~E() ";}
    virtual void g() const{cout << "E::g ";}
    const E* j(){cout<<"E::j "; return this;}
    void m() {cout <<"E::m "; g(); j();}
    D& n() final{cout <<"E::n "; return *this;}
};

class F: public E{
public:
	F() {cout<<"F() ";}
	~F() {cout<<"~F() ";}
	F (const F& x): B(x) {cout<<"Fc ";}
	void k() {cout<<"F::k "; g();}
	void m() {cout<<"F::m "; j();}
};


int main() {
    B *p1 = new E();
    B *p2 = new C();
    B *p3 = new D();
    C *p4 = new E();
    const B *p5 = new D();
    const B *p6=new E();
    const B *p7=new F();
    F f;
    cout<<endl;
//stampe
	cout<<"STAMPE"<<endl;
	F x;cout<<endl;    							//stampa B() C() D() E() F() - segue l'ordine di costruzione della gerarchia
	C *p=new F(f);cout<<endl;					//stampa C() D() E() Fc - in questo caso, crea un oggetto F di copia partendo da C, stampa questo
	
	p1->f();cout<<endl;							//stampa B::f E::g E::j
	// B::f in quanto non ha overriding sotto, la stampa di G fa match sul tipo E, essendo che 
	// in B è marcata costante (essendo tipo statico B, va bene sul const va giù)
	// permette l'overriding corretto in C, poi ancora scende e va verso E, trovando il metodo corretto
	// similmente, per j(), il nostro oggetto è tipo statico B*, quindi va bene come const B* e ritornando *this
	// non ci sono problemi, in D overriding perfetto (l'oggetto è sempre implicitamente un B)
	// poi ancora verso E, l'oggetto è in effetti un E*, stampa quello

	p1->m();cout<<endl;							//stampa B::m E::g E::j
	// m() non è ridefinito in B, quindi si prende quello; per g() e j() valgono le stesse 
	// osservazioni precisate al punto precedente

	//(p1->j())->k(); 							//NON COMPILA "error: passing ‘const B’ as ‘this’ argument discards qualifiers"
	// come si vede, si ha un const B* come tipo di ritorno di j();
	// il problema è che ci sta "return this", ma è costante; successivamente, prendiamo
	// l'oggetto dereferenziato (con ->) su k(), che non è const;
	// quindi, non compila: o mettiamo il metodo k() const oppure togliamo con const_cast
	
	(dynamic_cast<const F*>(p1->j()))->g();		//RUNTIME ERROR

	// in questo caso, stampa E::j eseguendolo, dato che il dynamic_cast prende l'oggetto di tipo B
	// e converte verso il basso, questa andrebbe bene senza problemi.
	// di fatto, però, quando si va ad invocare "g", se eseguite, vedete che "ci pensa"
	// (attende un po') e poi non stampa nulla; questo è dovuto al fatto che, in realtà,
	// l'oggetto è un E*, ma il tipo statico è B*; quindi, quando si va a fare l'invocazione
	// di g(), si va a cercare il metodo g() in B, che è marcato const;
	// fatto sta che F discende da E, similmente da C e da D che offrono metodi simili
	// e con overriding corretto; quindi, questo provoca in fase di stampa un errore di runtime
	// (comportamente non definito), in quanto può chiamare potenzialmente qualsiasi metodo
	// tra quelli offerti da E, C e D, ma non sa quale prendere (non è definito per const F*)

	p2->f();cout<<endl;							//stampa B::f C::g B::j
	// B::f in quanto non ha overriding sotto, la stampa di G fa match sul tipo C, essendo che
	// il tipo dinamico è C, quindi il const override va sotto, per j() non abbiamo un overriding in
	// C, quindi va a prendere quello di B, che ritorna this, quindi va bene

	p2->m();cout<<endl;							//stampa B::m C::g
	// m() non è ridefinito in C, quindi si prende quello di B; per g(), fa overriding corretto
	// in C, essendo che override ridefinisce correttamente per la sottoclasse e se lo prende

	(p2->j())->g();cout<<endl;					//stampa B::j C::g
	// j() non è ridefinito in C, quindi si prende quello di B; per g(), fa overriding corretto

	p3->f();cout<<endl;							//stampa B::f B::g D::j
	// B::f in quanto non ha overriding sotto in D, la stampa di g() non fa overriding giusto su D
	// perché non è const, quindi va a prendere quello di B, per j() sappiamo che l'oggetto è sempre di tipo B
	// quindi essendo virtuale in B, va a prendersi quello in D (dato che il tipo statico è B*)

	p3->k();cout<<endl;							//stampa B::k D::j B::m B::g D::j
	// k() non è ridefinito in D, quindi si prende quello di B; per j(), sappiamo che l'oggetto è sempre di tipo B
	// quindi essendo virtuale in B, va a prendersi quello in D (dato che il tipo statico è B*)
	// per m(), non è ridefinito in D, quindi si prende quello di B; per g(), non ha overriding in D corretto
	// per il const, poi per j() è un metodo correttamente ridefinito in D e prende quello

	(p3->n()).m();cout<<endl;					//B::n B::m B::g D::j
	// non abbiamo n() in D, prendiamo B, per m() non ci sta il virtual, per g() non ha overriding corretto in D
	// per il const, poi per j() è un metodo correttamente ridefinito in D e prende quello

	(dynamic_cast<D&>(p3->n())).g();cout<<endl; //stampa B::n D::g
	// il cast va bene verso D per l'espressione, quindi essendo che è tipo statico B/tipo dinamico D
	// mentre per g() prendiamo il solito in D per l'overriding corretto
	
	p4->f();cout<<endl;							//stampa B::f E::g E::j
	// sta tra C ed E, ma non essendo presente in C od E, prende quello di B;
	// per g() e j() fa overriding corretto in E, essendo che nel primo caso è marcato const, 
	// nel secondo "l'oggetto è un B (tipo statico) ma anche un E (tipo dinamico)", 
	// quindi va a prendere quello di E con match su const

	p4->k();cout<<endl;							//stampa C::k B::n
	// k() è ridefinito in C, quindi prende quello, essendo virtuale sopra e override prende quello non essendo sotto; 
	// per n() si ha semplicemente lo scoping

	(p4->n()).m();cout<<endl;					//stampa E::n B::m E::g E::j
	// la parola "final" previene di andare giù ancora dopo E (vieta gli overriding "ulteriori dopo E")
	// ma qui fa match perfetto per overriding, mentre m() non ha virtual
	// gli altri vengono correttamente ridefiniti

	//(p5->n()).g();cout<<endl;					//NON COMPILA "error: passing ‘const B’ as ‘this’ argument discards qualifiers"
	// l'errore è dato da avere const B e il fatto di avere alla base virtual B& n che ritorna un this;
	// andrebbe se togliamo il const (come capita tra due stampe) oppure marcando const virtual B& n() const

	//(dynamic_cast<E*>(p6))->j();cout<<endl;		//NON COMPILA "cannot dynamic_cast ‘p6’ (of type ‘const class B*’) to type ‘class E*’"
	// il problema è che p6 è const B*, quindi quando proviamo a fare j(), ritornando this
	// e avendolo costante, non fa match con il tipo e non compila

	(dynamic_cast<C*>(const_cast<B*>(p7)))->k();cout<<endl; //stampa F::k E::g
	// il const_cast toglie il const da B, quindi abbiamo un C* e va bene il dynamic_cast
	// su p7, che quindi diventa tra C ed F; override lo fa andare verso F, dove ci sta l'overriding
	// per g(), non è presente in E, quindi essendo overriding corretto rispetto a C, scende in E e stampa quello

	delete p7;cout<<endl;						//stampa ~F() ~E() ~D() ~C() ~B()
	// stampa delle distruzioni al contrario delle costruzioni (già commentaye), da cui questo
	cout<<"FINE STAMPE"<<endl;
	    
}