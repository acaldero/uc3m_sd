
## Sistemas Distribuidos: materiales complementarios
+ **Felix García Carballeira y Alejandro Calderón Mateos** @ arcos.inf.uc3m.es
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contents

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
      <td>Repaso de C y make</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-cymake/ssdd_c.md">Aspectos de C para sistemas distribuidos</a></li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-cymake/ssdd_make.md">Introducción a make para sistemas distribuidos</a></li>
      </td>
  </tr>
  <tr>
      <td>Repaso de concurrencia</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-concurrencia/ssdd_threads_posix.md">Concurrencia en sistemas distribuidos (POSIX)</a></li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-concurrencia/ssdd_threads_c.md">Concurrencia en sistemas distribuidos (C11)</a></li>
      </td>
  </tr>
  <tr>
      <td rowspan="1">3</td>
      <td>Paso de mensajes</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-pasomensajes/ssdd_pq.md">Colas de mensajes POSIX</a></li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-pasomensajes/ssdd_mpi.md">Introducción a MPI</a>
             <a href="https://colab.research.google.com/github/acaldero/uc3m_sd/blob/main/materiales/tema-pasomensajes/ssdd_mpi.ipynb">(notebook)</a>  </li>
      </td>
  </tr>
  <tr>
      <td rowspan="1">4</td>
      <td>Sockets</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-sockets/ssdd_sockets.md">Sockets</a></li>
      </td>
  </tr>
  <tr>
      <td rowspan="1">5</td>
      <td>Servicios distribuidos</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-sd/ssdd_sd.md">Principales servicios distribuidos</a></li>
      </td>
  </tr>
  <tr>
      <td rowspan="1">6</td>
      <td>RPC</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-rpc/ssdd_rpc.md">RPC</a></li>
      </td>
  </tr>
  <tr><td>7</td>
      <td>Sistema de ficheros distribuidos</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-sfd/ssdd_sfd.md">Introducción a los sistemas de ficheros distribuidos</a></li>
      </td>
  </tr>
  <tr><td>8</td>
      <td>Servicios Web</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-ws/ssdd_web-services.md">Introducción a servicios web</a></li>
      </td>
  </tr>
  <tr><td>9</td>
      <td>Tolerancia a fallos</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-tf/t9_tolerancia-a-fallos.pdf">t9_tolerancia-a-fallos.pdf</a> :notebook_with_decorative_cover:</li>
      </td>
  </tr>
 </table>
 </small>
</html>


## Casos prácticos

  * [Ejemplo de transformación de aplicación monolítica a aplicación distribuida: almacenamiento clave-valor](/materiales/cp-clavevalor/#readme)
    * [Ejemplo de almacenamiento clave-valor centralizado monolítico](/materiales/cp-clavevalor/kv-centralizado-monolitico#readme)
    * [Ejemplo de almacenamiento clave-valor distribuido basado en colas POSIX](/materiales/cp-clavevalor/kv-distribuido-mqueue#readme)
    * [Ejemplo de almacenamiento clave-valor distribuido basado en sockets](/materiales/cp-clavevalor/kv-distribuido-sockets#readme)
    * [Ejemplo de almacenamiento clave-valor distribuido basado en RPC](/materiales/cp-clavevalor/kv-distribuido-rpc#readme)

  * [Ejemplo de transformación de aplicación monolítica a aplicación distribuida: calculadora](/materiales/cp-calculadora/#readme)
    * [Ejemplo de calculadora centralizado monolítico](/materiales/cp-calculadora/cal-centralizado-monolitico#readme)
    * [Ejemplo de calculadora distribuido basado en colas POSIX](/materiales/cp-calculadora/cal-distribuido-mqueue#readme)
    * [Ejemplo de calculadora distribuido basado en sockets](/materiales/cp-calculadora/cal-distribuido-sockets#readme)
    * [Ejemplo de calculadora distribuido basado en RPC](/materiales/cp-calculadora/cal-distribuido-rpc#readme)
    * [Ejemplo de calculadora distribuido basado en GSOAP](/materiales/cp-calculadora/cal-distribuido-gsoap-standalone#readme)


## Ejercicios

  * Paso de mensajes
    * [Ejercicio de paso de mensajes (colas POSIX)](https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-pasomensajes/ejercicio_pasomensajes_vector.md)
    * [Ejercicio de paso de mensajes (colas POSIX) en PDF](https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-pasomensajes/e1-pasomensajes-v2a.pdf)
    * [Ejercicio de paso de mensajes (nombrado)](https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-pasomensajes/ejercicio_pasomensajes_upgraded.md)
  * Sockets
    * [Ejercicio de calculadora distribuida basada en Sockets](https://github.com/acaldero/uc3m_sd/blob/main/materiales/tema-sockets/ejercicio_sockets_calculadora.md)


