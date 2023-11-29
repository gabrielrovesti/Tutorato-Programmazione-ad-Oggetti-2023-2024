template <class T1,class T2>
bool Fun(T1* t1, T2& t2) const {
     return typeid(T1) == typeid(T2) && typeid(*t1) == typeid(t2) && dynamic_cast<Abs*>(t1);
}