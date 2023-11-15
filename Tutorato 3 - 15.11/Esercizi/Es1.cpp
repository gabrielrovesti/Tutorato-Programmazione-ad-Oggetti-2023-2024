class A{
    public:
    A(int x=0) {cout << x << "A() ";}
}

template<class T>
class C{
    public:
    static A s;
}

template <class T>
A C<T>::s=A();

int main(){
    C<double> c;
    C<int> d;
    C<int>::s = A(2);
}