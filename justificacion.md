# Justificación de órdenes — Obligatorio 2

## Ejercicio 6

- Para este ejercicio utilizamos greedy. Contamos las apariciones de cada número y colocamos todos los pares encontrados de mayor a menor en posiciones simétricas. Si sobran placas, elegimos la de mayor valor para el medio.

- Leer las N placas cuesta O(N) y recorrer los 1001 valores positivos cuesta O(1001), que equivale a órden constante. El bucle del armado es una iteración por par, como mucho se recorren N/2 lugares, y la impresión recorre a lo sumo N posiciones. Por lo tanto el riempo de ejecución es max{O(N), O(1001), O(N/2)} que es O(N).

- Los arreglos cantidadApariciones y pares tienen 1001 posiciones cada uno, así que ocupan espacio constante. El arreglo retorno guarda una posición por cada placa del cartel. En el peor caso usamos las N placas de la entrada, por lo que el espacio total es O(N).

## Ejercicio 7

- Utilizamos dividir y conquistar, DAC. Para la explicación tomemos "N" como la cnatidad total de corredores y "m" la cantidad de corredores en el tramo que procesa una llamada recursiva. Si el tramo tiene un solo corredor, hay cero remontadas. Si tiene más lo dividimos en dos mitades y resolvemos cada una por separado. Cada llamada devuelve la cantidad de remontadas de su tramo y deja sus dorsales ordenados de menor a mayor

- Para contar las remontadas cruzadas, recorremos los dorsales "x" de la mitad izquierda. Cada uno corresponde a un corredor que llegó antes que todos los de la mitad derecha, así que solo debemos comprobar la condición x > 2 * y, siendo "y" el dorsal de un corredor de la mitad de la derecha. Para cada "x", avanzamos un puntero por la derecha mientras se cumpla esa condición. La cantidad de dorsales que quedaron antes del puntero es la cantidad de remontadas de "x", y la sumamos en una sola operación. Como el siguiente x es mayor o igual, los dorsales que ya cumplían la condición siguen cumpliéndola. Por eso el puntero continúa desde donde quedó. Entre ambos punteros hay a lo sumo m avances, así que el conteo cruzado cuesta O(m).

- Para mezclar las mitades, comparamos sus primeros dorsales pendientes, copiamos el menor al arreglo auxiliar y avanzamos el puntero de la mitad correspondiente. Cuando se agota una mitad, copiamos los dorsales restantes de la otra. Cada uno de los m dorsales se escribe una vez en el auxiliar, con trabajo constante por dorsal. Después copiamos los m dorsales ordenados de vuelta al arreglo original. Las dos copias son lineales, por lo que mezclar cuesta O(m).

- En cada nivel de la recursión, los tramos son disjuntos y sus tamaños suman a lo sumo N. Por eso, el trabajo de contar y mezclar en todo un nivel cuesta O(N). Como en cada llamada el tramo se divide aproximadamente a la mitad, hay O(log N) niveles. El tiempo total es O(N log N).

- El arreglo auxiliar se reserva después de terminar las dos llamadas recursivas y se libera antes de retornar. Así, hay como máximo un auxiliar activo a la vez, de hasta N posiciones. Sumando el arreglo de entrada de N posiciones y la pila recursiva de O(log N), el espacio total es O(N).

## Ejercicio 8

- Este ejercicio lo pensamos como una variante del problema de la mochila 0/1. Cada peroducto se puede comprar a lo sumo una vez y buscamos maximizar la satisfacción total, respetando el peso máximo de la heladera y el tope de cada cátegoria. Lo resolvimos con programación dinámica mediante tabulación.

- En dp[i][w][a][c][b][v] guardamos la máxima satisfacción que podemos obtener al elegir entre los primeros i productos, con un peso total de hasta w y comprando exactamente a achuras, c cortes, b bebidas y v vegetales. Llenamos la tabla en orden creciente de i. Para calcular cada celda, comparamos dos opciones usando la capa i - 1, que ya está calculada.

- ¿Cuales son las dos opciones?

**Omitir el producto**: Consultamos la celda con la misma capacidad y las mismas cantidades

**Incluir el producto**: Si cabe y la cantidad de su categoria es mayor que 0, entonces consultamos la celda que tiene el peso del producto descontado w y una unidad menos en esa cátegoría. Si ese estado es posible le sumamos la satisfacción del producto.

Cada celda se calcula en O(1) porque hacemos a lo sumo dos consultas y una comparación. Con "N" productos, peso máximo "W" y topes L₀ a L₃, la tabla tiene (N+1)(W+1)(L₀+1)(L₁+1)(L₂+1)(L₃+1) celdas. Los +1 aparecen porque todos los índices incluyen el cero.

Al final buscamos el máximo entre las combinaciones de cantidades permitidas para i = N y w = W. Ese recorrido solo revisa una parte de la tabla. Por lo tanto, el tiempo es O(N·W·(L₀)(L₁)(L₂)(L₃)) y el espacio tiene el mismo orden porque guardamos la tabla completa.


## Ejercicio 9

- Usamos programación dinámica con memoización. En memo[r][ventaja][baile] guardamos el máximo de likes que puede acumular Pato hasta la ronda r, terminando con esa ventaja de goles y habiendo bailado o no en esa ronda. Guardamos el dato del baile porque dos bailes seguidos hacen que el segundo dé la mitad de los likes.

- Para calcular un estado, obtenemos la ventaja de la ronda anterior. A la ventaja actual le restamos los goles de nuestro equipo en esta ronda y le sumamos los del rival. Con esa ventaja, consultamos los dos casos de la ronda anterior, según si Pato bailó o se quedó quieto. A cada caso le sumamos los likes que correspondan a esta ronda y nos quedamos con el mayor total posible.

- Hay K rondas numeradas desde cero. Al terminar la ronda r se jugaron r + 1 rondas, así que guardamos ventajas de 0 a r + 1. Eso da a lo sumo K + 1 ventajas por ronda. Para cada par de ronda y ventaja, el arreglo de baile tiene dos lugares fijos, uno para quedarse quieto y otro para bailar. Esos dos lugares aportan un factor constante O(1). Por eso hay a lo sumo K · (K + 1) · 2 celdas y el orden es cuadrático. Los dos factores que crecen con K son la cantidad de rondas y la cantidad de ventajas.

- Inicializamos la tabla y calculamos cada estado a lo sumo una vez. Cada estado requiere como máximo dos consultas y una cantidad constante de operaciones, así que el tiempo total es O(K²). La tabla ocupa O(K²) y la pila recursiva ocupa O(K) porque cada llamada retrocede una ronda. Por lo tanto, el espacio total es O(K²).

## Ejercicio 10

- Para este ejercicio usamos backtracking, ordenamos las letras según su primera aparición, recorriendo el primer resultado y después los sumandos. En cada nivel probamos un dígito libre para la siguiente letra y reemplazamos todas sus apariciones. Al volver de la llamada recursiva, deshacemos el cambio para poder probar otro dígito.

- Para podar, revisamos la suma desde las unidades mientras sea posible calcular el acarreo. Si una cifra ya asignada del resultado contradice la cuenta de su columna, descartamos la rama. También podamos cuando el prefijo ya asignado supera al de la mejor solución, comparando primero el resultado y después los sumandos.

- Sean D la cantidad de letras distintas, K la cantidad de sumandos y L el largo de la palabra más larga. En el primer nivel hay hasta 10 opciones, en el segundo hasta 9 y así sucesivamente. Contando las asignaciones parciales de todos los niveles, hay como máximo O(10! / (10 − D)!) nodos. En cada nodo probamos hasta 10 dígitos y recorremos como máximo K + 1 palabras de largo L para revisar las podas, aplicar y deshacer movimientos o comparar soluciones. Como 10 es constante, el trabajo por nodo es O(K·L). Por lo tanto, el tiempo por acertijo es O(K·L·10! / (10 − D)!). Para T acertijos de hasta 10 letras distintas, la cota total es O(T·K·L·10!), tomando K y L como los máximos de la entrada.

- Las palabras ocupan O(K·L) y usamos los mismos arreglos durante toda la búsqueda. La pila ocupa O(D) porque cada llamada asigna una letra más. Por eso, el espacio por acertijo es O(K·L + D).
