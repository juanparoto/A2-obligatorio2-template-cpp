#include <iostream>

using namespace std;

int cuantosLikesPuedoAcumular(int ronda, bool baile, int ventaja, int* anotaA, int* likes, int*** memo, int sinCalcular) {
    if (ventaja < 0 || ventaja > ronda + 1) {
        return -1;
    }

    if (memo[ronda][ventaja][baile] != sinCalcular) {
        return memo[ronda][ventaja][baile];
    }

    int golesB = baile ? 1 : 0;
    int ventajaAnterior = ventaja - anotaA[ronda] + golesB;
    int mejor = -1;

    if (ronda == 0) {
        if (ventajaAnterior == 0) {
            mejor = baile ? likes[0] : 0;
        }
        memo[ronda][ventaja][baile] = mejor;
        return mejor;
    }

    for (int bailoAntes = 0; bailoAntes <= 1; bailoAntes++) {

        bool alternarBaile = (bailoAntes == 0) ? false : true;

        int likesAnteriores = cuantosLikesPuedoAcumular(
            ronda - 1, alternarBaile, ventajaAnterior, anotaA, likes, memo, sinCalcular);

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

    memo[ronda][ventaja][baile] = mejor;
    return mejor;
}

int main()
{
    
    int rondas;
    cin >> rondas;

    int* anotaA = new int[rondas];
    int* likes = new int[rondas];
    int*** memo = new int**[rondas];
    int sinCalcular = -2;

    int golesA = 0;
    for (int i = 0; i < rondas; i++) {
        cin >> anotaA[i];
        golesA += anotaA[i];
    }

    for (int i = 0; i < rondas; i++) {
        cin >> likes[i];
    }

    for (int ronda = 0; ronda < rondas; ronda++) {
        memo[ronda] = new int*[ronda + 2];
        for (int ventaja = 0; ventaja <= ronda + 1; ventaja++) {
            memo[ronda][ventaja] = new int[2];
            memo[ronda][ventaja][0] = sinCalcular;
            memo[ronda][ventaja][1] = sinCalcular;
        }
    }

    int res = 0;
    
    for (int ventaja = 0; ventaja <= golesA; ventaja++) {
        for (int baile = 0; baile <= 1; baile++) {
            int total = cuantosLikesPuedoAcumular(rondas - 1, baile, ventaja, anotaA, likes, memo, sinCalcular);
            if (total > res) {
                res = total;
            }
        }
    }

    cout << res << '\n';
    delete[] anotaA;
    delete[] likes;

    for (int ronda = 0; ronda < rondas; ronda++) {
        for (int ventaja = 0; ventaja <= ronda + 1; ventaja++) {
            delete[] memo[ronda][ventaja];
        }
        delete[] memo[ronda];
    }

    delete[] memo;
    return 0;
}
