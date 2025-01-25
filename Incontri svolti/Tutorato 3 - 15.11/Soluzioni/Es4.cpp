/*
Si considerino le seguenti definizioni. 
Fornire una dichiarazione (non e` richiesta la definizione) dei membri pubblici della classe Z nel minor numero possibile 
in modo tale che la compilazione del precedente main() non produca errori. 
Attenzione: ogni dichiarazione in Z non necessaria per la corretta compilazione del main() sara` penalizzata.
*/
#include <iostream>
using namespace std;

class Z {
  public:
  int& operator++();
  int operator++(int);
  bool operator==(const Z&) const;
  Z (const int&); //converte int a Z
};

template <class T1, class T2=Z>
class C {
public:
  T1 x;
  T2* p;
};

template<class T1,class T2>
void fun(C<T1,T2>* q) {
  ++(q->p); //nessun requirement
  if(true == false) cout << ++(q->x); else cout << q->p; //q->x di tipo T1, operator++() T1
  (q->x)++; //operator++(int) su T1
  if(*(q->p) == q->x) *(q->p) = q->x; //(1) bool operator==(T2, T1), (2) operator=(T2, const T1&)
  T1* ptr = &(q->x); //nessun requirement
  T2 t2 = q->x; //T2(const T1&)
}

int main(){
  //Non occorre implementare il main ma solo
  //capire cosa deve fare la classe Z
}