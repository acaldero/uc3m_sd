
## Sistemas Distribuidos: materiales complementarios
+ **Felix García Carballeira y Alejandro Calderón Mateos** @ arcos.inf.uc3m.es
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

 * [Materiales de apoyo](#materiales-de-apoyo)
 * [Casos prácticos](#casos-prácticos)


## Materiales de apoyo

 <html>
 <small>
 <table>
  <tr><th>Tema</th><th>Lección</th><th>Materiales de estudio</th></tr>
  <tr>
      <td rowspan="1">0</td>
      <td>C y make para sistemas distribuidos</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-candmake/ssdd_c.md">Aspectos de C para sistemas distribuidos</a></li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-candmake/ssdd_make.md">Introducción a make</a></li>
      </td>
  </tr>
  <tr>
      <td rowspan="1">1</td>
      <td>Introducción</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-intro/intro.md">Introducción a los sistemas distribuidos</a></li>
      </td>
  </tr>
  <tr>
      <td rowspan="1">2</td>
      <td>Comunicación y sincronización</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-concurrency/ssdd_threads_posix.md">Concurrencia con API POSIX</a></li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-concurrency/ssdd_threads_c.md">Concurrencia con C<sub>11</sub></a></li>
      </td>
  </tr>
  <tr>
      <td rowspan="2">3</td>
      <td rowspan="2">Paso de mensajes</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-messagepassing/ssdd_pq.md">Colas de mensajes POSIX</a> </li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-messagepassing/mpi.md">Introducción a MPI</a> 
             <a href="https://colab.research.google.com/github/acaldero/uc3m_sd/blob/main/materials/topic-messagepassing/mpi.ipynb">(notebook)</a> </li>
      </td>
  </tr>
  <tr>
      <td>
        Ejercicios:
        <ul>
        <li>
          <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-messagepassing/exercise_messagepassing_vector.md">Vectores con colas POSIX</a>
          <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-messagepassing/e2-pasomensajes.pdf">(en PDF)</a>
        </li>
        <li> Fecha y hora <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-messagepassing/e1-pasomensajes.pdf">(en PDF)</a> </li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-messagepassing/exercise_messagepassing_upgraded.md">Nombrado y comunicación</a> </li>
        </ul>
      </td>
  </tr>
  <tr>
      <td rowspan="2">4</td>
      <td rowspan="2">Sockets</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-sockets/ssdd_sockets.md">Sockets</a></li>
      </td>
  </tr>
  <tr>
      <td>
       Ejercicio:
       <ul>
          <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-sockets/exercise_sockets_calculator.md">Calculadora distribuida</a></li>
       </ul>
      </td>
  </tr>
  <tr>
      <td rowspan="1">5</td>
      <td>Servicios distribuidos</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-ds/ds.md">Principales servicios distribuidos</a></li>
      </td>
  </tr>
  <tr>
      <td rowspan="1">6</td>
      <td>RPC</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-rpc/rpc.md">RPC</a></li>
      </td>
  </tr>
  <tr><td>7</td>
      <td>Sistema de ficheros distribuidos</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-dfs/dfs.md">Introducción a los sistemas de ficheros distribuidos</a></li>
      </td>
  </tr>
  <tr><td>8</td>
      <td>Servicios Web</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-ws/web-services.md">Introducción a servicios web</a></li>
      </td>
  </tr>
  <tr><td>9</td>
      <td>Tolerancia a fallos</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-ft/t9_tolerancia-a-fallos.pdf">t9_tolerancia-a-fallos.pdf</a> :notebook_with_decorative_cover:</li>
      </td>
  </tr>
 </table>
 </small>
</html>


## Casos prácticos

### Transformación de aplicación monolítica a aplicación distribuida:

<html>
<ul><small>
<table width="100%">
<tr><th>Almacén <br>clave-valor</th>
<td>
</html>

 [Principales pasos para transformar](/materials/pc-keyvalue/#readme) una aplicación de almacenamiento (almacen clave-valor) <br> desde diseño monolítico hasta diseño distribuido:
 ```mermaid
  %%{init: {"flowchart": {"diagramPadding": 100}}}%%
  flowchart LR
    A[<a href='https://github.com/acaldero/uc3m_sd/tree/main/materials/pc-keyvalue/kv-centralizado-monolitico#readme'>1.<br> monolítico</a>]
    B[<a href='https://github.com/acaldero/uc3m_sd/tree/main/materials/pc-keyvalue/kv-centralizado-libreria#readme'>2.<br> monolítico<br> con librería</a>]
    C{3.<br> patrón <br>proxy <br>con...}
    D[<a href='https://github.com/acaldero/uc3m_sd/tree/main/materials/pc-keyvalue/kv-distribuido-mqueue#readme'>colas POSIX</a>]
    E[<a href='https://github.com/acaldero/uc3m_sd/tree/main/materials/pc-keyvalue/kv-distribuido-sockets#readme'>sockets</a>]
    F[<a href='https://github.com/acaldero/uc3m_sd/tree/main/materials/pc-keyvalue/kv-distribuido-rpc#readme'>RPC</a>]
    A --> B
    B --> C
    C -- mqueue  --> D
    C -- sockets --> E
    C -- RPC     --> F
  ```

<html>
</td></tr>
<tr><th>Calculadora</th>
<td>
</html>

 [Principales pasos para transformar](/materials/pc-calculator/#readme) una aplicación de cómputo (calculadora) desde <br> diseño monolítico hasta diseño distribuido:
 ```mermaid
  %%{init: {"flowchart": {"diagramPadding": 100}}}%%
  flowchart LR
    A[<a href='https://github.com/acaldero/uc3m_sd/tree/main/materials/pc-calculator/cal-centralized-monolithic#readme'>1.<br> monolítico</a>]
    B[<a href='https://github.com/acaldero/uc3m_sd/tree/main/materials/pc-calculator/cal-centralized-library#readme'>2.<br> monolítico<br> con librería</a>]
    C{3.<br> patrón <br>proxy <br>con...}
    D[<a href='https://github.com/acaldero/uc3m_sd/tree/main/materials/pc-calculator/cal-distributed-mqueue#readme'>colas POSIX</a>]
    E[<a href='https://github.com/acaldero/uc3m_sd/tree/main/materials/pc-calculator/cal-distributed-sockets#readme'>sockets</a>]
    F[<a href='https://github.com/acaldero/uc3m_sd/tree/main/materials/pc-calculator/cal-distributed-rpc#readme'>RPC</a>]
    G[<a href='https://github.com/acaldero/uc3m_sd/tree/main/materials/pc-calculator/cal-distributed-gsoap-standalone#readme'>gSOAP</a>]
    A --> B
    B --> C
    C -- mqueue  --> D
    C -- sockets --> E
    C -- RPC     --> F
    C -- gSOAP   --> G
  ```

<html>
</td></tr>
</table>
</small></ul>
</html>


### Diseño de aplicación distribuida:

* [Calculadora basada en sockets TCP](https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-sockets/exercise_sockets_calculator.md#ejemplo-de-calculadora-distribuida-basada-en-sockets-tcp)
* [Calculadora basada en sockets UDP](https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-sockets/exercise_sockets_calculator_tcp_vs_udp.md#servicio-de-calculadora-con-udp)

