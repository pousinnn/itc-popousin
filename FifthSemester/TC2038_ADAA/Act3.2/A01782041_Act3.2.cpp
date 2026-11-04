//Act 3.2
//Pau Cortez Balvanera | A01782041

//Proposito: Escribe un programa en C++ que implemente los algoritmos de Dijkstra y Floyd para
//encontrar la distancia más corta entre parejas de nodos en un grafo dirigido. Las implementaciones
//deben ser las más eficientes, es decir, Dijkstra debe ser implementado con una cola con prioridad
//y Floyd con Programación Dinámica.

// El programa debe leer un numero n seguido de n x n valores enteros no negativos que representan
//una matriz de adyacencias de un grafo dirigido.
// El primer número representa el número de nodos, los siguientes valores en la matriz, el valor
//en la posición i,j representan el peso del arco del nodo i al nodo j. Si no hay un arco entre
//el nodo i y el nodo j, el valor en la matriz debe ser -1

// La salida del programa es, primero con el algoritmo de Dijkstra la distancia del nodo i a l
//nodo j para todos los nodos, y luego, la matriz resultado del algoritmo de Floyd


//librerias

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int infinite = 1000000000; //pq aun no conocemos la distancia

//dijkstra - O(n^2 + m log n)
//calculamos la distancia mas corta por cada nodo considerando la cantidad de nodos y la matriz de adyacencia
void dijkstra(int n, const vector<vector<int>>& grafo) {cout << "Dijkstra :" << endl;
    //corremos desde cada nodo origibal
    for (int inicio = 0; inicio < n; inicio++) {
        //para la mejor distancia conocida
        vector<long long> dist(n, infinite);
        //heap de prioridad para determinar la menor distancia
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> cola;
        dist[inicio] = 0;
        cola.push({0, inicio});

        while (!cola.empty()) {
            long long distancia = cola.top().first;
            int nodo = cola.top().second;
            cola.pop();
            //en caso de distancias que no se actualicen y haya un mejor camino
            if (distancia > dist[nodo]) {
                continue;
            }

            //revisar los otros (se recorre con matriz)
            for (int j = 0; j < n; j++) {
                if (grafo[nodo][j] != -1) {
                    long long newDist =
                        distancia + grafo[nodo][j];
                    if (newDist < dist[j]) {
                        dist[j] = newDist;
                        cola.push({dist[j], j});
                    }
                }
            }
        }

        //mostrar distancias 
        for (int j = 0; j < n; j++) {
            if (inicio != j) {
                cout << "node " << inicio + 1 << " to node " << j + 1 << " : ";
                if (dist[j] == infinite) {
                    cout << -1;
                } else {
                    cout << dist[j];
                }
                cout << endl;
            }
        }
    }
}

// floyd - complejidad: 
//distancia mas corta entre parejas
void floyd(int n, const vector<vector<int>>& grafo) {
    cout << endl << "Floyd :" << endl;
    vector<vector<long long>> distFloyd(n, vector<long long>(n, infinite)
    );

    //copiamos la matriz para el caso base
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grafo[i][j] != -1) {
                distFloyd[i][j] = grafo[i][j];
            }
        }
    }

    //usaremos i para el origen, k para el nodo del medio, j para destino
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (distFloyd[i][k] != infinite && distFloyd[k][j] != infinite) {
                    //i debe ir a k & k a j
                    long long newDist = distFloyd[i][k] + distFloyd[k][j];
                    if (newDist < distFloyd[i][j]) {
                        distFloyd[i][j] = newDist;
                    }
                }
            }
        }
    }

    // mostramos la matriz que queda al final
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (distFloyd[i][j] == infinite) {
                cout << -1;
            } else {
                cout << distFloyd[i][j];
            }

            if (j < n - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    // ejempls
    vector<vector<vector<int>>> ejemplos = {

        // ejemplo 1: el del ejemplo del ejercico
        {
            {0, 2, -1, 3},
            {-1, 0, 1, 5},
            {2, 3, 0, -1},
            {3, -1, 4, 0}
        },

        // ejemplo 2: para mas nodos
        {
            {0, 3, -1, 7, -1},
            {8, 0, 2, -1, -1},
            {5, -1, 0, 1, -1},
            {2, -1, -1, 0, 4},
            {-1, -1, -1, -1, 0}
        },

        // ejemplo 3: un nodo que no se puede
        {
            {0, 6, -1},
            {-1, 0, -1},
            {4, -1, 0}
        },

        // ejemplo 4: un ciclo
        {
            {0, 1, -1, -1},
            {-1, 0, 2, -1},
            {-1, -1, 0, 3},
            {4, -1, -1, 0}
        }
    };

    for (int e = 0; e < (int)ejemplos.size(); e++) {
        int n = ejemplos[e].size();
        cout << " ejemplo " << e + 1 << endl;
        dijkstra(n, ejemplos[e]);
        floyd(n, ejemplos[e]);
        cout << endl;
    }

    return 0;
}