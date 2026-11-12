#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int cuantosLikesPuedoAcumular(int ronda, bool baile, int ventaja, int* anotaA, int* likes){
    if (ventaja < 0 || ventaja > ronda + 1) {
        return -1;
    }

    int golesB = baile ? 1 : 0;
    int ventajaAnterior = ventaja - anotaA[ronda] + golesB;

    if (ronda == 0) {
        if (ventajaAnterior != 0) {
            return -1;
        }
        return baile ? likes[0] : 0;
    }

    int mejor = -1;

    for (int bailoAntes = 0; bailoAntes <= 1; bailoAntes++) {

        bool alternarBaile = (bailoAntes == 0) ? false : true;

        int likesAnteriores = cuantosLikesPuedoAcumular(ronda - 1, alternarBaile, ventajaAnterior, anotaA, likes);

        if (likesAnteriores == -1) {
            continue;
        }

        int likesDeEstaRonda = 0;
        if (baile) {
            likesDeEstaRonda = alternarBaile ? likes[ronda] / 2 : likes[ronda];
        }

        int acumulados = likesAnteriores + likesDeEstaRonda;
        
        if (acumulados > mejor) {
            mejor = acumulados;
        }
    }

    return mejor;
}



int main()
{
    
    int rondas;
    cin >> rondas;

    int* anotaA = new int[rondas];
    int* likes = new int[rondas];

    for (int i = 0; i < rondas; i++) {
        in >> anotaA[i];
    }

    for (int i = 0; i < rondas; i++) {
        cin >> likes[i];
    }

    int ventaja = (anotaA[0] == 1) ? 1 : 0;
    bool yaBaile = false;

    int res = cuantosLikesPuedoAcumular(rondas-1, yaBaile, ventaja, anotaA, likes);

    return 0;
}