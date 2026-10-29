#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> monedas = {50, 25, 20, 10, 5, 1};
vector<int> memo(41, -1);

int MinNumMon(int cant) {
    //caso base
    if (cant== 0) {
        return 0;
    }

    if (memo[cant] != -1) {
        return memo[cant];
    }

    int minimo= 1000000;

    for (int moneda : monedas) {
        if (moneda <= cant) {
            minimo= min(minimo, MinNumMon(cant-moneda) + 1);
        }
    }

    memo[cant] = minimo;
    return minimo;
}

int main() {
    int cantidad= 40;
    cout << "cantidad: " << cantidad << endl;
    cout << "minimo monedas: "
         << MinNumMon(cantidad) << endl;

    return 0;
}