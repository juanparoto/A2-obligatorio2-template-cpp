#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

long long contarRemontadas(int* llegando, int inicio, int final){
        if (inicio >= final){
            return 0;
        }
        int mitad = inicio + (final - inicio)/2;
        long long izq = contarRemontadas(llegando, inicio, mitad);
        long long der = contarRemontadas(llegando, mitad + 1, final);
        long long cruzadas = 0;
        for (int i = inicio; i <= mitad; i++){
            for (int j = mitad + 1; j <= final; j++){
                if (llegando[i] > llegando[j] * 2){
                    cruzadas++;
                }
            }
        }
        return izq + der + cruzadas;
    }

int main()
{
    int cantidadDorsales;
    cin >> cantidadDorsales;
    int* llegando = new int[cantidadDorsales];
    for (int i = 0; i < cantidadDorsales; i++){
        int dorsal;
        cin >> dorsal;
        llegando[i] = dorsal;
    }
    cout << contarRemontadas(llegando, 0, cantidadDorsales - 1);
}