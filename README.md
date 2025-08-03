
## Sistemas Distribuidos: materiales complementarios
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Materiales de apoyo

 <html>
 <small>
 <table>
  <tr><th>Tema</th><th>Lección</th><th>:notebook: Materiales de estudio</th><th>:pencil2: Ejercicios</th></tr>
  <tr>
      <td rowspan="2">1</td>
      <td>Repaso de C y make</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ssdd_c.md">Aspectos de C para sistemas distribuidos</a></li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ssdd_make.md">Introducción a make para sistemas distribuidos</a></li>
      </td>
      <td>&nbsp;</td>
  </tr>
  <tr>
      <td>Repaso de concurrencia</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ssdd_threads_posix.md">Concurrencia en sistemas distribuidos (POSIX)</a></li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ssdd_threads_c.md">Concurrencia en sistemas distribuidos (C11)</a></li>
      </td>
      <td>&nbsp;</td>
  </tr>
  <tr>
      <td rowspan="1">3</td>
      <td>Paso de mensajes</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ssdd_pq.md">Colas de mensajes POSIX</a></li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ssdd_mpi.md">MPI</a></li>
      </td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ejercicio_pasomensajes_vector.md">Ejercicio de paso de mensajes (colas POSIX)</a>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ejercicio_pasomensajes_upgraded.md">Ejercicio de paso de mensajes (nombrado)</a></li>
      </td>
  </tr>
  <tr>
      <td rowspan="1">4</td>
      <td>Sockets</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ssdd_sockets.md">Sockets</a></li>
      </td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ejercicio_sockets_calculadora.md">Ejercicio de calculadora distribuida basada en Sockets</a>
      </td>
  </tr>
  <tr>
      <td rowspan="1">6</td>
      <td>RPC</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ssdd_rpc.md">RPC</a></li>
      </td>
      <td>&nbsp;</td>
  </tr>
  <tr><td>7</td>
      <td>Sistema de ficheros distribuidos</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ssdd_sfd.md">Introducción a los sistemas de ficheros distribuidos</a></li>
      </td>
      <td>&nbsp;</td>
  </tr>
  <tr><td>8</td>
      <td>Servicios Web</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/ssdd_web-services.md">Introducción a servicios web</a></li>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/t8_web-services.pdf">t8_web-services.pdf</a> :notebook_with_decorative_cover:</li>
      </td>
      <td>&nbsp;</td>
  </tr>
  <tr><td>9</td>
      <td>Tolerancia a fallos</td>
      <td>
        <li> <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/t9_tolerancia-a-fallos.pdf">t9_tolerancia-a-fallos.pdf</a> :notebook_with_decorative_cover:</li>
      </td>
      <td>&nbsp;</td>
  </tr>
 </table>
 </small>
</html>


## Casos prácticos

  * [Ejemplo de transformación de aplicación monolítica a aplicación distribuida: almacenamiento clave-valor](/casos-practicos/kv_centralizado_a_distribuido.md)
    * [Ejemplo de almacenamiento clave-valor centralizado monolítico](/casos-practicos/kv-centralizado-monolitico#readme)
    * [Ejemplo de almacenamiento clave-valor distribuido basado en colas POSIX](/casos-practicos/kv-distribuido-mqueue#readme)
    * [Ejemplo de almacenamiento clave-valor distribuido basado en sockets](/casos-practicos/kv-distribuido-sockets#readme)
    * [Ejemplo de almacenamiento clave-valor distribuido basado en RPC](/casos-practicos/kv-distribuido-rpc#readme)

  * [Ejemplo de transformación de aplicación monolítica a aplicación distribuida: calculadora](/casos-practicos/cal_centralizado_a_distribuido.md)
    * [Ejemplo de calculadora centralizado monolítico](/casos-practicos/cal-centralizado-monolitico#readme)
    * [Ejemplo de calculadora distribuido basado en colas POSIX](/casos-practicos/cal-distribuido-mqueue#readme)
    * [Ejemplo de calculadora distribuido basado en sockets](/casos-practicos/cal-distribuido-sockets#readme)
    * [Ejemplo de calculadora distribuido basado en RPC](/casos-practicos/cal-distribuido-rpc#readme)
    * [Ejemplo de calculadora distribuido basado en GSOAP](/casos-practicos/cal-distribuido-gsoap-standalone#readme)

