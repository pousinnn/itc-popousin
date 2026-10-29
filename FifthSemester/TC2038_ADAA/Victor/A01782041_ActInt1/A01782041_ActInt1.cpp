//Actividad Integradora 1
//Nicolás Casillas Larrañaga | A01787292
//Paulina Cortez Balvanera | A01782041
//Regina Fernanda Portela Palacios | A01786698

/*
Propósito: Aplicar diferentes algoritmos de búsqueda y procesamiento de cadenas para analizar archivos de texto. Se busca utilizar 
el algoritmo KMP para encontrar patrones dentro de una transmisión, identificar el palíndromo más largo de una cadena y determinar 
la subcadena común más larga entre dos transmisiones. Además, se pretende reforzar el uso de algoritmos eficientes y comprender como éstos 
pueden utilizarse para resolver problemas de búsqueda y análisis de información.
*/


//librerías
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

//abrimos el file para guardar lo que sería el texto, este se va a leer línea por línea usando un ciclo
string leerF(string name) {
    ifstream archivo(name);
    string txt = "";
    string linea;
    while (getline(archivo, linea)) {
        txt = txt + linea;
    }
    return txt;
}

//parte 1
//búsqueda de mcode con kmp, vamos a usar una tabla para determinar las letras que podemos conservar
vector<int> tablaPrefijos(string mcode) {
    //asignamos el tamaño (mcode) y creamos la tabla en 0
    int m = mcode.size();
    vector<int> tabla(m, 0);
    int c = 0; //c representa cuántos caracteres llevamos
    //ciclo para iniciar en la segunda posición
    for (int i=1; i < m; i++) {
        //en caso que no coincidan 
        while (c > 0 && mcode[i] != mcode[c]) {
            c = tabla[c - 1];
        }
        //condicional para aumentar c
        if (mcode[i]== mcode[c]) {
            c++;
        }
        //guardamos el resultado en la tabla
        tabla[i]= c;
    }
    return tabla;
}

//aquí vamos a buscar el mcode dentro de transmission pero hace -1 si no se encuentra
int searchCodigo(string transmission, string mcode) {
    //asignamos tamaños
    int n= transmission.size();
    int m= mcode.size();
    // en caso de un mcode vacío o que no esté
    if (m == 0 || m > n) {
        return -1;
    }

    //tabla para kmp
    vector<int> tabla = tablaPrefijos(mcode);
    int c = 0; //c para la misma cantidad de caracteres
    for (int i = 0; i < n; i++) {
        //por si los caracteres no coinciden
        while (c > 0 && transmission[i] != mcode[c]) {
            c = tabla[c - 1];
        }
        //por si los caracteres sí coinciden
        if (transmission[i] == mcode[c]) {
            c++;
        }

        //cuando se encuentra el tamaño completo del mcode ya tenemos el código
        if (c== m) {
            //i para donde termina el mcode
            return i - m + 2;
        }
    }

    //por si no encontramos el mcode
    return -1;
}

//parte 2: para encontrar el palíndromo más largo
//regresa la posición inicial y la final
pair<int, int> palindromoL(string transmission) {
    // tamaño, posición inicial y longitud
    int n= transmission.size();
    int bestInicio= 0;
    int bestLongitud= 1;

    //probar cada caracter desde el centro
    for (int centro= 0; centro < n; centro++) {
        //hacer dos posibles tipos de palíndromos, par e impar
        for (int tipo= 0; tipo < 2; tipo++) {
            //para impar tanto izquierda como derecha empiezan igual
            //para par, la derecha va a empezar adelante (por uno)
            int izquierda= centro;
            int derecha= centro+tipo;

            //checar que sigan iguales, para seguir moviéndonos usando un ciclo while
            while (izquierda >= 0 && derecha < n && transmission[izquierda] == transmission[derecha]) {
                izquierda--;
                derecha++;
            }

            //para cuando acaba while
            int longitud= derecha - izquierda - 1;
            //guardamos la nueva información si la longitud nueva es mejor
            if (longitud > bestLongitud) {
                bestLongitud= longitud;
                bestInicio= izquierda + 1; //regresa a la posición real
            }
        }
    }

    //setteamos nuestro inicio en 1
    int inicio= bestInicio + 1;
    int fin= bestInicio + bestLongitud;
    return {inicio, fin};
}

//parte 3
//encontrar el substring más largo, va a regresar la posición inicial y la posición final
pair<int, int> substringL(string transmission1, string transmission2) {
    //asignamos tamaño y guardamos las filas (anterior y actual)
    int n= transmission1.size();
    int m= transmission2.size();
    vector<int> anterior(m + 1, 0);
    vector<int> actual(m + 1, 0);

    //registramos la mejor longitud y la posición donde acaba el mejor substring
    int bestLongitud= 0;
    int mejorFin= 0;

    //ciclos para recorrer transmission 1 y 2
    for (int i= 1; i <= n; i++) {
        for (int j= 1; j <= m; j++) {
            if (transmission1[i - 1] == transmission2[j - 1]) { 
                //si son iguales, podemos continuar el substring y sumarle 1 hasta guardarlo
                actual[j]= anterior[j - 1] + 1;
                if (actual[j] > bestLongitud) {
                    bestLongitud= actual[j];
                    mejorFin = i; //i es el final
                }
            }
            else {
                actual[j]= 0; //en caso que no coincidan los valores
            }
        }

        //reasignamos la anterior a la actual
        anterior= actual;
    }

    //en caso que no haya
    if (bestLongitud== 0) {
        return {0, 0};
    }

    //definir el inicio
    int bestInicio= mejorFin - bestLongitud + 1;
    return {bestInicio, mejorFin};
}

//display de resultados
//kmp: true y posición vs false si no hay
void showResult(string transmission, string mcode) {
    int posicion= searchCodigo(transmission, mcode);
    if (posicion != -1) {
        cout << "true " << posicion << endl;
    }
    else {
        cout << "false" << endl;
    }
}

//main
int main() {
    //leer los files
    string transmission1= leerF("transmission1.txt");
    string transmission2= leerF("transmission2.txt");
    string mcode1= leerF("mcode1.txt");
    string mcode2= leerF("mcode2.txt");
    string mcode3= leerF("mcode3.txt");

    //parte 1: 
    cout << "parte 1: búsqueda de mcode" << endl;
    //transmission 1
    showResult(transmission1, mcode1);
    showResult(transmission1, mcode2);
    showResult(transmission1, mcode3);
    //transmission2
    showResult(transmission2, mcode1);
    showResult(transmission2, mcode2);
    showResult(transmission2, mcode3);

    //parte 2
    cout << endl;
    cout << "parte 2: palíndromo más largo" << endl;
    //transmission1
    pair<int, int> palindromo1 = palindromoL(transmission1);
    //transmission2
    pair<int, int> palindromo2 = palindromoL(transmission2);
    cout << palindromo1.first << " " << palindromo1.second << endl;
    cout << palindromo2.first << " " << palindromo2.second << endl;

    //parte 3
    cout << endl;
    cout << "parte 3: substring más largo" << endl;
    pair<int, int> comun = substringL(transmission1, transmission2);
    cout << comun.first << " " << comun.second << endl;
    return 0;

}

