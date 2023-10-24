// COSA STAMPA IL SEGUENTE PROGRAMMA: ASSEGNAZIONE DI DEFAULT C++
#include <iostream>
using namespace std;
class Puntatore {
public:
    int* punt;
};
int main() {
    Puntatore x, y;
    x.punt = new int(8);
    y = x;
    cout << "*(y.punt) = " << *(y.punt) << endl;
    *(y.punt) = 3;
    cout << "*(x.punt) = " << *(x.punt) << endl;
}
