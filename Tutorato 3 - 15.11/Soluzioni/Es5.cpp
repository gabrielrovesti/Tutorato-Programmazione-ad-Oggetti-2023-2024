#include <iostream>
#include <string>
#include <vector>

using namespace std; 

template <class T>
class Dizionario{
    public:
        bool insert(string, const T&);
        bool erase(string);
        T* findValue(string);
        vector<string> findKey(const T&);
        T* operator[](string);
        bool operator==(const Dizionario);
        int index(string);
    private:
        vector<string> keys;
        vector<T> values;
};

template <class T>
ostream& operator<<(ostream& os, const Dizionario<T>& dict){
    for(int i=0; i<dict.keys.size(); i++){
        os << "Chiave: " << dict.keys[i] << " e valore: " << dict.values[i] << "\n\t";
    }
    return os;
}

template <class T>
int Dizionario<T>::index(string key){
    for(int k=0; k<keys.size(); k++){
        if(values[k]==key) return k;
        else return -1;
    }
}

template <class T>
bool Dizionario<T>::insert(string key, const T& val){
    int index_found=index(key);

    if(!index_found) return false;
    else{
        keys.push_back(key);
        values.push_back(val);
        return true;
    }
}

template <class T>
bool Dizionario<T>::erase(string key){
    int index_found=index(key);

    if(!index_found) return false;
    else{
        keys.erase(keys.begin()+index);
        values.erase(values.begin()+index);
        return true;
    }
}

template <class T>
T* Dizionario<T>::operator[](string key){
    int indice=index(key);
    if(indice)   return &values[key];
    else return 0;
}

template <class T>
vector<string> Dizionario<T>::findKey(const T& t){
    vector<string> v;
    for(int i=0; i<keys.size(); i++){
        if(t == values[i])  v.push_back(keys[i]);
    }
    return v;
}

template <class T>
T* Dizionario<T>::findValue(string key){
    for(int i=0; i<values.size(); i++){
        if(key == keys[i])  return &values[i];
    }
    return 0;
}

template <class T>
bool Dizionario<T>::operator==(const Dizionario dict){
    if(keys.size() != dict.keys.size()) return false;
    for(int i=0; i<keys.size(); i++){
        if(keys[i] != dict.keys[i]) return false;
    }
    return true;
}

int main(){

}