#include <vector>
#include <string>

using namespace std;

class Workout{
private: 
    int durataInMinuti;

public:
    Workout(int t): durataInMinuti(t){};
    virtual ~Workout(){};
    virtual Workout* clone() const = 0;
    virtual int calorie() const = 0;

    int getDurata() const {return durataInMinuti;}
};

class Corsa: public Workout{
private:
    double distanzaInKm;

public:
    Corsa(int t, double d): Workout(t), distanzaInKm(d){};
    
    Workout* clone() const {return new Corsa(*this);}
    int calorie() const {return pow(500*distanzaInKm, 2) / getDurata();}

    double getDistanza() const {return distanzaInKm;}
};

class Nuoto: public Workout{
private:
    unsigned int numeroVasche;

public:
    Nuoto(int t, unsigned int n): Workout(t), numeroVasche(n){};
    
    unsigned int getVasche() const {return numeroVasche;}
};

class StileLibero: public Nuoto{
public:
    Workout* clone() const {return new StileLibero(*this);}
    int calorie() const {
        if(getDurata() < 10) return 30 * getVasche();
        else if(getDurata() >= 10) return 40 * getVasche();
    }
};

class Dorso: public Nuoto{
public:
    Workout* clone() const {return new Dorso(*this);}
    int calorie() const {
        if(getDurata() < 15) return 30 * getVasche();
        else if(getDurata() >= 15) return 35 * getVasche();
    }
};

class Rana: public Nuoto{
public:
    Workout* clone() const {return new Rana(*this);}
    int calorie() const {return 25 * getVasche();}
};

class InForma{
private:
    vector<const Workout*> vct;

public:
    vector<Nuoto*> vasche(int v){
        vector<Nuoto*> nv;
        for(auto i = vct.begin(); i < vct.end(); ++i){
            auto pippo = dynamic_cast<Nuoto*>(const_cast<Workout*>(*i));
            if(pippo && pippo->getVasche() > v){
                nv.push_back(dynamic_cast<Nuoto*>(pippo->clone()));
            }
        }
        return nv;
    }

    vector<Workout*> calorie(int x){
        vector<Workout*> v;
        for(auto i = vct.begin(); i < vct.end(); ++i){
            auto pippo = const_cast<Workout*>(*i);
            if(pippo->calorie() > x && dynamic_cast<Rana*>(pippo) == nullptr){
                v.push_back(pippo->clone());
            }
        }
        return v;
    }

    void removeNuoto(){
        int maxCal = 0;
        for(auto i = vct.begin(); i < vct.end(); ++i){
            auto pippo = dynamic_cast<Nuoto*>(const_cast<Workout*>(*i));
            if(pippo && pippo->calorie() > maxCal){
                maxCal = pippo->calorie();
            } else if(pippo && pippo->calorie() == maxCal){
                vct.erase(i);
            } else if(pippo == nullptr){
                throw string("NoRemove");
            }
        }
    }
};