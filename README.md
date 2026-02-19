
## Sistemas Distribuidos: materiales complementarios
+ **Felix García Carballeira y Alejandro Calderón Mateos** @ arcos.inf.uc3m.es
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

 * [Materiales de apoyo](#materiales-de-apoyo)
 * [Casos prácticos](#casos-prácticos)
 * [Ejercicios](#ejercicios)


## Materiales de apoyo

 <html>
 <small>
 <table>
  <tr><th>Tema</th><th>Lección</th><th>Materiales de estudio</th></tr>
  <tr>
      <td rowspan="2">1</td>
      <td>C y make para sistemas distribuidos</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-candmake/ssdd_c.md">Aspectos de C para sistemas distribuidos</a></li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materials/topic-candmake/ssdd_make.md">Introducción a make</a></li>
      </td>
  </tr>
  <tr>
      <td>Concurrencia en sistemas distribuidos</td>
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
        </li>
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

  * [Ejemplo de transformación de aplicación monolítica a aplicación distribuida: almacenamiento clave-valor](/materials/pc-keyvalue/#readme)
    * [Ejemplo de almacenamiento clave-valor centralizado monolítico](/materials/pc-keyvalue/kv-centralizado-monolitico#readme)
    * [Ejemplo de almacenamiento clave-valor distribuido basado en colas POSIX](/materials/pc-keyvalue/kv-distribuido-mqueue#readme)
    * [Ejemplo de almacenamiento clave-valor distribuido basado en sockets](/materials/pc-keyvalue/kv-distribuido-sockets#readme)
    * [Ejemplo de almacenamiento clave-valor distribuido basado en RPC](/materials/pc-keyvalue/kv-distribuido-rpc#readme)

  * [Ejemplo de transformación de aplicación monolítica a aplicación distribuida: calculadora](/materials/pc-calculator/#readme)
    * [Ejemplo de calculadora centralizado monolítico](/materials/pc-calculator/cal-centralizado-monolitico#readme)
    * [Ejemplo de calculadora distribuido basado en colas POSIX](/materials/pc-calculator/cal-distribuido-mqueue#readme)
    * [Ejemplo de calculadora distribuido basado en sockets](/materials/pc-calculator/cal-distribuido-sockets#readme)
    * [Ejemplo de calculadora distribuido basado en RPC](/materials/pc-calculator/cal-distribuido-rpc#readme)
    * [Ejemplo de calculadora distribuido basado en GSOAP](/materials/pc-calculator/cal-distribuido-gsoap-standalone#readme)

