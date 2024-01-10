#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>

using namespace std;

class A {
public:
    virtual ~A() {}
    virtual A* f() const = 0;
};

class B : public A {
public:
    virtual ~B() {}
    virtual B* f() const = 0;
};

class C : public B {
public:
    virtual ~C() {}
    virtual C* f() const { return nullptr; }
};

class D : public B {
public:
    virtual ~D() {}
    virtual D* f() const { return nullptr; }
};

class E : public D {
public:
    virtual ~E() {}
    virtual E* f() const { return nullptr; }
};

list<const D *const> fun(const vector<const B*>&v){
    list<const D *const> ret;
    int count = 0;
    for(auto cit = v.begin(); cit != v.end(); ++cit){
        if(*cit != nullptr && typeid(**cit) == typeid(C)){       
            count++;
            if(count > 2){
                throw C();
            }
            //Cancellazione del const_iterator
            // cit = v.erase(cit); - procedura normale; è const_iterator, quindi la cosa corretta è
            cit--; // 
        }
        
        A* ptr = (*cit)->f();
        if(ptr){
            if(dynamic_cast<const D* const>(ptr) && dynamic_cast<const E* const>(ptr) ){
                ret.push_back(dynamic_cast<const D* const>(ptr));
            }
        }
        else{
           throw std::string("nullptr"); 
        }
    }

    /*
    C++ - range-based
    for(auto i: v){

    }
    */
    

    /*for(list<const B*>::const_iterator cit = v.begin(); cit != v.end(); ++cit){

    }*/

    return ret;
}