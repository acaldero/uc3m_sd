
# Sistemas Distribuidos: Servicios Web
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ Licencia [GPLv3.0](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

  * [Motivación en el uso de servicios Web](#primera-generacion-de-la-www-contenido-estatico)
  * [Estilos de servicios web: SOAP vs REST](#estilos-de-servicios-web-soap-vs-rest)
  * [Ejemplo simple de servicio web (servidor, en Python)](#ejemplo-simple-de-servicio-web--servidor--en-python-)
  * [Ejemplo simple de servicio web basado en eventos enviados por servidor (SSE)](#ejemplo-simple-de-servicio-web-basado-en-eventos-enviados-por-servidor--sse-)
  * [Usar un servicio distribuido basado en gSOAP/XML (cliente solo, en C)](#usar-un-servicio-distribuido-basado-en-gSOAP-XML--cliente-solo,-en-C-)
  * [Creación de un servicio distribuido basado en gSOAP/XML (cliente y servidor, en C)](#creación-de-un-servicio-distribuido-basado-en-gSOAP/XML--cliente-y-servidor--en-C-)


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
   * **Distintas aplicaciones de software** desarrolladas en lenguajes de programación diferentes, y ejecutadas sobre cualquier plataforma, pueden utilizar los servicios web para intercambiar datos.
   * Una única **aplicación distribuida** puede descomponerse en servicios modulares independientes débilmente acoplados que pueden interoperar entre sí mediante el paradigma cliente/servidor.
     * **Arquitectura SOA**: Arquitectura en la que el software se expone como “servicio” servicio”, que es invocado utilizando un protocolo estándar de comunicación
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
<td>Se puede usar caché</td>
<td>No</td>
<td>Si</td>
</tr>
<tr>
<td>A destacar</td>
<td>Seguridad y escalabilidad</td>
<td>Sencillez y ligero</td>
</tr>
</table>
</html>

   ![REST versus SOAP](./ssdd_web-services/ssdd_web-services_drawio_32.svg)<img src="./transparencias/ssdd_web-services/ssdd_web-services_drawio_32.svg">

### Ejemplo de comunicación con SOAP

Para la siguiente función:
  ```c
  Float precio ;
  Precio = ObtenerPrecio(mesa);
  ```
  En el caso de SOAP:
   * Una **petición** podría representarse como:
     ```xml
     POST StockQuote HTTP/1.1
     ...
     <SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"
      SOAP-ENV:encodingStyle ="http://schemas.xmlsoap.org/soap/
     <SOAP-ENV:Body>
       <m:ObtenerPrecio xmlns:m="http://example.com/stockquote.xsd">
          <item>mesa</item>
       </m:ObtenerPrecio>
     </SOAP-ENV:Body>
     </SOAP-ENV:Envelope>
     ```
   * Una **respuesta** podría representarse como:
     ```xml
     HTTP/1.1 200 OK
     ...
     <SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"
      SOAP-ENV:encodingStyle ="http://schemas.xmlsoap.org/soap/
     <SOAP-ENV:Body>
        <m:ObtenerPrecioResponse xmlns:m="http://example.com/stockquote.xsd">
          <Precio>123.5</Precio>
        </m:ObtenerPrecioResponse>
     </SOAP-ENV:Body>
     </SOAP-ENV:Envelope>
     ```

Principales tecnologías (protocolos, etc.) usadas con servicios web basados en SOAP:
* HTTP: transporte utilizado
* XML: describe la información, los mensajes
* SOAP: empaqueta la información y la transmite entre el cliente y el proveedor del servicio
* WSDL: descripción del servicio
* UDDI: lista de servicios disponibles
   ![Pila de protocolos habitual en servicios web](./ssdd_web-services/ssdd_web-services_drawio_29.svg)<img src="./transparencias/ssdd_web-services/ssdd_web-services_drawio_29.svg">

### Ejemplo de comunicación con REST

Para la siguiente función:
  ```c
  Float precio ;
  Precio = ObtenerPrecio(mesa);
  ```
  En el caso de REST:
   * Una **petición** podría representarse como:
     ```xml
     POST /precio HTTP/1.1
     Content-Type: application/json
     ...
     {"item":"mesa"}   
     ```
   * Una **respuesta** podría representarse como:
     ```xml
     HTTP/1.0 201 CREATED
     ...
     123.5   
     ```

Principales tecnologías (protocolos, etc.) usadas con servicios web basados en REST:
* HTTP: transporte utilizado
* JSON: describe la información como estructura de datos en JavaScript
   

## Ejemplo simple de servicio web (servidor, en Python)

El siguiente ejemplo de servicio web implementa el servidor de dicho servicio web en Python, pero para el cliente utiliza el mandato `curl` en línea de mandatos.

 * El script **`app.py`** se encarga de implementar un servicio web en Python usando los paquetes *Flask*, *request* y *jsonify*:
   ```python
   from flask import Flask, request, jsonify

   app = Flask(__name__)
   precios = { "mesa": "123.5", "reserva": "12" }

   @app.route('/precio', methods=["POST"])
   def add_precio():
       if not request.is_json:
          return {"error": "Request must be JSON"}, 415
       da = request.get_json()
       if None == da['item']:
          return {"error": "Request must content an item"}, 415
       item = da['item']
       return precios[item], 201
   ```

 * El script **`run.sh`** se encarga de (1) iniciar el servicio web, (2) hacer una petición REST y (3) parar el servicio web:
   ```bash
   #!/bin/bash
   set -x
   echo " (1) Inicializar servicio web..."
   FLASK_APP=app.py FLASK_DEBUG=true  flask run &
   sleep 2
   echo " (2) Obtener el precio de 'mesa'"
   curl -i http://127.0.0.1:5000/precio \
        -X POST \
        -H 'Content-Type: application/json' \
        -d '{"item":"mesa"}'
   sleep 1
   echo " (3) Finalizar servicio web..."
   kill $(pgrep -f flask)
   ```

 * La salida es:
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
* Hay que crear la aplicación "app-d.c" que use el servicio:
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
  result = 5.79
  ```


## Creación de un servicio distribuido basado en gSOAP/XML (cliente y servidor, en C)

Usaremos el ejemplo disponible en [ws-gsoap-xml-standalone](ws-gsoap-xml-standalone/README.md)

Dicho ejemplo es el ejemplo de calculadora disponible en: https://www.genivia.com/dev.html#client-c

Los pasos a seguir habitualmente son los siguientes:
* Primero hay que generar el archivo de cabecera calc.h con la interfaz del servicio a partir de la descripción del servicio dada en WSDL:
  ```bash
  wsdl2h -c -o calc.h http://www.genivia.com/calc.wsdl
  ```
* A continuación hay que generar los resguardos (stubs) a partir de la interfaz de calc.h:
  ```bash
  soapcpp2 -CL calc.h
  ```
* Hay que crear la aplicación "app-d.c" que use el servicio:
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
* NUEVO: hay que crear la aplicación servidora "lib-server.c" que implementa el servicio:
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

  int ns__add (struct soap *soap, double a, double b, double *result)
  {
      *result = a + b;
      return SOAP_OK;
  }

  int ns__sub (struct soap *soap, double a, double b, double *result)
  {
       *result = a - b;
       return SOAP_OK;
  }
  ```
* NUEVO: Hay que compilar todo, por ejemplo usando:
  ```bash
  gcc -o app-d \
      -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/ \
      app-d.c soapC.c soapClient.c -lgsoap
  gcc -o lib-server \
      -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/ \
      lib-server.c soapC.c soapClient.c -lgsoap
  ```
* Es posible ejecutar por un lado el servidor (lib-server) y por otro el cliente (app-d) de la siguiente manera:
  ```bash
  $ ./lib-server &
  $ ./app-d
  ```


Gracias al mandato soapcpp2 se han generado gran parte del trabajo, como se puede ver en la siguiente figura:
<img src="https://www.genivia.com/images/flowchart.png" style="max-height:512" />


**Información adicional**:
  * [t8_web-services.pdf](https://github.com/acaldero/uc3m_sd/blob/main/transparencias/t8_web-services.pdf)



