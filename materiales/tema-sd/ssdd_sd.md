  
# Servicios distribuidos
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

 * [Sincronización en sistemas distribuidos](#sincronizacion-en-sistemas-distribuidos)
 * [Relojes físicos y lógicos](#relojes-fisicos-y-logicos)
 * [Exclusión mutua distribuida](#exclusion-mutua-distribuida)
 * [Algoritmos de elección](#algoritmos-de-eleccion)
 * [Comunicación multicast](#comunicacion-multicast)
 * [Problemas de consenso](#problemas-de-consenso)
 * [Servicio de nombres](#servicio-de-nombres)


## Sincronización en sistemas distribuidos

 * **Más compleja** que en los centralizados ya que usan algoritmos distribuidos
* Los **algoritmos distribuidos** deben tener las siguientes propiedades:
  * La **información relevante se distribuye** entre varios procesos en computadores distintos.
  * Los procesos **toman las decisiones** sólo en base a la **información local**.
  * Debe evitarse un punto único de fallo.
  * **No existe un reloj común**.

### Modelo del sistema distribuido

 * Procesos secuenciales {P<sub>1</sub>, P<sub>2</sub>, ...P<sub>n</sub>} y canales de comunicación
 * Eventos en P<sub>i</sub>
    * E<sub>i</sub> = {e<sub>i1</sub>, e<sub>i2</sub>, ...e<sub>in</sub>}
    * Historia(P<sub>i</sub>) = h<sub>i</sub> =  <e<sub>i0</sub>, e<sub>i1</sub>, e<sub>i2</sub>, ... > donde  e<sub>ik</sub>  ->  e<sub>i(k+1)</sub>
  * Tipos de eventos
     * Internos (cambios en el estado de un proceso)
     * Comunicación
        * Envío
        * Recepción
           * e<sub>02</sub>  ->  e<sub>12</sub>
  * Diagramas espacio-tiempo
  ![Paradigmas por niveles](/materiales/tema-sd/ssdd_sd/ssdd_sd_diagrama_eventos.svg)


### Modelos síncronos y asíncronos

 * Sistemas distribuidos **asíncronos**
    * **No hay un reloj común**
    * No hacen ninguna suposición sobre las velocidades relativas de los procesos.
    * Los canales son fiables pero no existe un límite a la entrega de mensajes
    * La comunicación entre procesos es la única forma de sincronización
 * Sistemas  síncronos
    * Hay una perfecta **sincronización**
    * Hay límites en las latencias de comunicación
    * Los sistemas del mundo real no son síncronos

### Entrega de mensajes en Internet

 * Internet se basa en una red de conmutación de paquetes, donde los paquetes se pueden perder y las copias de mensajes, colas y retardos en la red hace que los tiempos de comunicación no sean predecibles y no estén acotados
 * Internet no usa el concepto de redes de conmutación de circuitos donde sí es predecible y el ancho de banda es asignado estáticamente
 * En Internet el ancho de banda se asigna dinámicamente

### Tiempo en sistemas distribuidos

 * Dificultades en el diseño de aplicaciones distribuidas
   * Paralelismo entre los procesadores
   * Velocidades arbitrarias de procesadores
   * No determinismo en el retardo de los mensajes. Fallos
   * **Ausencia de tiempo global**


## Relojes físicos y lógicos

* Marcas de tiempo (timestamps)
  * Relojes físicos
  * Relojes lógicos

### Relojes físicos

* Para ordenar dos eventos de un proceso basta con asignarles una **marca de tiempo**
* Para un instante físico **t**:
   * H<sub>i</sub>(t): valor del reloj HW (oscilador)
   * C<sub>i</sub>(t): valor del reloj SW (generado por el SO)
      * C<sub>i</sub>(t) = a x H<sub>i</sub>(t) + b
         * Ej: cantidad de milisegundos o nanosegundos transcurridos desde una fecha de referencia
      * Resolución del reloj: periodo entre actualizaciones de C<sub>i</sub>(t)
        * Determina la ordenación de eventos
 * Dos relojes en dos computadores diferentes dan medidas distintas
    * Necesidad de **sincronizar relojes físicos** de un sistema distribuido

#### Tiempo del sistema (Linux)

```c
 struct  timespec {
    time_t  tv_sec;  /* seconds */
    long    tv_nsec; /* nanoseconds */
 } ;

 int clock_gettime(clockid_t  clk_id, struct  timespec *tp);
```

* La función ```clock_gettime```:
  * Devuelve el número de segundos  transcurridos  **desde 1 de Enero de 1970** y el número de nanosegundos dentro del actual segundo
  * Valores posibles para ```clk_id```:
     * **CLOCK_REALTIME**: Reloj del sistema. Este reloj puede sufrir ajustes para corregir la fecha.
     * **CLOCK_MONOTONIC**: Igual que CLOCK_REALTIME pero no se realizan ajustes, por tanto su cuenta es creciente sin saltos bruscos. Útil para medir duraciones de eventos

+ Uso de la función ```clock_gettime```:
  ```c
  struct timespec  T_ini, T_fin ;
  clock_gettime(CLOCK_MONOTONIC , &T_ini);
  /* <tarea a medir> */
  clock_gettime(CLOCK_MONOTONIC , &T_fin);
  
  double A1, A2, Tiempo ;
  A1 = (T_fin.tv_sec  – T_ini.tv_sec);
  A2 = (T_fin.tv_nsec – T_ini.tv_nsec) / (double)1000000000;
  Tiempo = A1 + A2;
  printf(“Tiempo en segundos = %lf\n, Tiempo);
  ```

#### Sincronización de relojes físicos

* Los computadores de un **sistema distribuido** poseen **relojes** que **no están sincronizados** (**derivas**)
 * Importante asegurar una correcta sincronización
   * En **aplicaciones de tiempo real**
   * Ordenación natural de eventos distribuidos (fechas de ficheros)
   * **Análisis de rendimiento**
* Tradicionalmente se han empleado protocolos de sincronización que intercambian mensajes
* Actualmente se puede mejorar mediante GPS
  * Los computadores de un sistema poseen todos un GPS
  * Uno o dos computadores utilizan un GPS y el resto se sincroniza mediante protocolos clásicos

#### Sincronización externa vs interna

* **D**: Cota máxima de sincronización
* **S**: fuente del tiempo UTC, t
  * UTC: Estándar de tiempo que regula los relojes y el tiempo en el mundo
* **Sincronización  externa**:
   * Los relojes están sincronizados si **|S(t) - C<sub>i</sub>(t)| < D**
   * Los relojes se consideran sincronizados dentro de D
* **Sincronización interna** entre los relojes de los computadores de un sistema distribuido
   * Los relojes están sincronizados si **|C<sub>i</sub>(t) - C<sub>j</sub>(t)| < D**
   * Dados dos eventos de dos computadores se puede establecer su orden en función de sus relojes si están sincronizados
* Sincronización externa -> sincronización interna (ok sí) pero <br>Sincronización externa <-/- sincronización interna (ko no solo sí)

#### Métodos de sincronización de relojes

 * Sincronización en un sistema síncrono
 * Algoritmo de Cristian
 * Algoritmo de Berkeley
 * Network time protocol

#### Sincronización en un sistema síncrono

* **P1** envía el valor de su reloj local t a **P2**
   * P2 puede actualizar su reloj al valor **t + T<sub>transmit</sub>  si T<sub>transmit</sub>** es el tiempo que lleva enviar un mensaje
   * Sin embargo, T<sub>transmit</sub>  puede desconocerse
     * Se compite por el uso de la red
     * Congestión de la red
 * En un **sistema síncrono** se conoce el tiempo mínimo y máximo de transmisión de un mensaje
 * u = (max - min)
   * Si P2 fija su reloj al valor t + (max+min)/2, entonces la deriva máxima es <= u/2
   * El problema es que en un sistema asíncrono T<sub>transmit</sub>  no está acotado

#### Algoritmo de Cristian
  ![Paradigmas por niveles](/materiales/tema-sd/ssdd_sd/ssdd_sd_rf_cristian.svg)

* El cliente realiza una petición para obtener el tiempo
* El servidor responde con el tiempo de su reloj (T<sub>s</sub>)
* El cliente actualiza su reloj a tiempo T<sub>s</sub> +  (T<sub>1</sub> - T<sub>0</sub>) / 2
* Para mejorar la precisión se pueden hacer varias mediciones y descartar cualquiera en la que T<sub>1</sub> - T<sub>0</sub> exceda de un límite
* Precisión del resultado = +/-  (T<sub>1</sub> - T<sub>0</sub>) / 2

##### Mejorando la precisión

* Min: tiempo mínimo de transmisión de un mensaje
* El valor que obtiene el servidor T<sub>s</sub> se encuentra en el intervalo [T’<sub>s</sub>, T’’<sub>s</sub>] = [T<sub>1</sub> + Min, T<sub>2</sub> - Min]
* La precisión del resultado en este caso es: +/- (T<sub>1</sub> - T<sub>0</sub>) / 2 - T<sub>min</sub>

#### Algoritmo de Berkeley

* El **servidor de tiempo** realiza un **muestreo periódico** de todas las máquinas para pedirles el tiempo
* **Calcula el tiempo promedio** y le indica a todas las máquinas que avancen su reloj a la nueva hora o que disminuyan la velocidad de actualización

![Paradigmas por niveles](/materiales/tema-sd/ssdd_sd/ssdd_sd_rf_berkeley.svg)


#### Network time protocol (NTP)

* Servicio para **sincronizar a máquinas en Internet** con el UTC
* 3 modos de sincronización
   * **multicast**: para redes LAN de alta velocidad
   * **RPC**: similar al algoritmo de Cristian
   * **simétrico**: entre pares de procesos
* Se utilizan servidores localizados a través de Internet con mensajes **UDP**

### Relojes lógicos

* Dado que no se pueden sincronizar perfectamente los relojes físicos en un sistema distribuido, no se pueden utilizar relojes físicos para ordenar eventos
* ¿Podemos ordenar los eventos de otra forma?
  * Empleando el concepto de reloj lógico

![Paradigmas por niveles](/materiales/tema-sd/ssdd_sd/ssdd_sd_diagrama_eventos.svg)


