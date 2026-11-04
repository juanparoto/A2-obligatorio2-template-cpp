#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

long long contarRemontadas(int *llegando, int inicio, int final) {
    if (inicio >= final) {
        return 0;
    }
    int mitad = inicio + (final - inicio) / 2;
    long long izq = contarRemontadas(llegando, inicio, mitad);
    long long der = contarRemontadas(llegando, mitad + 1, final);
    long long cruzadas = 0;
    int j = mitad + 1;
    for (int i = inicio; i <= mitad; i++) {
        while (j <= final && llegando[i] > 2 * llegando[j]) {
            j++;
        }
        cruzadas += j - (mitad + 1);
    }
    int *aux = new int[final - inicio + 1];
    int i = inicio;
    j = mitad + 1;
    int k = 0;
    while (i <= mitad && j <= final) {
        if (llegando[i] <= llegando[j]) {
            aux[k++] = llegando[i++];
        }
        else {
            aux[k++] = llegando[j++];
        }
    }
    while (i <= mitad) {
        aux[k++] = llegando[i++];
    }
    while (j <= final) {
        aux[k++] = llegando[j++];
    }
    for (int i = 0; i < k; i++) {
        llegando[inicio + i] = aux[i];
    }
    return izq + der + cruzadas;
}

int main()
{
    int cantidadDorsales;
    cin >> cantidadDorsales;
    int *llegando = new int[cantidadDorsales];
    for (int i = 0; i < cantidadDorsales; i++) {
        int dorsal;
        cin >> dorsal;
        llegando[i] = dorsal;
    }
    cout << contarRemontadas(llegando, 0, cantidadDorsales - 1);
}