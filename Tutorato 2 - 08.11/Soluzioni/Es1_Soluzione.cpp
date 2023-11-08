class S{
    public:
        string s;
        S(string t): s(t) {}
};

class N{
    private:
        S x;
    public:
        N* next;
        N(S t, N* p): x(t), next(p) 
        {cout << "N2 ";}

        ~N() {
            if(next) 
            delete next; 
            cout << x.s + "~N ";
        }
};

class C{
    N* pointer;
    public:
        C(): pointer(0) {}
        ~C() {delete pointer; cout << "~C ";}
        void F(string t1, string t2 = "pippo"){
            pointer = new N(S(t1), pointer);
            pointer = new N(t2, pointer);
        }
}

int main(){
    C* p = new C; cout << "UNO\n";
    p->F("pluto, paperino"); 
    p->F("topolino"); cout << "DUE\n";
    delete p; cout << "TRE\n";
}

/*
NESSUNA STAMPA UNO - non traccia nulla di utile
N2 N2 N2 N2 DUE - deve costruire tramite n ogni stringa, da pluto a topolino, compreso l'oggetto di creazione
pluto~N paperino~N topolino~N ~N pippo~N ~N ~C TRE - cancello tutti i valori in ordine e stampo
NESSUNA STAMPA - fine del programma
*/