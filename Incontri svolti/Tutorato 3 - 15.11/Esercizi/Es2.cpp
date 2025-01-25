#include <iostream>
#include <string>

using namespace std;

template <class T>
class C{
    template <class V>
    friend void fun(C<V>);
    private:
        T x;
    public:
        C(T y): x(y) {}
};

template<class T>
void fun(C<T> t){
    cout << t.x < " ";
    C<double> c(3.1);
    cout << c.x << endl;
}

int main(){
    C<int> c(4);
    C<string> s("blob");
    fun(c);
    fun(s);
}