
# Sistemas Distribuidos: Servicios Web
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ Licencia [GPLv3.0](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

  * [Motivación en el uso de servicios Web](#introducción)
  * [Estilos de servicios: SOAP vs RESTful](#estilos-de-servicios-soap-vs-rest)
  * Ejemplos REST y SOAP:
    * [Python - REST: Ejemplo simple de servicio web  (servidor y cliente)](#ejemplo-simple-de-servicio-web-rest-servidor-y-cliente-en-python)
    * [Python - SOAP: Ejemplo de servicio web  (cliente)](#ejemplo-simple-de-servicio-web-soap-cliente-en-python)
    * [Python - SOAP: Ejemplo simple de servicio web (cliente y servidor)](#ejemplo-simple-de-servicio-web-soap-cliente-y-servidor-en-python)
    * [C - SOAP: Usar un servicio distribuido basado en gSOAP/XML (cliente solo)](#usar-un-servicio-distribuido-basado-en-gsoapxml-cliente-solo-en-c)
    * [C - SOAP: Creación de un servicio distribuido basado en gSOAP/XML (cliente y servidor)](#creación-de-un-servicio-distribuido-basado-en-gsoapxml-cliente-y-servidor-en-c)
  * [Otras tecnologías además de REST y SOAP](#otras-tecnologías-además-de-rest-y-soap)
  * Ejemplos de otras tecnologías:
    * [Ejemplo simple de servicio web basado en eventos enviados por servidor (SSE)](#ejemplo-simple-de-servicio-web-basado-en-sse-en-bash)
    * [Creación de un servicio distribuido basado en Apache Thrift (cliente y servidor, en Python)](#creación-de-un-servicio-distribuido-basado-en-apache-thrift-cliente-y-servidor-en-python)
    * [Creación de un servicio distribuido basado en gRPC (cliente y servidor, en Python)](#creación-de-un-servicio-distribuido-basado-en-grpc-cliente-y-servidor-en-python)


## Introducción

Los servicios web están al nivel de un servicio de red y un nivel más del paradigma de procedimiento remoto:

   ![Paradigmas por niveles](/transparencias/ssdd_web-services/ssdd_web-services-drawio_4.svg)


Los servicios web (y los servicios de red) son una extensión al paradigma de invocación de procedimientos remotos en el que se añade un servicio de directorio que proporcionan la referencia a los servicios disponibles:

   ![Transparencia de localización](/transparencias/ssdd_web-services/ssdd_web-services-drawio_5.svg)

Este servicio de directorio permite *transparencia de localización*, lo que es un nivel de abstracción extra.

#### Transparencia de localización

Los pasos habituales para el uso del servicio de directorio (o registro) son:
1. El proceso solicitante contacta con el servicio de directorio y busca un servicio
2. El servicio de directorio devuelve la referencia al servicio solicitado
3. Usando la referencia, el proceso solicitante interactúa con el servicio

Las principales diferencias con RPC son:
   * En una RPC se busca el puerto de la máquina donde ejecuta el *"servicio de directorio"*
     *  En servicios Web se busca por el listado de las URL (protocolo, máquina y puerto) donde está el servicio
   * En una RPC se busca por un número identificador del servicio
     * En servicios Web se podría buscar por su nombre, características del servicio, etc.


#### Invocación remota usando la Web

En el directorio se puede dar de alta el servicio (paso 0) y dar de baja.
Dar de alta un servicio puede suponer incluir en el directorio lo siguiente:
* Identificación del servicio.
* Dirección y puerto de la máquina donde se ofrece.
* Una descripción del API que permite diseñar, implementar y probar un cliente (consumidor) que pida el servicio a un servidor (proveedor).

A partir de la descripción del API puede ser posible generar los resguardos (stubs) que facilitan el despliegue de forma parecida a como `rpcgen` automatiza la generación de parte del código en las RPC.
* La generación de código mediante una herramienta de este tipo permite garantizar que se ha validado dicho proceso de generación (en lugar de basarse en una generación estocástica de código que puede no funcionar como es el caso de herramientas puramente basadas en IA).


#### Qué ha facilitado los servicios Web

El disponer de un repositorio de servicios web ofrecidos permite que:
   * **Distintas aplicaciones de software** desarrolladas en lenguajes de programación diferentes, y ejecutadas sobre cualquier plataforma, pueden utilizar los servicios web para intercambiar datos.
   * Una única **aplicación distribuida** puede descomponerse en servicios modulares independientes débilmente acoplados que pueden interoperar entre sí.
     * **Arquitectura SOA**: Arquitectura en la que el software se expone como “servicio”, que es invocado utilizando un protocolo estándar de comunicación
     *  Es posible componer y combinar servicios web para generar nuevas aplicaciones distribuidas (por ejemplo: agencia de viajes que interactúa con hoteles, aviones, banco, etc.)


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


## Estilos de servicios: SOAP vs REST

Hay dos estilos principales:
 * Servicios web **SOAP** (*Simple Object Accces Protocol*)
 * **REST** (*RESTful Architecture Style*)

Inicialmente apareció la idea de Servicio Web y se estandarizó con el uso de **SOAP**, lo que ofrece muchas funcionalidades para *business to business*.
Con el paso del tiempo apareció otra necesidad complementaria: una versión simplificada que permita definir un API Web simple.
En su tesis doctoral en el año 2000, Roy Fielding introduce la propuesta de REST, que proporciona un nivel relativamente alto de flexibilidad, escalabilidad y eficiencia para los/as desarrolladores/as.
Las API REST se han popularizado, siendo el método común para conectar componentes y aplicaciones en una arquitectura de microservicios.

<html>
<table>
<tr><th></th><th>SOAP</th><th>REST</th></tr>
<tr>
<td>Orientación</td>
<td>A mensaje</td>
<td>A recurso</td>
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
<td><img src="/transparencias/ssdd_web-services/ssdd_web-services-drawio_soap.svg"></td>
<td><img src="/transparencias/ssdd_web-services/ssdd_web-services-drawio_rest.svg"></td>
</tr>
</table>
</html>

Los [seis principios de diseño (o restricciones arquitectónicas)](https://www.ibm.com/topics/rest-apis) REST son:
* Interfaz uniforme: Todas las solicitudes de API para el mismo recurso deben tener el mismo aspecto, independientemente de la procedencia de la solicitud.
* Desacoplamiento cliente-servidor: Las aplicaciones cliente y servidor deben ser completamente independientes entre sí, solo se interactúa con el API.
* Sin estado: Las API REST son apátridas, lo que significa que cada solicitud debe incluir toda la información necesaria para procesarla.
* Cacheabilidad: En la medida de lo posible, los recursos deben poder almacenarse en caché en el cliente o en el servidor.
* Arquitectura en capas: las llamadas y las respuestas pueden pasar por diferentes capas (no asumir que cliente y servidor se conectan directamente entre sí).
* Código bajo demanda (opcional): Las API REST suelen enviar recursos estáticos, pero en algunos casos las respuestas también pueden contener código ejecutable (como applets de Java). En estos casos, el código solo debe ejecutarse bajo demanda.


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
<img src="/transparencias/ssdd_web-services/ssdd_web-services-drawio_10_soap.svg" alt="Pila de protocolos habitual en servicios web basados en SOAP">
</td>
<td>
<img src="/transparencias/ssdd_web-services/ssdd_web-services-drawio_10_rest.svg" alt="Pila de protocolos habitual en servicios web basados en REST">
</td>
</tr>

</table>
</html>


##  Ejemplos de servicio usando REST y SOAP

A continuación se presentan 3 ejemplos simples en Python:
   * Servicio web REST (servidor y cliente)
   * Servicio web SOAP (cliente solo)
   * Servicio web SOAP (cliente y servidor)

Y posteriormente se presentan 2 ejemplos en C:
   * Uso de servicio basado en gSOAP/XML (cliente solo)
   * Creación de un servicio basado en gSOAP/XML (cliente y servidor)


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

   app.run(debug=False, host="0.0.0.0", port="5000")
   ```

 * Para *iniciar* la ejecución del servidor hay que usar lo siguiente:
   ```bash
   python3 app.py &
   ```

 * Para *parar* la ejecución del servidor (cuando ya no se necesite el servicio) se puede usar lo siguiente:
   ```bash
   kill $(pgrep -f app.py)
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
   127.0.0.1 - - [11/Mar/2025 12:42:00] "POST /precio HTTP/1.1" 201 -
   HTTP/1.0 201 CREATED
   Server: Werkzeug/2.3.2 Python/3.10.12
   Date: Tue, 11 Mar 2025 11:42:00 GMT
   Content-Type: text/html; charset=utf-8
   Content-Length: 5
   Connection: close

   123.5
   ```


<br>

A partir de este ejemplo inicial nos podemos hacer algunas preguntas, como por ejemplo:
* ¿Cómo vamos a documentar este servicio REST?
* ¿Se podría describir en un formato simplificado de WSDL para generar código y documentación de forma automática?
* ¿Cómo se podría validar o/y probar este servicio de forma automática?



<br>

### OpenAPI

Existe el estándar OpenAPI que permite describir un servicio REST:
* La documentación del estándar OpenAPI 3.1 está disponible en: https://spec.openapis.org/oas/v3.1.1
* Como ejemplos tenemos:
  * Ejemplo simple: https://learn.openapis.org/examples/v3.0/link-example.html
  * Tienda de mascotas: https://github.com/swagger-api/swagger-petstore/blob/master/src/main/resources/openapi.yaml

Basado en este estándar hay herramientas para ayudar en el diseño, desarrollo y pruebas de dicho servicio REST:
* Para diseñar el API se puede usar un editor en línea (*online*) como *Swagger Editor*: https://editor.swagger.io/
* Para la generación de código (*client libraries*, *server stubs*, documentación) en diferentes lenguajes se puede usar *Swagger Codegen*: https://github.com/swagger-api/swagger-codegen


### Ejemplo simple de servicio web REST con OpenAPI

El siguiente ejemplo implementa un pequeño servicio de almacen clave-valor:

0. Primero se precisa comprobar que esté instalado los paquetes python **fastapi, uvicorn y pydantic**.
    Se puede instalar mediante:
   ```bash
   pip3 install fastapi uvicorn[standard] pydantic
   ```
    O bien mediante:
   ```bash
   sudo python3 -m pip install fastapi uvicorn[standard] pydantic
   ```
   Suele tardar algún tiempo la instalación, hay que esperar.
   Puede usar ```pip3 install --user fastapi uvicorn``` para instalar solo para el usuario actual.
1. El siguiente paso sería crear el archivo servidor de dicho servicio web (ws-openapi.py en nuestro ejemplo):
   ```python
   from typing   import Optional
   from fastapi  import FastAPI
   from pydantic import BaseModel
   import uvicorn

   # Key-Value: a cada clave hay una clase Item asociada
   list_kv = {}

   # pydantic se usa para describir esa clase Item asociada a cada clave
   class Item(BaseModel):
       name: str
       description: Optional[str] = None
       weight: Optional[float] = None

   # fastAPI
   app = FastAPI()

   @app.put("/items/{key}")
   async def create_item(key: int, item: Item):
       list_kv[key] = item
       return { "key": key, **item.dict() }

   @app.get("/items/{key}")
   async def select_item(key: int):
       try:
          item = list_kv[key]
       except:
          item = { name:'', description:'', weight: 0.0 }
       return { "key": key, **item.dict() }

   if __name__ == "__main__":
       uvicorn.run(app, host="127.0.0.1", port=8000)
   ```
2. Para ejecutar el servidor:
   ```bash
   python3 ws-openapi.py &
   ```
    Y la salida se parecerá a:
   ```bash
   INFO:     Started server process [67103]
   INFO:     Waiting for application startup.
   INFO:     Application startup complete.
   INFO:     Uvicorn running on http://127.0.0.1:8000 (Press CTRL+C to quit)
   ```
3. Para ver la interfaz *swagger* con la documentación y cliente interactivo básico ha de usar un navegador web:
   ```bash
   firefox http://127.0.0.1:8000/docs
   ```
    Esta interfaz permite tanto ver la documentación generada de forma automática como poder interactuar con el servicio:
   ![Interfaz swagger para ws-openapi](/transparencias/ssdd_web-services/ws-openapi-ui.png)


El siguiente ejemplo implementa un pequeño cliente del servicio de almacen clave-valor anterior:

1. El primer paso es crear el archivo cliente de dicho servicio web (ws-openapi-clnt.py en nuestro ejemplo):
   ```python
   import requests

   r = requests.put(url="http://127.0.0.1:8000/items/10",
                    json   ={ "name": "string",   "description": "string",   "weight":0.0 },
                    headers={ 'Content-type': 'application/json', 'accept': 'application/json' })
   print(r.text)
   ```
2. Para ejecutar dicho cliente se usará:
   ```bash
   python3 ws-openapi-clnt.py
   ```
3. Y la salida podría ser similar a:
   ```bash
   INFO:     127.0.0.1:57732 - "PUT /items/10 HTTP/1.1" 200 OK
   {"key":10,"name":"string","description":"string","weight":0.0}
   ```


<br>

Aprovecho para agradecer a Pablo Velo Moreno la introducción al mundo de fastAPI y pydantic.
Tambien comentar que pueden verse más ejemplos de uso en los siguientes interesantes artículos:
* https://data-ai.theodo.com/en/technical-blog/fastapi-pydantic-powerful-duo
* https://medium.com/codenx/fastapi-pydantic-d809e046007f
* https://www.geeksforgeeks.org/fastapi-pydantic/
* https://realpython.com/fastapi-python-web-apis/



## Ejemplo simple de servicio web SOAP (cliente en Python)

A la hora de crear un servicio Web en Python con SOAP hay múltiples entornos:
  * https://wiki.python.org/moin/WebServices

Ejemplos más conocidos son:
* **Zeep**: para crear **clientes**
   * Modelo basado en SOAP para Python.
   * Hace uso de los diccionarios de Python para el manejo de XML.
* **Spyne**: para crear **servicios**
   * Modelo basado en SOAP para Python para creación de servicios.
   * Despliegue del servidor.
   * Generador de WDSL.

El siguiente ejemplo implementa un cliente de saludar (``Hello + <nombre>``) basado en Zeep:

0. Primero se precisa comprobar que esté instalado el paquete python **zeep**.
    Se puede instalar mediante:
   ```bash
   pip3 install zeep
   ```
   Suele tardar algún tiempo la instalación, hay que esperar.
   Puede usar ```pip3 install zeep --user``` para instalar solo para el usuario actual.

1. Hay que conocer la información del servicio Web usando ``python -mzeep <URL>``, siendo URL la asociada al WSDL:
   ```bash
   python3 -mzeep https://apps.learnwebservices.com/services/hello?WSDL
   ```

2. El siguiente paso habitual es crear el archivo cliente de dicho servicio web (ws-echo.py en nuestro ejemplo):
   ```python
   import zeep

   wsdl = 'https://apps.learnwebservices.com/services/hello?WSDL'
   client = zeep.Client(wsdl=wsdl)
   print(client.service.SayHello('Web Services'))
   ```

3. Para ejecutar:
   ```bash
   $ python3 ./ws-echo.py
   Hello Web Services!
   ```

Puede probarse otros servicios WSDL disponibles gratis (al menos en el momento de escribir este tutoría) de la siguiente lista:
* https://ngrashia.medium.com/compiled-list-of-free-and-working-wsdl-urls-a7a54be6b91
<br>

## Ejemplo simple de servicio web SOAP (cliente y servidor en Python)

A la hora de crear un servicio Web en Python con SOAP hay múltiples entornos:
  * https://wiki.python.org/moin/WebServices

Ejemplos más conocidos son:
* **Zeep**: para crear **clientes**
   * Modelo basado en SOAP para Python.
   * Hace uso de los diccionarios de Python para el manejo de XML.
* **Spyne**: para crear **servicios**
   * Modelo basado en SOAP para Python para creación de servicios.
   * Despliegue del servidor.
   * Generador de WDSL.

El siguiente ejemplo implementa un cliente de echo (repetir lo que se manda) basado en Spyne:

0. Primero se precisa comprobar que estén instalados los paquetes python **spyne** y **zeep**.
    Se pueden instalar mediante:
   ```bash
   pip3 install spyne zeep
   ```
   Suele tardar algún tiempo la instalación, hay que esperar.
   Puede usar ```pip3 install spyne zeep --user``` para instalar solo para el usuario actual.

1. El primer paso habitual es crear el archivo servidor de dicho servicio web (ws-calc-servidor.py en nuestro ejemplo):
   ```python
   import time, logging
   from wsgiref.simple_server import make_server
   from spyne import Application, ServiceBase, Integer, Unicode, rpc
   from spyne.protocol.soap import Soap11
   from spyne.server.wsgi import WsgiApplication

   class Calculadora(ServiceBase):
       @rpc(Integer, Integer, _returns=Integer)
       def add(ctx, a, b):
           return a+b
       @rpc(Integer, Integer, _returns=Integer)
       def sub(ctx, a, b):
           return a-b

   application = Application(services=[Calculadora],
                             tns='http://tests.python-zeep.org/',
                             in_protocol=Soap11(validator='lxml'),
                             out_protocol=Soap11())
   application = WsgiApplication(application)

   if __name__ == '__main__':
       logging.basicConfig(level=logging.DEBUG)
       logging.getLogger('spyne.protocol.xml').setLevel(logging.DEBUG)
       logging.info("listening to http://127.0.0.1:8000; wsdl is at: http://localhost:8000/?wsdl ")
       server = make_server('127.0.0.1', 8000, application)
       server.serve_forever()
   ```

2. El segundo paso es ejecutar el servidor:
   ```bash
   python3 ./ws-calc-servidor.py
   ```

3. El siguiente paso es conocer la información del servicio Web usando ``python -mzeep <URL>``:
   ```bash
   $ python3 -mzeep http://localhost:8000/?wsdl

   ...
   Service: Calculadora
     Port: Application (Soap11Binding: {http://tests.python-zeep.org/}Application)
         Operations:
            add(a: xsd:integer, b: xsd:integer) -> addResult: xsd:integer
            sub(a: xsd:integer, b: xsd:integer) -> subResult: xsd:integer
   ```

5. El siguiente paso habitual es crear el archivo cliente de dicho servicio web (ws-calc-cliente.py en nuestro ejemplo):
   ```python
   import zeep

   wsdl = "http://localhost:8000/?wsdl"
   client = zeep.Client(wsdl=wsdl)

   r = client.service.add(5, 2)
   print(' 5+2 = ' + str(r))

   r = client.service.sub(5, 3)
   print(' 5-3 = ' + str(r))
   ```

6. Para ejecutar el cliente del servicio:
   ```bash
   $ python3 ./ws-calc-cliente.py
    5+2 = 7
    5-3 = 2
   ```


## Usar un servicio distribuido basado en gSOAP/XML (cliente solo, en C)

Usaremos un ejemplo basado en el servicio de calculadora disponible en: http://www.genivia.com/calc.wsdl

Los pasos principales a seguir son los siguientes:

0. Primero se precisa comprobar que estén instalados los paquetes **gsoap** y **libgsoap-dev**.
    Se pueden instalar mediante:
    ```bash
    sudo apt install gsoap gsoap-doc libgsoap-dev
    ```
1. Primero hay que obtener el archivo calc.h con la interfaz del servicio a partir de la descripción del servicio dada en WSDL:
    ```bash
    wsdl2h -c -o calc.h http://www.dneonline.com/calculator.asmx?WSDL
    ```
2. A continuación hay que generar los resguardos (*stubs*) a partir de la interfaz de calc.h:
    ```bash
    soapcpp2 -CcL calc.h
    ```
3. Hay que crear la aplicación **`app-d.c`** que use el servicio:
    ```c
    #include "CalculatorSoap.nsmap"
    #include "soapH.h"

    int main ( int argc, char *argv[] )
    {
      struct _tempuri__Add in ;
      struct _tempuri__AddResponse out ;
      struct soap *soap ;

      soap = soap_new();
      if (NULL == soap) { return -1; }

      in.intA = 1 ;
      in.intB = 1 ;
      int ret = soap_call___tempuri__Add(soap, NULL, NULL, &in, &out) ;
      if (SOAP_OK != ret) { soap_print_fault(soap, stderr); exit(-1); }

      printf("Sum = %d\n", out.AddResult);

      soap_destroy(soap); soap_end(soap); soap_free(soap);
      return 0;
    }
    ```
4. Hay que compilar todo, por ejemplo usando:
    ```bash
    gcc -o app-d   app-d.c soapC.c soapClient.c -lgsoap
    ```
   En caso de tener, por ejemplo, instalado gsoap 2.8.127 con *brew*, se podría usar:
    ```bash
    gcc -o app-d \
        -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ \
        -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/ \
        app-d.c soapC.c soapClient.c -lgsoap
    ```
5. La ejecución del ejemplo sería:
   ```bash
   $ ./app-d
   Sum = 2
   ```


## Creación de un servicio distribuido basado en gSOAP/XML (cliente y servidor, en C)

El siguiente ejemplo está basado en el ejemplo de calculadora disponible en: https://www.genivia.com/dev.html#client-c

En el proceso de creación de un servicio distribuido basado en gSOAP/XML que permita sumar y restar, <br>los pasos a seguir son:

1. Hay que generar el archivo de cabecera **`calc.h`** con la interfaz del servicio:
   ```c
    //gsoap ns service name: calc
    //gsoap ns schema namespace: urn:calc
    int ns__add(double a, double b, double *result);
    int ns__sub(double a, double b, double *result);
   ```
2. Con *soapcpp2* (versión 2.8.91 o compatible) hay que generar los resguardos (*stubs*) a partir de la interfaz de calc.h:
   ```bash
   soapcpp2 -cL calc.h
   ```
   Gracias al mandato soapcpp2 se han generado gran parte del trabajo, como se puede ver en la siguiente figura: <br/>
   <img src="https://www.genivia.com/images/flowchart.png" style="max-height:512" /><br/><br/>
3. Hay que crear la parte que implementa el servicio, por ejemplo en el archivo **`lib-server.c`**:
   ```c
   #include "soapH.h"
   #include "calc.nsmap"

   int main(int argc, char **argv)
   {
      struct soap soap;

      if (argc < 2) {
          printf("Uso: %s <puerto>\n", argv[0]) ;
          exit(-1);
      }
      soap_init(&soap);
      soap_bind(&soap, NULL, atoi(argv[1]), 100);
      while(1)
      {
        soap_accept(&soap);
        soap_serve(&soap);
        soap_end(&soap);
      }

      return 0;
   }

   int ns__add ( struct soap *soap, double a, double b, double *result )
   {
       *result = a + b;
       return SOAP_OK;
   }

   int ns__sub ( struct soap *soap, double a, double b, double *result )
   {
       *result = a - b;
       return SOAP_OK;
   }
   ```
4. Hay que crear la aplicación **`app-d.c`** que use el servicio:
   ```c
   #include "soapH.h"
   #include "calc.nsmap"

   int d_add ( double a, double b, double *r )
   {
       struct soap soap;

       // env SERVER_IP=localhost:12345 ./app-d
       char *host = getenv("SERVER_IP") ;
       if (NULL == host) {
           printf("ERROR: missing 'export SERVER_IP=<ip>:<port>'\n") ;
           return -1 ;
       }

       soap_init(&soap);
       soap_call_ns__add(&soap, host, "", a, b, r);
       if (soap.error) {
           soap_print_fault(&soap, stderr);
           return -1 ;
       }
       soap_done(&soap) ;

       return 0 ;
   }

   int main ( int argc, char **argv )
   {
       double result = 0 ;
       int ret ;

       ret = d_add(1.0, 2.0, &result) ;
       if (ret < 0)
            printf("result is not valid\n") ;
       else printf("result = %g\n", result) ;

       return 0;
   }
   ```
5. Hay que compilar todo, por ejemplo usando:
   ```bash
    gcc -g -o app-d       app-d.c soapC.c soapClient.c -lgsoap
    gcc -g -o lib-server  lib-server.c soapC.c soapServer.c -lgsoap
   ```
   En caso de tener, por ejemplo, instalado gsoap 2.8.127 con *brew*, se podría usar:
   ```bash
    gcc -g -o app-d \
        -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/ \
        app-d.c soapC.c soapClient.c -lgsoap
    gcc -g -o lib-server \
        -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/ \
        lib-server.c soapC.c soapServer.c -lgsoap
   ```
6. Es posible ejecutar por un lado el servidor (lib-server) y por otro el cliente (app-d) de la siguiente manera:
   ```bash
    $ ./lib-server 12345 &
    $ env SERVER_IP=localhost:12345 ./app-d
    result = 3
    ```


## Otras tecnologías además de REST y SOAP

REST y SOAP han ido evolucionando, al igual que han apareciendo nuevas tecnologías.
La siguiente imagen resume la evolución en el tiempo y la comparación de las principales tecnologías:

 ![Evolución de tecnologías Web](/transparencias/ssdd_web-services/ssdd_web-services-api-timeline.svg) <br/>

La siguiente tabla resume los principales aspectos de algunas de las principales tecnologías:

|                 | SOAP        | REST           | JSON-RPC   | gRPC | GraphQL | Thrift |
|-----------------|-------------|----------------|------------|------|---------|--------|
| Presentado      | fin 1990s   | 2000           | mitad 2000 | 2015 | 2015    | 2007   |
| Formato         | XML         | JSON, XML, ... | JSON       | Protobuf, JSON, ... | JSON | JSON o binario |
| Ventajas        | conocido    | Formato de intercambio flexible y simple | Simple de implementar | Permite cualquier tipo función | Estructuración flexible de datos | Adaptable a muchos casos de uso |
| Casos de uso    | pagos, "legacy", ...   | API pública |        | HPC microservicios | API móvil |  |
| Organización    | mensajes empaquetados | cumplir 6 restricciones |        | llamada a procedimiento | sistema tipado |  |

Entre estas tecnologías hay que destacar dos:
* **gRPC**, que es un proyecto creado por Google para su uso interno.
* **Apache Thrift**, que es un proyecto originalmente creado por Facebook también para su uso interno.
Ambas tecnologías permiten crear software en distintos lenguajes, y usar protocolos eficientes.


### Motor de la evolución: servicios con más necesidades 

A día de hoy, el estándar más usado como base de servicios Web es HTTP lo que hace que solo usando HTTP todo se tenga que basar en el modelo de interacción *petición/respuesta* y protocolo basado en mensajes de *texto*.
En algunos casos puede que no sea el modelo ideal para construir algunos servicios lo que fuerza a adaptar dichos servicios al modelo y protocolo de una forma que complica tanto el diseño y como la eficiencia de ejecución.

Algunos ejemplos de modelos de interacción diferentes al *petición/respuesta* se tienen:
* **Fire-and-forget**. Este modelo es una optimización del modelo *petición/respuesta* que es útil cuando la respuesta no es necesaria. Por ejemplo si un cliente quiere usar un servicio no crítico de registro de eventos (*non-critical event logging*). Ahorra tanto recursos de uso en red (al no enviar la respuesta) y también recursos de procesamiento (al necesitar el procesamiento de la respuesta). También es común su uso en [sistemas de mensajería](https://dasunpubudumal.medium.com/distributed-systems-messaging-eee8e70c4a77)
* **Request/stream**. Este modelo es una variante de *petición/respuesta* en el que la respuesta no es un único mensaje sino una colección de mensajes. Por ejemplo si un cliente pide la lista de productos de un catálogo.
* **Event**. Este modelo es una variante de modelo *petición/respuesta* en el que no hay una petición y si una secuencia de  respuestas, son mensajes de respuesta asociados a eventos asíncronos. Por ejemplo si un cliente quiere estar suscrito a los comentarios que se vayan haciendo de una transmisión deportiva.


## Ejemplos de otras tecnologías

Como ejemplos de otras tecnologías se tienen los siguientes:
* Python - SSE: Ejemplo simple de servicio web basado en SSE 
* BASH - SSE: Ejemplo simple de servicio web basado en SSE 
* Creación de un servicio distribuido basado en Apache Thrift (cliente y servidor, en Python)
* Creación de un servicio distribuido basado en gRPC (cliente y servidor, en Python)


## Ejemplo simple de servicio web basado en SSE (en Python)

El siguiente es un ejemplo de [Server Side Events](https://developer.mozilla.org/es/docs/Web/API/Server-sent_events/Using_server-sent_events) basado en Python. \
Los eventos enviados por el servidor (SSE) es una tecnología que permite enviar notificaciones/mensajes/eventos desde el servidor a los clientes a través de una conexión HTTP (tecnología push).

Este ejemplo está compuesto de 2 ficheros:
 * El archivo **`demo-server.py`**: servidor que cada segundo genera un mensaje con el instante de tiempo actual
   ```python
   import time, datetime
   from flask import Flask, Response
   from flask_cors import CORS

   app = Flask(__name__)
   CORS(app)

   @app.route("/")
   def publish_data():
       def stream():
           while True:
               ts  = datetime.datetime.now()
               msg = f"data: " + str(ts) + "\n\n"
               yield msg
               time.sleep(1)

       return Response(stream(), mimetype="text/event-stream")

   if __name__ == "__main__":
        app.run(debug=True, port=5000)
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
       var s = new EventSource('http://localhost:5000');
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
   ```bash
   python3 ./demo-server.py
   ```
 * Ejecutar el cliente:
   ```bash
   firefox demo-client.html
   ```


En la página Web `demo-client.html` cada segundo llega un evento por parte de `demo-server.py`.
En lugar de mostrarse en la página Web el instante de tiempo cada segundo, se puede mandar otro tipo de información (por ejemplo, valores de los sensores), con distinto tipo de periodicidad y distinto tipo de visualización o procesamiento.


## Ejemplo simple de servicio web basado en SSE (en bash)

El siguiente es un ejemplo de [Server Side Events](https://developer.mozilla.org/es/docs/Web/API/Server-sent_events/Using_server-sent_events) o eventos enviados por servidor. \
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
   chmod a+x *.sh
   ./demo-server.sh &
   ```
 * Ejecutar el cliente:
   ```
   firefox demo-client.html
   ```


En la página Web `demo-client.html` cada segundo llega un evento por parte del script `demo.sh` a través del mandato `nc`que simula un servidor web en el puerto 8080.
En lugar de mostrarse en la página Web el instante de tiempo cada segundo, se puede mandar otro tipo de información (por ejemplo, valores de los sensores), con distinto tipo de periodicidad y distinto tipo de visualización o procesamiento.



## Creación de un servicio distribuido basado en Apache Thrift (cliente y servidor, en Python)

El siguiente ejemplo está basado en el ejemplo disponible en: https://github.com/apache/thrift/tree/master/tutorial/py

En el proceso de creación de un servicio distribuido basado en Apache Thrift que permita sumar y restar, <br>los pasos a seguir son:

1. Hay que generar el archivo **`calc.thrift`** con la interfaz del servicio:
   ```c
   service calc
   {
      i32 add(1:i32 a, 2:i32 b) ;
      i32 sub(1:i32 a, 2:i32 b) ;
   }
   ```
2. Con *thrift* (versión 0.13.0 o compatible) hay que generar los resguardos (*stubs*) a partir de la interfaz de calc.thrift:
   ```bash
   thrift -r --gen py calc.thrift
   cd gen-py
   ```
3. Hay que crear la parte que implementa el servicio, por ejemplo en el archivo **`server.py`**:
   ```python
   from calc import calc
   from calc.ttypes import *

   from thrift.transport import TSocket
   from thrift.transport import TTransport
   from thrift.protocol  import TBinaryProtocol
   from thrift.server    import TServer

   class calcHandler:
       def __init__(self):
           self.log = {}
       def add(self, n1, n2):
           print('add(%d,%d)' % (n1, n2))
           return n1 + n2
       def sub(self, n1, n2):
           print('sub(%d,%d)' % (n1, n2))
           return n1 - n2

   if __name__ == '__main__':
       handler   = calcHandler()
       processor = calc.Processor(handler)
       transport = TSocket.TServerSocket(host='127.0.0.1', port=9090)
       tfactory  = TTransport.TBufferedTransportFactory()
       pfactory  = TBinaryProtocol.TBinaryProtocolFactory()

       server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)
       # You could do one of these for a multithreaded server
       # server = TServer.TThreadedServer  (processor, transport, tfactory, pfactory)
       # server = TServer.TThreadPoolServer(processor, transport, tfactory, pfactory)

       print('Starting the server on localhost:9090...')
       server.serve()
       print('done.')
   ```
4. Hay que crear la parte cliente que use el servicio, por ejemplo en el archivo **`client.py`**:
   ```python
   from calc import calc
   from calc.ttypes import *

   from thrift import Thrift
   from thrift.transport import TSocket
   from thrift.transport import TTransport
   from thrift.protocol import TBinaryProtocol

   def main():
       transport = TSocket.TSocket('localhost', 9090)
       transport = TTransport.TBufferedTransport(transport)
       protocol  = TBinaryProtocol.TBinaryProtocol(transport)

       transport.open()
       client = calc.Client(protocol)
       res_ = client.add(1, 1)
       print('1+1=%d' % res_)
       res_ = client.sub(1, 1)
       print('1-1=%d' % res_)
       transport.close()

   if __name__ == '__main__':
       try:
           main()
       except Thrift.TException as tx:
           print('%s' % tx.message)
   ```
5. Es posible ejecutar el servidor y el cliente de la siguiente manera:
   ```bash
    $ python3 ./server.py &
    $ python3 ./client.py
    add(1,1)
    1+1=2
    sub(1,1)
    1-1=0
    ```


## Creación de un servicio distribuido basado en gRPC (cliente y servidor, en Python)

El siguiente ejemplo está basado en el ejemplo disponible en: https://medium.com/@coderviewer/simple-usage-of-grpc-with-python-f714d9f69daa

En el proceso de creación de un servicio distribuido basado en gRPC que permita sumar y restar, <br>los pasos a seguir son:

1. Hay que generar el archivo **`calc.proto`** con la interfaz del servicio:
   ```c
   syntax = "proto3";
   package calculator;

   service Calculator {
     rpc Add (AddRequest) returns (AddResponse);
   }

   message AddRequest {
     int32 num1 = 1;
     int32 num2 = 2;
   }

   message AddResponse {
     int32 result = 1;
   }
   ```
2. Con *grpc_tools.protoc* (``pip3 install grpcio grpcio-tools``) hay que generar los resguardos (*stubs*) a partir de la interfaz de calc.proto:
   ```bash
   python3 -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. calc.proto
   ```
3. Hay que crear la parte que implementa el servicio, por ejemplo en el archivo **`server.py`**:
   ```python
   import grpc
   from concurrent import futures
   import calc_pb2
   import calc_pb2_grpc

   class CalculatorServicer(calc_pb2_grpc.CalculatorServicer):
        def Add(self, request, context):
            result = request.num1 + request.num2
            return calc_pb2.AddResponse(result=result)

   server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
   calc_pb2_grpc.add_CalculatorServicer_to_server(CalculatorServicer(), server)
   server.add_insecure_port('[::]:50051')
   server.start()
   server.wait_for_termination()
   ```
4. Hay que crear la parte cliente que use el servicio, por ejemplo en el archivo **`client.py`**:
   ```python
   import grpc
   import calc_pb2
   import calc_pb2_grpc

   with grpc.insecure_channel('localhost:50051') as channel:
       stub = calc_pb2_grpc.CalculatorStub(channel)
       response = stub.Add(calc_pb2.AddRequest(num1=1, num2=2))
   print(f"Result: {response.result}")
   ```
5. Es posible ejecutar el servidor y el cliente de la siguiente manera:
   ```bash
   $ python3 ./server.py &
   $ python3 ./client.py
   Result: 3
    ```





<br/>

## Información adicional
  * [Transparencias del tema 8: t8_web-services.pdf](https://github.com/acaldero/uc3m_sd/blob/main/transparencias/t8_web-services.pdf)
  * [Know your API protocols: SOAP vs. REST vs. JSON-RPC vs. gRPC vs. GraphQL vs. Thrift](https://www.mertech.com/blog/know-your-api-protocols)
  * [A brief look at the evolution of interface protocols leading to modern APIs](https://www.soa4u.co.uk/2019/02/a-brief-look-at-evolution-of-interface.html)
  * [Soap vs REST vs GrapQL vs gRPC](https://www.altexsoft.com/blog/soap-vs-rest-vs-graphql-vs-rpc/)
  * [A brief look at the evolution of interface protocols leading to modern APIs](https://www.soa4u.co.uk/2019/02/a-brief-look-at-evolution-of-interface.html)
  * [RPC Frameworks: gRPC vs Thrift vs RPyC for python](https://www.hardikp.com/2018/07/28/services/)

