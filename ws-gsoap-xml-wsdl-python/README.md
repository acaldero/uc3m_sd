
## Sistemas Distribuidos: materiales complementarios
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)
+ ARCOS.INF.UC3M.ES


## Aplicación que usa un servicio distribuido basado en gSOAP/XML

#### Preparación

* Se precisa tener instalado el paquete de python "zeep" para crear clientes:
  ```
  pip3 install zeep 
  ```
  Suele tardar algún tiempo la instalación, hay que esperar.

* A continuación hay que conocer la información del servicio Web usando "python -mzeep URL", siendo URL la asociada al WSDL:
  ```
  python3 -mzeep http://www.dneonline.com/calculator.asmx?WSDL
  ```

* El siguiente paso habitual es crear el archivo cliente de dicho servicio web (app-d.py en nuestro ejemplo):
  ```
  import zeep

  wsdl_url = "http://www.dneonline.com/calculator.asmx?WSDL"
  soap = zeep.Client(wsdl=wsdl_url) 

  result = soap.service.Add(5, 5)
  print("5 + 5 = ", result)

  result = soap.service.Multiply(5, 5)
  print("5 * 5 = ", result)
  ```


#### Ejecutar

<html>
<table>
<tr><th>Paso</th><th>Cliente</th><th>Servidor</th></tr>

<tr>
<td>1</td>
<td>

```
$ python3 ./app-d.py
5 + 5 =  10
5 * 5 =  25
```

</td>
<td>

```
```

</td>
</tr>

</table>
</html>


#### Arquitectura

```mermaid
sequenceDiagram
    app-d          ->> web-service: request lib.h API in a distributed way
    web-service    ->> app-d: return result of the distributed API call
```


