//MinNumMon

#include <iostream>
#include <unordered_map>
using namespace std;

int MinNumMon(int cant) {
    //caso base
    if (cant == 0) {
        return 0;
    }

    int minMonedas= 1000000;

    //para 6
    if (cant >= 6) {
        minMonedas = min(minMonedas, MinNumMon(cant-6)+1);
    }

    //para 5
    if (cant >= 5) {
        minMonedas = min(minMonedas, MinNumMon(cant-5)+1);
    }

    //para 1
    if (cant >= 1) {
        minMonedas = min(minMonedas, MinNumMon(cant-1)+1);
    }
    return minMonedas;
}

int main() {
    int cant;
    cout << "cantidad: ";
    cin >> cant;
    cout << "minimo numero de monedas: "
         << MinNumMon(cant) << endl;
    return 0;
}