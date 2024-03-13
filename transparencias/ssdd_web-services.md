
# Sistemas Distribuidos: Servicios Web
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ Licencia [GPLv3.0](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

  * [Motivación en el uso de servicios Web](#introducción)
  * [Estilos de servicios web: SOAP vs REST](#estilos-de-servicios-web-soap-vs-rest)
  * [Ejemplo simple de servicio web REST (servidor y cliente en Python)](#ejemplo-simple-de-servicio-web-rest-servidor-y-cliente-en-python)
  * [Ejemplo simple de servicio web basado en eventos enviados por servidor (SSE)](#ejemplo-simple-de-servicio-web-basado-en-eventos-enviados-por-servidor-sse)
  * [Usar un servicio distribuido basado en gSOAP/XML (cliente solo, en C)](#usar-un-servicio-distribuido-basado-en-gsoapxml-cliente-solo-en-c)
  * [Creación de un servicio distribuido basado en gSOAP/XML (cliente y servidor, en C)](#creación-de-un-servicio-distribuido-basado-en-gsoapxml-cliente-y-servidor-en-c)


## Introducción

Los servicios web están al nivel de un servicio de red y un nivel más del paradigma de procedimiento remoto:

   ![Paradigmas por niveles](./ssdd_web-services/ssdd_web-services_drawio_4.svg)<img src="./transparencias/ssdd_web-services/ssdd_web-services_drawio_4.svg">

#### Transparencia de localización
Los servicios web (y los servicios de red) son una extensión al paradigma de invocación de procedimientos remotos en el que se añade un servicio de directorio que proporcionan la referencia a los servicios disponibles:

   ![Paradigmas por niveles](./ssdd_web-services/ssdd_web-services_drawio_5.svg)<img src="./transparencias/ssdd_web-services/ssdd_web-services_drawio_5.svg">

Este servicio de directorio permite *transparencia de localización*, lo que es un nivel de abstracción extra.
Los pasos habituales para el uso del servicio de directorio (o registro) son:
1. El proceso solicitante contacta con el servicio de directorio
2. El servicio de directorio devuelve la referencia al servicio solicitado
3. Usando la referencia, el proceso solicitante interactúa con el servicio

El disponer de un repositorio de servicios web ofrecidos permite:
   * **Distintas aplicaciones de software** desarrolladas en lenguajes de programación diferentes, y ejecutadas sobre cualquier plataforma, pueden utilizar los servicios web para intercambiar datos.
   * Una única **aplicación distribuida** puede descomponerse en servicios modulares independientes débilmente acoplados que pueden interoperar entre sí mediante el paradigma cliente/servidor.
     * **Arquitectura SOA**: Arquitectura en la que el software se expone como “servicio”, que es invocado utilizando un protocolo estándar de comunicación
     *  Es posible componer y combinar servicios web para generar nuevas aplicaciones distribuidas (por ejemplo: agencia de viajes que interactúa con hoteles, aviones, banco, etc.)


#### Invocación remota usando la Web

En el directorio se puede dar de alta el servicio (paso 0) y dar de baja. 
Dar de alta un servicio puede suponer incluir en el directorio lo siguiente:
* Identificación del servicio.
* Dirección y puerto de la máquina donde se ofrece.
* Una descripción del API que permite diseñar, implementar y probar un cliente (consumidor) que pida el servicio a un servidor (proveedor).

A partir de la descripción del API puede ser posible generar los resguardos (stubs) que facilitan el despliegue de forma parecida a como `rpcgen` automatiza la generación de parte del código en las RPC. 
* La generación de código mediante una herramienta de este tipo permite garantizar que se ha validado dicho proceso de generación (en lugar de basarse en una generación de código basada en probabilidad que puede no funcionar como es el caso de herramientas puramente basadas en IA).


## Primera generación de la WWW: contenido estático

En la WWW se usa una arquitectura cliente (ejemplo: navegador web) y servidor (ejemplo: servidor web Apache), con un protocolo HTTP basado en texto. \
Por ejemplo, es posible pedir una página web a mano:
* Ejecutamos:
  ```
  $ telnet www.lab.inf.uc3m.es 80
  ```
  Y la salida es:
  ```
  Trying 163.117.61.51...
  Connected to waf.uc3m.es.
  Escape character is '^]'.
  ```
* Escribimos:
  ```
  GET / HTTP/1.0
  accept: */*
  ```
  Y la salida es:
  ```html
  HTTP/1.1 301 Moved Permanently
  Date: Fri, 28 Apr 2023 11:18:58 GMT
  Server: Apache
  Location: https:///
  Content-Length: 217
  Connection: close
  Content-Type: text/html; charset=iso-8859-1

  <!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
  <html><head>
  <title>301 Moved Permanently</title>
  </head><body>
  <h1>Moved Permanently</h1>
  <p>The document has moved <a href="https:///">here</a>.</p>
  </body></html>
  Connection closed by foreign host.
  ```

La salida tiene dos partes:
* Una cabecera con los metadatos de la respuesta.
* El contenido de la página pedida (index.html) en formato texto HTML.

Inicialmente los servidores Web se han usado para enviar el contenido estático guardado en ficheros. \
Esta primera generación permitía servir información escrita previamente en ficheros en formato HTML.


## Segunda generación de la WWW: contenido dinámico

La siguiente generación, el contenido se generaba parcialmente o totalmente de forma dinámica:
 * En el servidor con tecnologías como servlets, JSP, PHP, etc.
 * En el cliente con tecnologías como Applets, JavaScript, etc.

Hay un paso adicional interesante, ¿y si detrás de un fichero dinámico no hay un fichero sino un programa al que enviar los parámetros y que nos responda con el resultado?
El método POST se usaba para enviar información útil para la generación dinámica: los "parámetros" con los que trabajar.

Por tanto tenemos el potencial de:
* Al escribir:
  ```
  GET /calculadora,sumar,2,3 HTTP/1.0
  accept: */*
  ```
* Tener la salida siguiente en lugar del texto HTML:
  ```html
  HTTP/1.1 200 OK
  Date: Fri, 28 Apr 2023 11:18:58 GMT
  Server: Apache
  Location: https:///
  Content-Length: 1
  Connection: close
  Content-Type: text/html; charset=iso-8859-1

  5
  ```

Inicialmente este "dinamismo" se usó para permitir a las personas poder indicar términos de búsqueda y tener una página de resultados asociada a esos términos construida de forma dinámica.

En la segunda generación se caracterizaba inicialmente por que:
  * Había distintas tecnologías no siempre compatibles.
  * Estaba muy orientada a interacción con personas.
  * Por seguridad los cortafuegos solo solía dejar pasar el tráfico hacia el puerto 80.


## Por qué usar un Servicio Web

No obstante, si se usa este mecanismo de generación dinámica para comunicar aplicaciones entre sí, tenemos la base para construir un posible servicio Web.
En la tercera generación:
 * Se empezó a usar el mecanismo de generación dinámica de contenido para b2b (*business to business*).
 * Aparecieron distintos estándares que nos permiten construir servicios web en los que se evite en lo posible incompatibilidades.
 * Se empezó a definir un servicio web en base a generación dinámica de contenido, facilitando el despliegue de una nueva generación de aplicaciones distribuidas.

Un **servicio web** (*Web Service*) es un conjunto de protocolos y estándares que sirven para intercambiar datos entre aplicaciones en redes de ordenadores como Internet:
   * La **interoperabilidad** se consigue mediante la adopción de **estándares abiertos**.
     * Las organizaciones OASIS y W3C son los comités responsables de la arquitectura y reglamentación de los servicios Web.


## Estilos de servicios web: SOAP vs REST

Hay dos estilos principales:
 * Servicios web **SOAP** (*Simple Object Accces Protocol*)
 * **REST** (*RESTful Architecture Style*)

<html>
<table>
<tr><th></th><th>SOAP</th><th>REST</th></tr>
<tr>
<td>Qué ofrece</td>
<td>Un protocolo de mensajes</td>
<td>Un estilo de arquitectura software</td>
</tr>
<tr>
<td>Una URL representa...</td>
<td>Acceso a un API</td>
<td>Un recurso</td>
</tr>
<tr>
<td>Métodos HTTP</td>
<td>Habitualmente solo precisa POST (y el algún caso simple puede usarse GET)</td>
<td>POST y/o PUT/GET/UPDATE/DELETE se corresponden a CRUD (Create/Read/Update/Delete)</td>
</tr>
<tr>
<td>Representación de datos</td>
<td>XML</td>
<td>JSON (pero también HTML, texto plano, XML)</td>
</tr>
<tr>
<td>Ventajas</td>
<td>
<li> Seguridad</li>
<li> Flexibilidad</li>
</td>
<td>
<li> Precisa menos ancho de banda</li>
<li> Tecnología sin estado</li>
<li> Almacenamiento en caché</li>
<li> Escalabilidad</li>
</td>
</tr>
<tr>
<td>Registro</td>
<td><img src="/transparencias/ssdd_web-services/ssdd_web-services_drawio_soap.svg"></td>
<td><img src="/transparencias/ssdd_web-services/ssdd_web-services_drawio_rest.svg"></td>
</tr>
</table>
</html>



### Ejemplo de comunicación con SOAP y REST

Para la siguiente función:
  ```c
  Float precio ;
  Precio = ObtenerPrecio(mesa);
  ```

La siguiente tabla muestra un ejemplo de cómo podría ser las peticiones y respuestas:

<html>
<table>
<tr><th></th><th>SOAP</th><th>REST</th></tr>

<tr>
<td>
Petición
</td>
<td>
<pre>
POST StockQuote HTTP/1.1
...
&lt;SOAP-ENV:Envelope
  xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"
  SOAP-ENV:encodingStyle ="http://schemas.xmlsoap.org/soap/
&lt;SOAP-ENV:Body&gt;
  &lt;m:ObtenerPrecio
     xmlns:m="http://example.com/stockquote.xsd"&gt;
     &lt;item&gt;mesa&lt;/item&gt;
  &lt;/m:ObtenerPrecio&gt;
&lt;/SOAP-ENV:Body&gt;
&lt;/SOAP-ENV:Envelope&gt;
</pre>
</td>
<td>
<pre>
POST /precio HTTP/1.1
Content-Type: application/json
...
{"item":"mesa"}
</pre>
</td>
</tr>

<tr>
<td>
Respuesta
</td>
<td>
<pre>
HTTP/1.1 200 OK
...
&lt;SOAP-ENV:Envelope
  xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"
  SOAP-ENV:encodingStyle ="http://schemas.xmlsoap.org/soap/
&lt;SOAP-ENV:Body&gt;
   &lt;m:ObtenerPrecioResponse
     xmlns:m="http://example.com/stockquote.xsd"&gt;
     &lt;Precio&gt;123.5&lt;/Precio&gt;
   &lt;/m:ObtenerPrecioResponse&gt;
&lt;/SOAP-ENV:Body&gt;
&lt;/SOAP-ENV:Envelope&gt;
</pre>
</td>
<td>
<pre>
HTTP/1.0 201 CREATED
...
123.5
</pre>
</td>
</tr>

<tr>
<td>
Principales tecnologías (protocolos, etc.)
</td>
<td>
<ul>
<li> HTTP: transporte utilizado</li>
<li> XML: describe la información, los mensajes</li>
<li> SOAP: empaqueta la información y la transmite entre el cliente y el proveedor del servicio</li>
<li> WSDL: descripción del servicio</li>
<li> UDDI: lista de servicios disponibles </li>
<ul>
</td>
<td>
<ul>
<li> HTTP: transporte utilizado </li>
<li> JSON: describe la información como estructura de datos en JavaScript</li>
<ul>
</td>
</tr>

<tr>
<td>
Relación entre tecnologías
</td>
<td>
<img src="/transparencias/ssdd_web-services/ssdd_web-services_drawio_29.svg" alt="Pila de protocolos habitual en servicios web">
</td>
<td>
&nbsp;
</td>
</tr>

</table>
</html>



## Ejemplo simple de servicio web REST (servidor y cliente en Python)

El siguiente ejemplo implementa un servidor de un servicio web en Python que permite consultar el precio de una mesa de un restaurante:

 * El script **`app.py`** se encarga de implementar un servicio web en Python usando los paquetes *Flask* y *request*:
   ```python
   from flask import Flask, request

   app = Flask(__name__)
   precios = { "mesa": "123.5", "reserva": "12.5" }

   @app.route('/precio', methods=["POST"])
   def add_precio():
       try:
          req  = request.get_json()
          item = req['item']
          return precios[item], 201
       except Exception as e:
          return {"error": str(e)}, 415
   ```

 * Para *iniciar* la ejecución del servidor hay que usar lo siguiente:
   ```bash
   FLASK_APP=app.py  FLASK_DEBUG=true  flask run &
   ```

 * Para *parar* la ejecución del servidor (cuando ya no se necesite el servicio) se puede usar lo siguiente:
   ```bash
   kill $(pgrep -f flask)
   ```


El siguiente ejemplo implementa un cliente del servicio web anterior usando Python:

 * El script **`clnt.py`**  usa *requests*:
   ```python
   import requests

   r = requests.post(url="http://127.0.0.1:5000/precio",
                     json={ "item": "mesa" },
                     headers={ 'Content-type': 'application/json' })
   print(r.text)
   ```

 * Para ejecutar el cliente se puede usar:
   ```bash
   python3 clnt.py
   ```

 * La salida es:
   ```bash
   123.5
   ```

Es incluso posible usar el mandato `curl` como cliente del servicio web anterior:

 * Para ejecutar un cliente se puede usar:
   ```bash
   curl -i http://127.0.0.1:5000/precio \
        -X POST \
        -H 'Content-Type: application/json' \
        -d '{"item":"mesa"}'
   ```

 * Y la salida sería:
   ```bash
   127.0.0.1 - - [12/Mar/2024 02:42:00] "POST /precio HTTP/1.1" 201 -
   HTTP/1.0 201 CREATED
   Content-Type: text/html; charset=utf-8
   Content-Length: 5
   Server: Werkzeug/2.0.3 Python/3.8.10
   Date: Tue, 12 Mar 2024 01:42:00 GMT

   123.5
   ```


## Ejemplo simple de servicio web basado en eventos enviados por servidor (SSE)

El siguiente es un ejemplo de [Server Side Events](https://developer.mozilla.org/es/docs/Web/API/Server-sent_events/Using_server-sent_events). \
Los eventos enviados por el servidor (SSE) es una tecnología que permite enviar notificaciones/mensajes/eventos desde el servidor a los clientes a través de una conexión HTTP (tecnología push).

Este ejemplo está disponible en [ws-rest-sse-bash](/ws-rest-sse-bash/README.md) y está compuesto de 3 ficheros:
 * El script **`demo-server.sh`**: manda la salida del script **`demo.sh`** al mandato **nc** (*net cat*) que está escuchando en el puerto 8080.
   ```bash
   #!/bin/bash
   set -x
   ./demo.sh | nc -l -p 8080
   ```
 * El script **`demo.sh`**: se encarga de mandar las cabeceras de respuesta de un servidor web, y luego cada segundo manda el instante de tiempo dentro de un JSON.
   ```bash
   #!/bin/bash
   # (1) cabeceras
   echo "HTTP/1.1 200 OK"
   echo "Access-Control-Allow-Origin: *"
   echo "Content-Type: text/event-stream"
   echo "Cache-Control: no-cache"
   echo ""
   # (2) cada segundo manda "data: {'timestamp': <instante>}"
   while [ 1 ]; do
     T=$(date +%H:%M:%S)
     echo "data: {'timestamp': $T}"
     echo ""
     echo ""
     sleep 1
   done
   ```
 * La página web **`demo-client.html`**: se encarga de mostrar la información que va llegando en tiempo real.
   ```html
   <!DOCTYPE html>
   <html>
     <head><meta charset="utf-8" /></head>
     <body>
     <div id="msg1"></div><br>
     <div id="msg2" style="overflow-y: scroll;height: 300px; width: 360px;"></div><br>
     <script>
       var s = new EventSource('http://localhost:8080');
           s.onmessage = function(e) {
               document.getElementById("msg1").innerHTML = e.data ;
               var old_msg2 = document.getElementById("msg2").innerHTML ;
               document.getElementById("msg2").innerHTML = e.data + '<br>' + old_msg2 ;
           };
     </script>
     </body>
   </html>
   ```


Los pasos para la ejecución típica son:
 * Ejecutar el servidor:
   ```
   ./demo-server.sh
   ```
 * Ejecutar el cliente:
   ```
   firefox demo-client.html
   ```


En la página Web `demo-client.html` cada segundo llega un evento por parte del script `demo.sh` a través del mandato `nc`que simula un servidor web en el puerto 8080.
En lugar de mostrarse en la página Web el instante de tiempo cada segundo, se puede mandar otro tipo de información (por ejemplo, valores de los sensores), con distinto tipo de periodicidad y distinto tipo de visualización o procesamiento.



## Usar un servicio distribuido basado en gSOAP/XML (cliente solo, en C)

Usaremos el ejemplo disponible en [ws-gsoap-xml-wsdl](ws-gsoap-xml-wsdl/README.md)

Dicho ejemplo se basa en el servicio de calculadora que está en: http://www.genivia.com/calc.wsdl

Los pasos a seguir habitualmente son los siguientes:
* Primero hay que generar el archivo de cabecera calc.h con la interfaz del servicio a partir de la descripción del servicio dada en WSDL:
  ```bash
  wsdl2h -c -o calc.h http://www.genivia.com/calc.wsdl
  ```
* A continuación hay que generar los resguardos (stubs) a partir de la interfaz de calc.h:
  ```bash
  soapcpp2 -CL calc.h
  ```
* Hay que crear la aplicación **`app-d.c`** que use el servicio:
  ```c
  #include "calc.nsmap"
  #include "soapH.h"

  int main ( int argc, char *argv[] )
  {
    double sum;

    struct soap *soap = soap_new();
    if (NULL == soap) { return -1; }

    int ret = soap_call_ns2__add(soap, NULL, NULL, 1.23, 4.56, &sum) ;
    if (SOAP_OK != ret) { soap_print_fault(soap, stderr); exit(-1); }

    printf("Sum = %g\n", sum);

    soap_destroy(soap); soap_end(soap); soap_free(soap);
    return 0;
  }
  ```
* Hay que compilar todo, por ejemplo usando:
  ```bash
  gcc -o app-d \
      -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ \
      -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/ \
      app-d.c soapC.c soapClient.c -lgsoap
  ```
* La ejecución del ejemplo sería:
  ```bash
  $ ./app-d
  Sum = 5.79
  ```


## Creación de un servicio distribuido basado en gSOAP/XML (cliente y servidor, en C)

Usaremos el ejemplo disponible en [ws-gsoap-xml-standalone](ws-gsoap-xml-standalone/README.md)

Dicho ejemplo es el ejemplo de calculadora disponible en: https://www.genivia.com/dev.html#client-c

Los pasos a seguir habitualmente son los siguientes:
* NUEVO: primero hay que generar el archivo de cabecera **`calc.h`** con la interfaz del servicio:
  ```c
   //gsoap ns service name: calc
   //gsoap ns schema namespace: urn:calc
   int ns__add(double a,double b,double *result);
   int ns__sub(double a,double b,double *result);
  ```
* A continuación hay que generar los resguardos (stubs) a partir de la interfaz de calc.h:
  ```bash
  soapcpp2 -cL calc.h
  ```
   Gracias al mandato soapcpp2 se han generado gran parte del trabajo, como se puede ver en la siguiente figura: <br/>
   <img src="https://www.genivia.com/images/flowchart.png" style="max-height:512" /><br/><br/>
* Hay que crear la aplicación **`app-d.c`** que use el servicio:
  ```c
  #include "soapH.h"
  #include "calc.nsmap"

  int main(int argc, char **argv)
  {
     const char *server = "localhost:12345";
     struct soap soap;
     double result = 0.0;

     if (argc < 3) {
         printf("Usage: %s <a|s> <operand 1> <operand 2>\n", argv[0]);
         exit(-1);
     }

     soap_init(&soap);
     double a = strtod(argv[2], NULL);
     double b = strtod(argv[3], NULL);
     char   o = argv[1][0];

     if ('a' == o)
         soap_call_ns__add(&soap, server, "", a, b, &result);
     else if ('s' == o)
         soap_call_ns__sub(&soap, server, "", a, b, &result);
     else printf("error en operación: %c\n", o) ;

     if (soap.error)
          soap_print_fault(&soap, stderr);
     else printf("result = %g\n", result);

     return 0;
  }
  ```
* NUEVO: hay que crear la aplicación servidora **`lib-server.c`** que implementa el servicio:
  ```c
  #include "soapH.h"
  #include "calc.nsmap"

  int main(int argc, char **argv)
  {
      struct soap soap;

      soap_init(&soap);
      soap_bind(&soap,NULL,atoi(argv[1]), 100);
      while(1)
      {
        soap_accept(&soap);
        soap_serve(&soap);
        soap_end(&soap);
      }

      return 0;
  }

  int ns2__add (struct soap *soap, double a, double b, double *result)
  {
      *result = a + b;
      return SOAP_OK;
  }

  int ns2__sub (struct soap *soap, double a, double b, double *result)
  {
       *result = a - b;
       return SOAP_OK;
  }
  ```
* NUEVO: Hay que compilar todo, por ejemplo usando:
  ```bash
   gcc -g -o app-d \
       -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/ \
       app-d.c soapC.c soapClient.c -lgsoap
   gcc -g -o lib-server \
       -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/ \
       lib-server.c soapC.c soapServer.c -lgsoap
  ```
* Es posible ejecutar por un lado el servidor (lib-server) y por otro el cliente (app-d) de la siguiente manera:
  ```bash
  $ ./lib-server 12345 &
  $ ./app-d a 1 2
  result = 3
  ```


**Información adicional**:
  * [t8_web-services.pdf](https://github.com/acaldero/uc3m_sd/blob/main/transparencias/t8_web-services.pdf)


