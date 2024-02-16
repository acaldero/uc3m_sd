
# Sistemas Distribuidos: Servicios Web
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ Licencia [GPLv3.0](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

  * [Motivación en el uso de servicios Web](#por-que-usar-un-servicio-web)
  * [Ejemplo simple de servicio web basado en eventos enviados por servidor (SSE)](#ejemplo-simple-de-servicio-web-basado-en-eventos-enviados-por-servidor--sse-)
  * [Usar un servicio distribuido basado en gSOAP/XML (cliente solo, en C)](#usar-un-servicio-distribuido-basado-en-gSOAP-XML--cliente-solo,-en-C-)
  * [Creación de un servicio distribuido basado en gSOAP/XML (cliente y servidor, en C)](#creación-de-un-servicio-distribuido-basado-en-gSOAP/XML--cliente-y-servidor--en-C-)



## Por qué usar un Servicio Web

En la WWW se usa una arquitectura cliente (ejemplo: navegador web) y servidor (ejemplo: servidor web Apache), con un protocolo HTTP basado en texto. \
Inicialmente los servidores Web se han usado para enviar el contenido estático guardado en ficheros. \
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

La siguiente generación, el contenido se generaba parcialmente o totalmente de forma dinámica (en el servidor con tecnologías como servlets, JSP, PHP, etc. así en el cliente con tecnologías como Applets, JavaScript, etc.)
Era posible usar el método POST para enviar información útil (argumentos) para la generación dinámica. \
Hay un paso adicional interesante, ¿y si detrás de un fichero dinámico no hay un fichero sino un programa al que enviar los argumentos y que nos responda con el resultado? \
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

Y de esta forma podemos tener un posible servicio web... afortunadamente hay distintos estándares que nos permiten construir servicios web en los que se evite en lo posible incompatibilidades. \
De esta forma se puede usar un servicio web, facilitando el despliegue de una nueva generación de aplicaciones distribuidas.


## Ejemplo simple de servicio web basado en eventos enviados por servidor (SSE)

Usaremos el ejemplo disponible en [ws-rest-sse-bash](ws-rest-sse-bash/README.md)

Los pasos para la ejecución típica son:
 * Ejecutar el servidor:
   ```
   ./demo-server.sh
   ```
 * Ejecutar el cliente:
   ```
   firefox demo-client.html
   ```

Como puede observarse, demo-server.sh manda la salida del script "demo.sh" a un net-cat que está escuchando en el puerto 8080. \
El script "demo.sh" se encarga de mandar las cabeceras de respuesta de un servidor web, junto a cada segundo el instante de tiempo dentro de un JSON. \
La página web "demo-client.html" se encarga de mostrar la información que va llegando en tiempo real.

Se usa en este ejemplo el [Server Side Events](https://developer.mozilla.org/es/docs/Web/API/Server-sent_events/Using_server-sent_events). \
Los eventos enviados por el servidor (SSE) es una tecnología que permite enviar notificaciones/mensajes/eventos desde el servidor a los clientes a través de una conexión HTTP (tecnología push).



## Usar un servicio distribuido basado en gSOAP/XML (cliente solo, en C)

Usaremos el ejemplo disponible en [ws-gsoap-xml-wsdl](ws-gsoap-xml-wsdl/README.md)

Dicho ejemplo se basa en el servicio de calculadora que está en: http://www.genivia.com/calc.wsdl

Los pasos a seguir habitualmente son los siguientes:
* Primero hay que generar el archivo de cabecera calc.h con la interfaz del servicio a partir de la descripción del servicio dada en WSDL:
  ```
  wsdl2h -c -o calc.h http://www.genivia.com/calc.wsdl
  ```
* A continuación hay que generar los resguardos (stubs) a partir de la interfaz de calc.h:
  ```
  soapcpp2 -CL calc.h
  ```
* Hay que crear la aplicación "app-d.c" que use el servicio:
  ```
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
  ```
  gcc -o app-d \
      -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ \
      -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/ \
      app-d.c soapC.c soapClient.c -lgsoap
  ```
* La ejecución del ejemplo sería:
  ```
  $ ./app-d
  result = 5.79
  ```


## Creación de un servicio distribuido basado en gSOAP/XML (cliente y servidor, en C)

Usaremos el ejemplo disponible en [ws-gsoap-xml-standalone](ws-gsoap-xml-standalone/README.md)

Dicho ejemplo es el ejemplo de calculadora disponible en: https://www.genivia.com/dev.html#client-c

Los pasos a seguir habitualmente son los siguientes:
* Primero hay que generar el archivo de cabecera calc.h con la interfaz del servicio a partir de la descripción del servicio dada en WSDL:
  ```
  wsdl2h -c -o calc.h http://www.genivia.com/calc.wsdl
  ```
* A continuación hay que generar los resguardos (stubs) a partir de la interfaz de calc.h:
  ```
  soapcpp2 -CL calc.h
  ```
* Hay que crear la aplicación "app-d.c" que use el servicio:
  ```
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
  ```
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
  ```
  gcc -o app-d \
      -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/ \
      app-d.c soapC.c soapClient.c -lgsoap
  gcc -o lib-server \
      -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/ \
      lib-server.c soapC.c soapClient.c -lgsoap
  ```
* Es posible ejecutar por un lado el servidor (lib-server) y por otro el cliente (app-d) de la siguiente manera:
```
$ ./lib-server &
$ ./app-d
```


Gracias al mandato soapcpp2 se han generado gran parte del trabajo, como se puede ver en la siguiente figura:
<img src="https://www.genivia.com/images/flowchart.png" style="max-height:512" />


**Información adicional**:
  * [t8_web-services.pdf](https://github.com/acaldero/uc3m_sd/blob/main/transparencias/t8_web-services.pdf)
  * <a href="https://github.com/acaldero/uc3m_sd/blob/main/transparencias/t8_web-services.pdf">t8_web-services.pdf</a>

