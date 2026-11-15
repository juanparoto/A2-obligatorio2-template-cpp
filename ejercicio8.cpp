#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int mochila(int n, int w, int* pesos, int* satifacciones, int* categorias, int* li, int****** tablero){
    for (int prod = 1; prod <= n; prod++){
        for (int cap = 0; cap <= w; cap++){
            for (int a = 0; a <= li[0]; a++){
                for (int c = 0; c <= li[1]; c++){
                    for (int b = 0; b <= li[2]; b++){
                        for (int v = 0; v <= li[3]; v++){
                            tablero[prod][cap][a][c][b][v] = tablero[prod - 1][cap][a][c][b][v];
                            if (pesos[prod] <= cap){
                                int anterior = -1;
                                if (categorias[prod] == 0 && a > 0){
                                    anterior = tablero[prod - 1][cap - pesos[prod]][a - 1][c][b][v];
                                }
                                if (categorias[prod] == 1 && c > 0){
                                    anterior = tablero[prod - 1][cap - pesos[prod]][a][c - 1][b][v];
                                }
                                if (categorias[prod] == 2 && b > 0){
                                    anterior = tablero[prod - 1][cap - pesos[prod]][a][c][b - 1][v];
                                }
                                if (categorias[prod] == 3 && v > 0){
                                    anterior = tablero[prod - 1][cap - pesos[prod]][a][c][b][v - 1];
                                }
                                if (anterior != -1){
                                    anterior += satifacciones[prod];
                                    tablero[prod][cap][a][c][b][v] = max(anterior, tablero[prod][cap][a][c][b][v]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int maximo = 0;
    for (int a = 0; a <= li[0]; a++){
        for (int c = 0; c <= li[1]; c++){
            for (int b = 0; b <= li[2]; b++){
                for (int v = 0; v <= li[3]; v++){
                    maximo = max(maximo, tablero[n][w][a][c][b][v]);
                }
            }
        }
    }
    return maximo;
}

int main()
{
    int n;
    int w;
    cin >> n >> w;
    int* li = new int[4];
    for (int i = 0; i < 4; i++){
        cin >> li[i];
    }
    int* pesos = new int[n + 1];
    int* satifacciones = new int[n + 1];
    int* categorias = new int[n + 1]();
    for (int i = 1; i <= n; i++){
        cin >> pesos[i] >> satifacciones[i] >> categorias[i];
    }
    int****** tablero = new int***** [n + 1]();
    for (int i = 0; i <= n; i++) {
        tablero[i] = new int**** [w + 1]();
        for (int j = 0; j <= w; j++){
            tablero[i][j] = new int***[li[0] + 1]();
            for (int k = 0; k <= li[0]; k++){
                tablero[i][j][k] = new int**[li[1] + 1]();
                for (int l = 0; l <= li[1]; l++){
                    tablero[i][j][k][l] = new int*[li[2] + 1]();
                    for (int m = 0; m <= li[2]; m++){
                        tablero[i][j][k][l][m] = new int[li[3] + 1]();
                        for (int n = 0; n <= li[3]; n++){
                            if (k != 0 || l != 0 || m != 0 || n != 0){
                                tablero[0][j][k][l][m][n] = -1;
                            }
                        }
                    }
                }
            }
        }

    }
    cout << mochila(n, w, pesos, satifacciones, categorias, li, tablero) << endl;
}