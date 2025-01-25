#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Widget{
    private:
        double width;
        double height; 
    public:
        double getWidth() const {return width;}
        double getHeight() const {return height;}

        // rendiamo la classe base polimorfa
        // aka distruggiamo tutti i sottooggetti
        virtual ~Widget(){};

        // metodo virtuale puro = astratto
        virtual void setStandardSize() = 0;

        //costruttore 
        Widget(double w, double h): 
        width(w), height(h) {};
};

class AbstractButton: public Widget{
    private:
        string label;
    public:
        AbstractButton(double w, double h, string l): 
        Widget(w, h), label(l) {}
};

int main() {

}