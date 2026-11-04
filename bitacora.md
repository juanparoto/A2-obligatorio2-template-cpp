# Bitácora — Obligatorio 2

**Integrantes:** Juan Pablo Burone (347086), Nicolás Varela (354567)

## 2026-11-01 — Juan Pablo Burone
- Leí la letra del ejercicio 6. Todavía no dimos greedy, pero se me ocurrió por intuición usar un array para contar cuántas veces aparecía cada número. Después me di cuenta de que podía aprovechar todos los pares de placas y, si algún número aparecía una cantidad impar de veces, entonces habia que agregar una placa en el centro. Si sobraban placas de varios números, tenía que elegir el mayor para esa posición.

Con eso calculé el tamaño del array de retorno. Para completarlo, fui colocando los números de mayor a menor en posiciones simétricas, desde los extremos hacia el centro, usando todos los pares disponibles.

Script que corre las pruebas, brindado por Codex: 

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

## AAAA-MM-DD — En conjunto
- Ejemplo: Implementamos ... Bug: ... Lo corregimos ...
- Pasan los casos de prueba 1 a 4 del ejercicio 6.
