#include<iostream>
using namespace std;

class A {
	bool x;
	public:
	virtual ~A() = default;
};

class B {
	bool y;
	public:
	virtual void f() const { cout << "B::f "; }
};

class C: public A {};

class D: public B {
	public:
	void f() const { cout << "D::f "; }
};

class E: public D {
	public:
	void f() const { cout << "E::f "; }
};

template<class T>
void Fun(const T& ref) {
	try{ throw ref; }
		catch(const C& c) {cout << "C ";}
		catch(const E& e) {cout << "E "; e.f();}
		catch(const B& b) {cout << "B "; b.f();}
		catch(const A& a) {cout << "A ";}
		catch(const D& d) {cout << "D ";}
		catch(...) {cout << "GEN ";}
}

int main() {
	C c; D d; E e; A& a1 = c; B& b1 = d; B& b2 = e; D& d1 = e; D* pd = dynamic_cast<E*>(&b2);
	
	Fun(c); cout << endl;
	Fun(d); cout << endl;
	Fun(e); cout << endl;
	Fun(a1); cout << endl;
	Fun(b1); cout << endl;
	Fun(d1); cout << endl;
	Fun(*pd); cout << endl;
	Fun<D>(*pd); cout << endl;
	Fun<D>(e); cout << endl;
	//Fun<E>(*pd); cout << endl;
	Fun<E>(e); cout << endl;
	//Fun<E>(d1); cout << endl;
	Fun<A>(c); cout << endl;
}

/*
RISPOSTE ACCETTATE:
C
B D::f 
E E::f 
A 
B D::f oppure B B::f
B E::f oppure B D::f
B E::f oppure B D::f
B E::f oppure B D::f
B E::f oppure B D::f
NON COMPILA // error: invalid initialization of reference of type 'const E&' from expression of type 'D'
E E::f 
NON COMPILA // error: invalid initialization of reference of type 'const E&' from expression of type 'D'
A 

La possibilità di due risposte è dovuta al fatto che throw non lancia 
direttamente l'oggetto usato, ma una sua copia. Viene quindi lanciato un T(ref)
e non ref! Tale oggetto chiaramente ha tipo statico e dinamico uguale a T.

In base al suo tipo, mantiene il tipo statico e anche il dinamico, in quanto il tipo dinamico qui puó fare match dati i const e quindi usa anche quello in fase di stampa.
Altrimenti normalmente manterresti solo il tipo statico, insomma, il caso particolare di questo esercizio é la doppia stampa per i tipi dinamici diciamo, 
dato piú che altro dai const e dal fatto di avere il riferimento costante di cui sopra, altrimenti ti basta il tipo statico perché l'eccezione si ferma 
e stampa con il primo tipo che fa match, quindi che gli corrisponde.


È stato deciso perciò di accettare anche delle risposte 
alternative, seppur coerenti col comportamento del tipo dinamico degli oggetti

Quindi:

void Fun(const T& ref)
Effettua un T(ref)
E mantiene sia tipo statico sia tipo dinamico dell'argomento.

Mentre: 

void Fun(T& ref)
Effettua un T(ref)
E mantiene solo il tipo statico dell'argomento.



*/
