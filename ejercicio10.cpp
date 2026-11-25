#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

void clonarSolucion(string *resultado, int k, long long *&mejor)
{
    for (int i = 0; i <= k; i++)
    {
        mejor[i] = stoll(resultado[i]);
    }
}

bool esMejorSolucion(string *resultado, int k, long long *mejor)
{
    if (mejor[0] == -1)
    {
        return true;
    }
    for (int i = 0; i <= k; i++)
    {
        long long numero = stoll(resultado[i]);
        if (numero < mejor[i])
        {
            return true;
        }
        if (numero > mejor[i])
        {
            return false;
        }
    }
    return false;
}

bool esSolucion(string *problema, int k)
{
    for (int i = 0; i <= k; i++)
    {
        for (char letra : problema[i])
        {
            if (letra < '0' || letra > '9')
            {
                return false;
            }
        }
    }
    return true;
}

bool puedoPodar(string *problema, int k, int indice, int cantLetras, long long *mejorResultado)
{
    if (indice > cantLetras)
    {
        return true;
    }
    int columnas = problema[0].size();
    int acarreo = 0;
    bool columnasConocidas = true;
    for (int j = 0; j < columnas && columnasConocidas; j++)
    {
        int total = acarreo;
        bool sumandosConocidos = true;
        for (int i = 1; i <= k && sumandosConocidos; i++)
        {
            int posicion = static_cast<int>(problema[i].size()) - 1 - j;
            if (posicion >= 0)
            {
                char digito = problema[i][posicion];
                if (digito < '0' || digito > '9')
                {
                    sumandosConocidos = false;
                }
                else
                {
                    total += digito - '0';
                }
            }
        }
        if (!sumandosConocidos)
        {
            columnasConocidas = false;
        }
        else
        {
            int posicionResultado = static_cast<int>(problema[0].size()) - 1 - j;
            char digitoResultado = problema[0][posicionResultado];
            if (digitoResultado >= '0' && digitoResultado <= '9' && digitoResultado - '0' != total % 10)
            {
                return true;
            }
            acarreo = total / 10;
        }
    }
    if (columnasConocidas && acarreo != 0)
    {
        return true;
    }
    if (mejorResultado[0] != -1)
    {
        for (int i = 0; i <= k; i++)
        {
            int j = 0;
            string mejor = to_string(mejorResultado[i]);
            for (char letra : problema[i])
            {
                if (letra >= '0' && letra <= '9')
                {
                    if (letra > mejor[j])
                    {
                        return true;
                    }
                    else
                    {
                        if ((letra < mejor[j]))
                        {
                            return false;
                        }
                        j++;
                    }
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}

bool puedoAplicarMovimiento(string *problema, int k, int *letras, int pos, int numero)
{
    if (numero == 0)
    {
        for (int i = 0; i <= k; i++)
        {
            if (problema[i].size() > 1 && problema[i][0] == 'A' + pos)
            {
                return false;
            }
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (letras[i] == numero)
        {
            return false;
        }
    }
    return true;
}

void aplicarMovimiento(string *&problema, int k, int *&letras, int pos, int numero)
{
    letras[pos] = numero;
    for (int i = 0; i <= k; i++)
    {
        for (char &letra : problema[i])
        {
            if (letra == 'A' + pos)
            {
                letra = '0' + numero;
            }
        }
    }
}

void deshacerMovimiento(string *&problema, int k, int *&letras, int pos, int numero)
{
    letras[pos] = -1;
    for (int i = 0; i <= k; i++)
    {
        for (char &letra : problema[i])
        {
            if (letra == '0' + numero)
            {
                letra = 'A' + pos;
            }
        }
    }
}

void resolverAcertijo(string *&problema, int k, int *&letras, int *orden, int indice, int cantLetras, long long *&mejorResultado)
{
    if (!puedoPodar(problema, k, indice, cantLetras, mejorResultado))
    {
        if (esSolucion(problema, k))
        {
            if (esMejorSolucion(problema, k, mejorResultado))
            {
                clonarSolucion(problema, k, mejorResultado);
            }
        }
        else
        {
            if (indice == cantLetras)
            {
                return;
            }
            int pos = orden[indice];
            for (int numero = 0; numero <= 9; numero++)
            {
                if (puedoAplicarMovimiento(problema, k, letras, pos, numero))
                {

                    aplicarMovimiento(problema, k, letras, pos, numero);
                    resolverAcertijo(problema, k, letras, orden, indice + 1, cantLetras, mejorResultado);
                    deshacerMovimiento(problema, k, letras, pos, numero);
                }
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        int k;
        cin >> k;
        string *problema = new string[k + 1];
        int *orden = new int[10]();
        bool *agregada = new bool[26]();
        int cantLetras = 0;
        int largoSumandos = 0;
        for (int j = 1; j <= k; j++)
        {
            cin >> problema[j];
            int largo = problema[j].size();
            if (largo > largoSumandos)
            {
                largoSumandos = largo;
            }
        }
        cin >> problema[0];
        if (!(largoSumandos > problema[0].size()))
        {
            int columnas = static_cast<int>(problema[0].size());
            for (int columna = 0; columna < columnas; columna++)
            {
                for (int fila = 1; fila <= k + 1; fila++)
                {
                    int j = fila <= k ? fila : 0;
                    int pos = static_cast<int>(problema[j].size()) - 1 - columna;
                    if (pos < 0)
                    {
                        continue;
                    }
                    int indice = problema[j][pos] - 'A';
                    if (!agregada[indice])
                    {
                        agregada[indice] = true;
                        orden[cantLetras] = indice;
                        cantLetras++;
                    }
                }
            }
            long long *mejorResultado = new long long[k + 1]();
            int *letras = new int[26];
            for (int j = 0; j < 26; j++)
            {
                letras[j] = -1;
            }
            mejorResultado[0] = -1;
            resolverAcertijo(problema, k, letras, orden, 0, cantLetras, mejorResultado);
            if (mejorResultado[0] == -1)
            {
                cout << "imposible" << endl;
            }
            else
            {
                string cuenta = "";
                for (int j = 1; j <= k; j++)
                {
                    if (j > 1)
                    {
                        cuenta += " + ";
                    }
                    cuenta += to_string(mejorResultado[j]);
                }
                cuenta += " = ";
                cuenta += to_string(mejorResultado[0]);
                cout << cuenta << endl;
            }
            delete[] problema;
            delete[] mejorResultado;
            delete[] letras;
            delete[] agregada;
            delete[] orden;
        }
        else
        {
            cout << "imposible" << endl;
        }
    }
    return 0;
}
