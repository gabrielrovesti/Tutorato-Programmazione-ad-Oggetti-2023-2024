//Sol di Greta C.

#include<list>
#include<vector>

class SIM{
  unsigned int tempo_tel;
  float traffico_dati;
public:
  static float costo_tel;
  static float costo_dati;
  virtual double costoMeseCorrente() const=0;
  float getTraffico() const {return traffico_dati;}
  unsigned int getTel() const {return tempo_tel;}
  virtual ~SIM() {}
};

float SIM::costo_tel=0.03;
float SIM::costo_dati=0.04;

class Tel : public SIM{
  float costo_abbonamento;
public:
  virtual double costoMeseCorrente() const{
    return (costo_abbonamento + (getTraffico()*SIM::costo_dati));
  }
  float getPriceAbb() const {return costo_abbonamento;}
};

class Dati : public SIM{
public:
  static float costo_abbonamento;
  virtual double costoMeseCorrente() const{
    return (costo_abbonamento + (getTel()*SIM::costo_tel));
  }
};

float Dati::costo_abbonamento=13.99;

class PAO{
  std::list<const SIM*> sim;

  std::vector<Dati> fun(double x) const{
    std::vector<Dati> v;
    for(std::list<const SIM*>::const_iterator cit=sim.begin(); cit!=sim.end(); ++cit){
      const Dati*p=dynamic_cast<const Dati*>(*cit);
      if(p && p->getTraffico() > x){
        v.push_back(*p);
      }
    }
    return v;
  }

  std::list<Tel*> fun2() const{
    std::list<Tel*> l;
    for(std::list<const SIM*>::const_iterator cit=sim.begin(); cit!=sim.end(); ++cit){
      const Tel*p=dynamic_cast<const Tel*>(*cit);
      if(p && p->getPriceAbb() >= 2*p->costoMeseCorrente()){
        l.push_back(const_cast<Tel*>(p));
      }
    }
    return l;
  }
};

int main(){}
