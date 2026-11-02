#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int cantidadPlacas;
    cin >> cantidadPlacas;

    int* cantidadApariciones = new int[1001]();

    for(int i = 0; i<cantidadPlacas; i++){
        int placa;
        cin >> placa;
        cantidadApariciones[placa]++;
    }

    int cantidadPares = 0;
    bool hayImpar = false;
    int maxImpar = 0;

    int* pares = new int[1001]();

    for(int i = 0; i<1001; i++){

        if(cantidadApariciones[i]%2!=0){

            hayImpar = true;

            if(i>maxImpar){
                maxImpar = i;
            }
        }
    
        cantidadPares+= cantidadApariciones[i] / 2;
        pares[i] = cantidadApariciones[i] / 2;
    }

    int tamañoRetorno = 0;

    if(hayImpar){
        tamañoRetorno = 2*cantidadPares + 1;
    }
    else{
        tamañoRetorno = 2*cantidadPares;
    }
    
    int* retorno = new int[tamañoRetorno]();

    if(hayImpar){
        retorno[tamañoRetorno/2]= maxImpar;
    }

    int indiceAvanzador = 0;

    for(int i = 1000; i>=0; i--){
        for(int j = 0; j < pares[i]; j++){
            retorno[indiceAvanzador] = i;
            retorno[tamañoRetorno - 1 - indiceAvanzador] = i;
            indiceAvanzador++;
        }
    }

    for(int i = 0; i<tamañoRetorno; i++){
        cout << retorno[i] << " ";
    }

    cout << endl;

    return 0;
}