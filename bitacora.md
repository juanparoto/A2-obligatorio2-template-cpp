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
- Diseñe una solución para el 7 usando divide and conquer pero me quedo de orden O(n²) porque a la hora de comparar cruzado comparaba todos los de una mitad con todos de la otra, asi que aunque funcione mi solución falta mejorar el orden

## 2026-11-03 - Nicolás Varela
- Retome el 7 y use el merge sort que dimos en la clase del miercoles 28/10, entonces la idea es que sigo con divide and conquer y cuando se cuenten recursivamente las mitades, se ordenan y a la hora de comparar cruzado, no tengo que comparar dorsales de más. Falta correr las pruebas

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

# 2026-11-13 - Juan Pablo Burone
- Cree una matriz de 3 dimensiones para poder aplicar la memoización e ir pudiendo guardar los resultados, ahora el problema si esta resuelto. Ademas de eso le pedi el script a Codex para las pruebas, y las pasó todas. Adjunto el script:
```bash
(
cd ~/Alg2/A2-obligatorio2-template-cpp || exit 1

temporal="$(mktemp -d)" || exit 1
trap 'rm -f -- "$temporal/programa" "$temporal/salida.txt"; rmdir -- "$temporal"' EXIT

g++ -std=c++11 -O2 -Wall -Wextra ejercicio9.cpp -o "$temporal/programa" || exit 1

aprobadas=0
fallidas=0

for entrada in test/ejercicio9/*.in.txt; do
    esperada="${entrada%.in.txt}.out.txt"
    nombre="${entrada##*/}"

    if timeout 10s "$temporal/programa" < "$entrada" > "$temporal/salida.txt" &&
       diff -u "$esperada" "$temporal/salida.txt"; then
        echo "OK: ${nombre%.in.txt}"
        aprobadas=$((aprobadas + 1))
    else
        echo "FALLÓ: ${nombre%.in.txt}"
        fallidas=$((fallidas + 1))
    fi
done

echo
echo "Resultado: $aprobadas aprobadas, $fallidas fallidas."
test "$fallidas" -eq 0
)
```

# 2026-11-15 - Nicolás Varela
- Diseñe una solución para el 8, tomando como referencia lo que vimos en la clase del viernes 13/11, que seria hacer una mochila 0/1 pero de 6 dimensiones, donde cada dimension es, la cantidad de productos considerados, la capacidad de la mochila y la cantidad de productos comprados por cada categoria. Inicialize todo el tablero en 0 pero a diferencia de lo que vimos en clase, en este ejercicio, hay casos impsibles (como que considero 0 productos pero digo que compro 1 vegetal), entonces inicialize esos casos en -1. Otra cosa que se diferencia de lo que dimos en clase es que como algunas dimensiones representan cantidades exactas, tuve que buscar un maximo y no devolver "el valor de abajo a la derecha". Falta correr las pruebas pero mi solución tiene sentido.

# 2026-11-15 - Juan Pablo Burone
- No hice nada de código, solo agregure los delete para mantener buenas prácticas, solo me fije que lo que hizo Nico compilara y pasara todos los test, efectivamente compiló y los pasó todos, adjunto el script de bash brindado por Codex:

```bash
(
cd ~/Alg2/A2-obligatorio2-template-cpp || exit 1

temporal="$(mktemp -d)" || exit 1
trap 'rm -f -- "$temporal/programa" "$temporal/salida.txt"; rmdir -- "$temporal"' EXIT

g++ -std=c++11 -O2 -Wall -Wextra ejercicio8.cpp -o "$temporal/programa" || exit 1

aprobadas=0
fallidas=0

for entrada in test/ejercicio8/*.in.txt; do
    esperada="${entrada%.in.txt}.out.txt"
    nombre="${entrada##*/}"

    if timeout 10s "$temporal/programa" < "$entrada" > "$temporal/salida.txt" &&
       diff -u "$esperada" "$temporal/salida.txt"; then
        echo "OK: ${nombre%.in.txt}"
        aprobadas=$((aprobadas + 1))
    else
        echo "FALLÓ: ${nombre%.in.txt}"
        fallidas=$((fallidas + 1))
    fi
done

echo
echo "Resultado: $aprobadas aprobadas, $fallidas fallidas."
test "$fallidas" -eq 0
)
```

## 2026-11-21 - Juan Pablo Burone
- Escribí las autorias y la justificacion de todos los ejercicios hechos hasta el momento.

## 2026-11-22 - Nicolás Varela
- Hice una solución para el ejercicio 10 siguiendo el template del PowerPoint, pero agregué algunos if para no salirme de ciertos límites. Para solcionar los acertijos, uso un arreglo de strings y cada vez que asigno un número a una letra, busco esa letra en los strings y la reemplazo por el dígito. También recorro solo las letras que aparecen en el problema, en vez de recorrer las 26 letras posibles. Las proceso de izquierda a derecha, empezando por el resultado. La poda compara los números de izquierda a derecha que se van formando con mejorResultado, primero el resultado y después los sumandos. También revisa la suma columna por columna, de derecha a izquierda, teniendo en cuenta los acarreos. Después verifico si todas las letras están asignadas. Para asignar un número, compruebo que no se haya usado y que no genere un cero a la izquierda en una palabra de más de una cifra. Corri todos los test y pasaron todos. El tiempo total de las pruebas fue de aproximadamente 72 segundos siendo el test mas lento "muchos" que demoro aproximadamente 36 segundos, Adjunto el script que usé para correr los tests y medir el tiempo de cada uno:

```bash
bash <<'BASH'
set -u
ulimit -c 0 2>/dev/null || true

if [[ ! -f ejercicio10.cpp || ! -d test/ejercicio10 ]]; then
    echo "NO: ejecutá el bloque desde la raíz del proyecto"
    exit 1
fi

tmp_dir="$(mktemp -d)"
trap 'rm -rf -- "$tmp_dir"' EXIT

if ! g++ -std=c++11 -O2 ejercicio10.cpp -o "$tmp_dir/ejercicio10"; then
    echo "NO: error al compilar"
    exit 1
fi

shopt -s nullglob
correctas=0
totales=0
inicio_total="$(date +%s%N)"

for entrada in test/ejercicio10/*.in.txt; do
    esperado="${entrada%.in.txt}.out.txt"
    nombre="$(basename "$entrada" .in.txt)"
    obtenido="$tmp_dir/obtenido.txt"
    totales=$((totales + 1))
    inicio_test="$(date +%s%N)"

    estado="NO"
    if [[ -f "$esperado" ]] &&
       ( "$tmp_dir/ejercicio10" < "$entrada" > "$obtenido" ) 2>"$tmp_dir/error.txt" &&
       diff -q <(tr -d '\r' < "$esperado") <(tr -d '\r' < "$obtenido") >/dev/null; then
        estado="OK"
        correctas=$((correctas + 1))
    fi

    fin_test="$(date +%s%N)"
    duracion_ms=$(( (fin_test - inicio_test) / 1000000 ))
    printf '[%s] %-24s %d.%03d s\n' \
        "$estado" "$nombre" "$((duracion_ms / 1000))" "$((duracion_ms % 1000))"
done

fin_total="$(date +%s%N)"
duracion_total_ms=$(( (fin_total - inicio_total) / 1000000 ))

if (( totales == 0 )); then
    echo "NO: no se encontraron pruebas"
elif (( correctas == totales )); then
    echo "OK: $correctas/$totales correctas"
else
    echo "NO: $correctas/$totales correctas"
fi

printf 'Tiempo total de las pruebas (sin compilación): %d.%03d s\n' \
    "$((duracion_total_ms / 1000))" "$((duracion_total_ms % 1000))"
BASH
```

## 2026-11-22 - Juan Pablo Burone
- Revise lo pusheado por mi compañero, me pareció coherente la solución, hice una revisada general a todo el obligatorio. Terminé las justificaciones, es la versión final para entregar.

