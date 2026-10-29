//Activity 1.2
// Paulina Cortez Balvanera | A01782041
// 01/09/2026

//Propositio: Poner en práctica la técnica de programación de "programación dinámica", y "algoritmos avaros"

// Utilizando las técnicas de programación de "programación dinámica", y la de "algoritmos avaros", escribe en C++ un programa que resuelva el problema del cambio de monedas.
// El programa recibe un numero entero N, seguido de N valores enteros (uno en cada línea) que representan las diferentes denominaciones disponibles de las monedas. 
// Seguido de esto, el programa recibe dos números enteros: P y Q, (uno en cada línea) por la entrada estándar, que representan P: el precio de un producto dado y Q: es el billete o moneda con el que se paga dicho producto.
// La salida del programa es una lista de N valores correspondientes al número de monedas de cada denominación, de mayor a menor, una en cada línea, que se tienen que dar para dar el cambio por el producto pagado, primero utilizando programación dinámica, y luego utilizando un algoritmo avaro.

//en cuanto a la complejidad, tenemos tres secciones diferentes; 
// Ordenar: O(n log n)
// Programcion dinamica: O(n^2)
// Programacion greedy: O(n^2)


//Librerias
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//creamos la funcion principal para dinamico que va a recibir las denominaciones posibles y cuanto se debe devolver en fomra de vector
vector<int> cambioDinamico(vector<int> monedas, int cambio) {
    vector<int> minimo(cambio + 1, 999999); //para saber a la cantidad que debemos llegar
    vector<int> monedaUsada(cambio + 1, -1); //guardamos que moneda usamos
    minimo[0]=0;

    //recorremos todas las cantidades (1 hasta el cambio)
    for (int monto = 1; monto <= cambio; monto++) {
        //revisarr cada moneda available
        for (int i = 0; i < monedas.size(); i++) {
            //checar si el tamaño de la moneda es correcto
            if (monedas[i] <= monto) {
                //buscar solución optima - si produce menos monedas se remplaza
                if (minimo[monto - monedas[i]] + 1 < minimo[monto]) {
                    minimo[monto] = minimo[monto - monedas[i]] + 1;
                    monedaUsada[monto] = i;
                }
            }
        }
    }

    //vector para contar lsa monedas
    vector<int> resultado(monedas.size(), 0);
    int restante = cambio; //guardamos cuanto nos falta (cambio)
    //bucle para checar si aun nos falta cambio
    while (restante > 0) {
        int indice = monedaUsada[restante];
        if (indice == -1) { //sin solucion, regresar resultado que tenemos
            return resultado;
        }
        resultado[indice]++; //resultado
        restante = restante - monedas[indice];
    }

    return resultado;
}

//greedy - mismo proceso pero en avaro
vector<int> cambioAvaro(vector<int> monedas, int cambio) {
    vector<int> resultado(monedas.size(), 0);
    int restante = cambio;

    //toma la moneda más grande que se puede usar
    for (int i = 0; i < monedas.size(); i++) {
        if (monedas[i] <= restante) {
            resultado[i] = restante / monedas[i];
            restante = restante % monedas[i]; //residuo
        }
    }

    return resultado;
}

//rresultados
//para razones esteticas
void mostrarResultado(vector<int> monedas,
                      vector<int> resultado) {

    cout << "denominacion | cantidad" << endl;
    for (int i = 0; i < monedas.size(); i++) {
        cout << monedas[i] << "           | "
             << resultado[i] << endl;
    }
}

//caso ejemplo
void ejecutarCaso(vector<int> monedas, int precio, int pago) { //recibe monedas, precio y pago

    //mayor a minor - invertir
    sort(monedas.begin(), monedas.end(), greater<int>());
    int cambio = pago - precio; //cambio
    cout << "Cambio: " << cambio << endl;

    //ejecutar ambos tipos de programacion
    //dinamica 
    vector<int> dinamico =
        cambioDinamico(monedas, cambio);
    //avaro
    vector<int> avaro =
        cambioAvaro(monedas, cambio);
    cout << endl;
    //mostrar ambos
    cout << "programacion dinamica:" << endl;
    mostrarResultado(monedas, dinamico);
    cout << endl;
    cout << "algoritmo greedy:" << endl;
    mostrarResultado(monedas, avaro);
    cout << endl;
}

//main
int main() {
//tanzania (ejemplo de clase)
    cout << "_____________________" << endl;
    cout << "Tanzania" << endl;
    vector<int> monedas1 = {50, 25, 20, 10, 5, 1};
    ejecutarCaso(monedas1, 40, 65);


    // cuando greedy no es lo mas optimo
    cout << "_____________________" << endl;
    cout << "avaro no optimo" << endl;
    vector<int> monedas2 = {4, 3, 1};
    ejecutarCaso(monedas2, 6, 12);


    // random sencillo
    cout << "_____________________" << endl;
    cout << "caso sencillo" << endl;
    vector<int> monedas3 = {10, 5, 1};
    ejecutarCaso(monedas3, 7, 25);

    //greedy no optimo
    cout << "_____________________" << endl;
    cout << "avaro no optimo" << endl;
    vector<int> monedas4 = {9, 6, 5, 1};
    ejecutarCaso(monedas4, 10, 21);
    return 0;
}

