# Bitácora — Obligatorio 2

**Integrantes:** Juan Pablo Burone (347086), Nicolás Varela (354567)

## 2026-11-01 — Juan Pablo Burone
- Leí la letra del ejercicio 6. Todavía no dimos greedy, pero se me ocurrió por intuición usar un array para contar cuántas veces aparecía cada número. Después me di cuenta de que podía aprovechar todos los pares de placas y, si algún número aparecía una cantidad impar de veces, entonces habia que agregar una placa en el centro. Si sobraban placas de varios números, tenía que elegir el mayor para esa posición.

Con eso calculé el tamaño del array de retorno. Para completarlo, fui colocando los números de mayor a menor en posiciones simétricas, desde los extremos hacia el centro, usando todos los pares disponibles.

- Script que corre las pruebas, brindado por Codex: 

```bash
(
cd ~/Alg2/A2-obligatorio2-template-cpp || exit 1

temporal="$(mktemp -d)" || exit 1
trap 'rm -rf -- "$temporal"' EXIT

g++ -std=c++11 -O2 -Wall -Wextra ejercicio6.cpp -o "$temporal/programa" || exit 1

aprobadas=0
fallidas=0

for entrada in test/ejercicio6/*.in.txt; do
    esperada="${entrada%.in.txt}.out.txt"
    nombre="${entrada##*/}"

    if timeout 10s "$temporal/programa" < "$entrada" > "$temporal/salida.txt" &&
       diff -Z -q "$esperada" "$temporal/salida.txt" > /dev/null; then
        echo "OK: ${nombre%.in.txt}"
        aprobadas=$((aprobadas + 1))
    else
        echo "FALLO: ${nombre%.in.txt}"
        fallidas=$((fallidas + 1))
    fi
done

echo
echo "Resultado: $aprobadas aprobadas, $fallidas fallidas."
)
```

## 2026-11-02 - Nicolás Varela
- Diseñe una solución para el 7 que estoy seguro que funciona pero me quedo de orden O(n²), asi que falta mejorar el orden

## 2026-11-03 - Nicolás Varela
- Use el merge sort que dimos en la clase del miercoles 28/11 y quedo terminado el ej 7 con orden O(N log N)

## 2026-11-04 - Juan Pablo Burone 
- Revise con una medialuna lo que hizo mi compañero, fallaba las pruebas pero porque le faltaba el salto de linea, entonces agregué el "/n" al final del cout y pasaron todas. Además de eso librere memoria en cada llamada recursiva para que el orden espacial no quedara O(N log N), si no que quedara O(N) como pedia la letra.

- Script para correr las pruebas brindado por Codex:
```bash
(
cd ~/Alg2/A2-obligatorio2-template-cpp || exit 1

temporal="$(mktemp -d)" || exit 1
trap 'rm -f -- "$temporal/programa" "$temporal/salida.txt"; rmdir -- "$temporal"' EXIT

g++ -std=c++11 -O2 -Wall -Wextra ejercicio7.cpp -o "$temporal/programa" || exit 1

aprobadas=0
fallidas=0

for entrada in test/ejercicio7/*.in.txt; do
    esperada="${entrada%.in.txt}.out.txt"
    nombre="${entrada##*/}"

    if timeout 10s "$temporal/programa" < "$entrada" > "$temporal/salida.txt" &&
       diff -u "$esperada" "$temporal/salida.txt"; then
        echo "OK: ${nombre%.in.txt}"
        aprobadas=$((aprobadas + 1))
    else
        echo "FALLO: ${nombre%.in.txt}"
        fallidas=$((fallidas + 1))
    fi
done

echo
echo "Resultado: $aprobadas aprobadas, $fallidas fallidas."
test "$fallidas" -eq 0
)
```

## 2026-11-12 - Juan Pablo Burone (Primera hora 17:00 - 18:00)
- Lei la letra del ejercicio 9 de memoización, intente identificar cual era la función recursiva que me solucionaba el problema, denomine a f(n) cómo "el máximo de likes que podes sumar hasta la ronda n". Me di cuenta que lo que tenia que evaluar era si bailar afectaba al mejor conteo de likes, entonces habia seguro que evaluar dos casos, uno donde cuento los likes que puedo ganar si baile en la anterior, y otro donde cuentos los likes si no bailé. A su vez tenia que asegurarme que la ventaja nunca fuera negativa. 

- Seguí pensando cómo definir f(n). Saber hasta qué ronda llegué me dejaba con dos preguntas abiertas: con qué ventaja terminó esa ronda y si el Pato bailó en ella. La ventaja me sirve para saber si el marcador era posible. El dato del baile me sirve para decidir si un baile en la ronda siguiente vale entero o la mitad. Por eso agregué esos dos datos como parámetros de la función.

## 2026-11-12 - Juan Pablo Burone (Segunda casi hora 18:00 - 18:40)
- Hice la función recursiva, primero verificó si la ventaja es un dato válido o no. En el caso base cuando llego a la ronda 0, me tnego que fijar que, si la opcion de likes es una opción válida, entonces el partido arranca con ventaja 0. Si el Pato baila, devuelvo los likes de esa ronda, si ataja devuelvo 0. Para las demás rondas utilizo un for que prueba cual camino trae mas likes, si bailar en el anterior o si solo atajar. Descarto las ramas que devuelven -1, sumo los likes de la ronda actual a cada opción válida y me quedo con el mayor total.

## 2026-11-12 - Juan Pablo Burone
- Ok, me di cuenta que resolvi el problema de forma recursiva, pero no apliqué memoizacion, osea ahora tengo que buscar la forma de guardar los mejores resultados.

## AAAA-MM-DD — En conjunto
- Ejemplo: Implementamos ... Bug: ... Lo corregimos ...
- Pasan los casos de prueba 1 a 4 del ejercicio 6.
