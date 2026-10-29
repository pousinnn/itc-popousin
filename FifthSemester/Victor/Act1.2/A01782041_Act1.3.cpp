//Act 1.3
//Pau Cortez Balvanera | A01782041

//Proposito: Poner en práctica la técnica de programación de "backtracking" y la de "ramificación y poda"

// Utilizando la técnica de programación de "backtracking" y la de "ramificación y poda", escribe en C++ un programa que resuelva un laberinto.
// El programa recibe dos numeros enteros M y N, seguido de M líneas de N valores booleanos(0|1) separados por un espacio, por la entrada estándar
// que representan el laberinto.  Un 1 representa una casilla en la que es posible moverse, un 0 es una casilla por la que NO se puede pasar.
// El origen o casilla de inicio es siempre la casilla (0,0) y la salida o meta es siempre la casilla (M-1, N-1)
// La salida del programa es una matriz de valores booleanos (0|1) que representan el camino para salir del laberinto. Primero debe mostrarse la
// solución utilizando la técnica de backtracking, y luego utilizando la técnica de ramificación y poda.

//en cuanto a la complejidad, tenemos dos secciones;
//para tanto backtracking como ramificación vamos a tener una complejidad de O(n!) pero una en el peor caso que otra
// y para el espacio en si tenemos una complejidad de O(n) 

//liberias
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//funcion para verificar si una casilla esta dentro del laberinto y si se puede recorrer.
bool valid(const vector<vector<int>>& laberinto, const vector<vector<int>>& visitado, int fila, int columna)
{
    int M = laberinto.size();
    int N = laberinto[0].size();

    return fila >= 0 && fila < M && columna >= 0 && columna < N && laberinto[fila][columna] == 1 && visitado[fila][columna] == 0;
}

//para backtracking vamos a intentar buscar el camino desde la posición en la que estamos hasta la salida
bool backtracking(const vector<vector<int>>& laberinto, vector<vector<int>>& camino, vector<vector<int>>& visitado, int fila, int columna)
{
    int M = laberinto.size();
    int N = laberinto[0].size();

    //si llegamos a la meta significa que ya encontramos el camino.
    if (fila == M - 1 && columna == N - 1) {
        camino[fila][columna] = 1;
        return true;
    }

    //condicional para checar si podemos usar esta casilla.
    if (!valid(laberinto, visitado, fila, columna)) {
        return false;
    }

    // descartamos  la casilla pq ya fue visitada
    visitado[fila][columna] = 1;
    camino[fila][columna] = 1;

    // para ir hacia abajo.
    if (backtracking(laberinto, camino, visitado,
             fila + 1, columna)) {
        return true;
    }

    //opción de moverse a la derecha.
    if (backtracking(laberinto, camino, visitado,
                     fila, columna + 1)) {
        return true;
    }

    // en caso que no, se puede mover hacia arriba.
    if (backtracking(laberinto, camino, visitado,
                     fila - 1, columna)) {
        return true;
    }

    // en caso que no, se puede mover a la izquierda.
    if (backtracking(laberinto, camino, visitado,
                     fila, columna - 1)) {
        return true;
    }

    //si ninguna sirve, pos lo detenemos
    camino[fila][columna] = 0;
    return false;
}


//para el caso de ramificacioón y poda, vamos a buscar un camino pero a su vez vamos a mantener el mejro camino encontrado, vamos a comparar si el camino que 
//tenemos a el camino que encontramos y comparar para ver si es mejor o peor - a partir de eso se poda y ya no se explora
void ramPoda(const vector<vector<int>>& laberinto, vector<vector<int>>& currentPath, vector<vector<int>>& mejorPath, vector<vector<int>>& visitado, int fila, int columna, int currentLongitud, int& mejorLength)
{
    int M = laberinto.size();
    int N = laberinto[0].size();

    //si no es valida, terminamos esta rama
    if (!valid(laberinto, visitado, fila, columna)) {
        return;
    }

    // si ya encontramos un camino igual o mejor, ya nos quedamos con eso
    if (currentLongitud >= mejorLength) {
        return;
    }
    
    //marcamos la casilla actual
    visitado[fila][columna] = 1;
    currentPath[fila][columna] = 1;

    //si llegamos a la meta, guardamos la solucion(el camino)
    if (fila== M - 1 && columna== N - 1)
    {
        mejorLength = currentLongitud;
        mejorPath = currentPath;
    }
    else
    {
        // para abajo
        ramPoda(laberinto, currentPath, mejorPath, visitado, fila + 1, columna, currentLongitud + 1, mejorLength);
        //parra derecha
        ramPoda(laberinto, currentPath, mejorPath, visitado,fila, columna + 1, currentLongitud + 1, mejorLength);
        //para arriba
        ramPoda(laberinto, currentPath, mejorPath, visitado, fila - 1, columna, currentLongitud + 1, mejorLength);
        //para izquierda
        ramPoda(laberinto, currentPath, mejorPath, visitado, fila, columna - 1, currentLongitud + 1, mejorLength);
    }

    // regresamos para intentar otra rama
    currentPath[fila][columna] = 0;
    visitado[fila][columna] = 0;
}

//imprimimos en formato de matriz
void printMatriz(const vector<vector<int>>& matriz)
{
    for (const auto& fila : matriz){
        for (int valor : fila)
        {
            cout << valor << " ";
        }

        cout << endl;
    }
}


//nuestro main
int main()
{
    // caso 1: camino sencillo
    vector<vector<int>> laberinto1 = {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 1}
    };

    // caso 2: muchas rutas posibles
    vector<vector<int>> laberinto2 = {
        {1, 1, 1, 0},
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 1}
    };

    //caaso 3: sin camino
    vector<vector<int>> laberinto3 =
    {
        {1, 1, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    // caso 4: muchas rutas posibles again
    vector<vector<int>> laberinto4 =
    {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };

    vector<vector<vector<int>>> casos =
    {
        laberinto1,
        laberinto2,
        laberinto3,
        laberinto4
    };

    for (int caso = 0; caso < 4; caso++)
    {
        vector<vector<int>> laberinto = casos[caso];
        int M = laberinto.size();
        int N = laberinto[0].size();

        cout << "_____________________" << endl;
        cout << "casos de prueba " << caso + 1 << endl;
        
        cout << endl;
        cout << "laberinto:" << endl;
        printMatriz(laberinto);

        // backtracking

        vector<vector<int>> caminoBacktracking(M, vector<int>(N, 0));
        vector<vector<int>> visitadoBacktracking(M, vector<int>(N, 0));

        bool encontradoBacktracking = backtracking(laberinto, caminoBacktracking, visitadoBacktracking, 0, 0);

        cout << endl;
        cout << "backtracking:" << endl;

        if (encontradoBacktracking) {
            printMatriz(caminoBacktracking);
        }
        else {
            cout << "no existe un camino" << endl;
        }

        //ramificacion y poda

        vector<vector<int>> caminoActual(M, vector<int>(N, 0));
        vector<vector<int>> mejorCamino(M, vector<int>(N, 0));
        vector<vector<int>> visitado(M, vector<int>(N, 0));

        int mejorLongitud = M * N + 1;

        ramPoda(laberinto, caminoActual, mejorCamino, visitado, 0, 0, 1, mejorLongitud);
        cout << endl;
        cout << "ramificacion y poda:" << endl;

        if (mejorLongitud != M * N + 1) {
            printMatriz(mejorCamino);
        }
        else {
            cout << "No existe un camino" << endl;
        }

        cout << endl;
    }

    return 0;
}