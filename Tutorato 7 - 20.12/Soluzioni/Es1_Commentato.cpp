#include <vector>
#include <string>

using namespace std;

class Workout{
    private:
        double durata;
    public:
        double getDurata() const{return durata;}
        virtual ~Workout(); //rende la classe polimorfa
        
        // Implementazione standard
        // Copia polimorfa = creazione nuovo puntatore di tipo classe
        // Workout* clone(){
        //     return new Workout(*this);
        // }

        // classe astratta = metodi virtuali puri
        virtual Workout* clone() = 0;
        virtual int calorie() = 0;

        Workout(double d): durata(d) {}
};

class Corsa: public Workout{
    private:
        double distanzaKm;
    public:
        Corsa(double dur, double d): 
        Workout(dur), distanzaKm(d) {}

        //metodo di clonazione classe Corsa
        virtual Corsa* clone(){
            return new Corsa(*this);
        }

        virtual int calorie(){
            return (500 * (distanzaKm * distanzaKm) / getDurata());
        }

        double getDistanzaKm() const{
            return distanzaKm;
        }
};

class Nuoto: public Workout{
    private:
        int vasche;
    public:
        Nuoto(int dur, int v): 
        Workout(dur), vasche(v){}
        int getVasche() const{
            return vasche;
        }
};

class StileLibero: public Nuoto{
    public:
        virtual StileLibero* clone(){
            return new StileLibero(*this);
        }

        virtual int calorie(){
            if(getDurata() < 10){
                return 35 * getVasche();
            }
            else{
                return 40 * getVasche();
            }
        }
};

class Dorso: public Nuoto{
    public:
        virtual Dorso* clone(){
            return new Dorso(*this);
        }

        virtual int calorie(){
            if(getDurata() < 15){
                return 30 * getVasche();
            }
            else{
                return 35 * getVasche();
            }
        }
};

class Rana: public Nuoto{
    public:
        virtual Rana* clone(){
            return new Rana(*this);
        }

        virtual int calorie(){
            return 25 * getVasche();
        }
};

class InForma{
    public:
    vector<const Workout*> v;

    vector<Nuoto*> vasche(int vasche){
        vector<Nuoto*> vec;

        // Alternativa con auto (prossime lezioni) 
        // for (auto it = v.begin(); it != v.end(); ++it)
        for(vector<const Workout*>::iterator it = v.begin(); it != v.end(); ++it){
            
            Nuoto* n = dynamic_cast<Nuoto*>(const_cast<Workout*>(*it));
            // alternativamente (considerando const)
            // Nuoto * n = dynamic_cast<const Nuoto*>(*it);

            if(n && n->getVasche() > vasche){
                // convertiamo a Nuoto* qua sotto
                // perché sennò (*it) (cioè l'oggetto puntato)
                // resta di tipo const Workout* (verrebbe convertito solo un oggetto)

                vec.push_back(dynamic_cast<Nuoto*>(n->clone()));
                // alternativamente (considerando const)
                // vec.push_back(dynamic_cast<const Nuoto*>(n->clone()));
            }
        }

        return vec;
    }

    vector<Workout*> calorie(int x){
        vector<Workout*> vec;

        for(vector<const Workout*>::iterator it = v.begin(); it != v.end(); ++it){

            Workout * w = dynamic_cast<Workout*>(const_cast<Workout*>(*it));
            Rana * r = dynamic_cast<Rana*>(const_cast<Workout*>(*it));

            if(!r && w->calorie() > x){
                vec.push_back(w->clone());
            }
        }
        return vec;
    }

    void removeNuoto(){
        int max = 0;
        // massimo tra tutti i tipi di calorie
        // for(vector<const Workout*>::iterator it = v.begin(); it != v.end(); ++it){
        //     Workout * w = dynamic_cast<Workout*>(const_cast<Workout*>(*it));
        //     if(w->calorie() > max){
        //         max = w->calorie();
        //     }
        // }

        // Massimo tra i soli allenamenti a nuoto
        for(vector<const Workout*>::iterator it = v.begin(); it != v.end(); ++it){
            Nuoto * n = dynamic_cast<Nuoto*>(const_cast<Workout*>(*it));
            if(n->calorie() > max){
                max = n->calorie();
            }
        }

        for(vector<const Workout*>::iterator it = v.begin(); it != v.end(); ++it){
            Nuoto * n = dynamic_cast<Nuoto*>(const_cast<Workout*>(*it));
            if(n->calorie() == max && !n){
                //it = v.erase(it); //altro modo di cancellare
                v.erase(it);
            }
            // if (n == nullptr)
            if(!n){
                throw std::string("NoRemove");
            }
        }
    }
};