
## Materiales usados en ARCOS.INF.UC3M.ES con Licencia CC BY-NC-SA 4.0
  * Felix García Carballeira y Alejandro Calderón Mateos

## Servicio distribuido REST basado en OpenAPI

#### Preparación

Hay que introducir:
```
cd ws-rest-openapi
```


#### Ejecutar

<html>
<table>
<tr><th>Paso</th><th>Cliente</th><th>Servidor</th></tr>
<tr>
<td>1</td>
<td></td>
<td>

```
$ python3 ws-openapi.py
```

</td>
</tr>

<tr>
<td>2</td>
<td>

```
$ firefox http://127.0.0.1:8000/docs &
$ python3 ws-openapi-clnt.py
```

</td>
<td>

```
{"key":10,"item":{"name":"name","weight":0.0}}
...
```

</td>
</tr>

<tr>
<td>3</td>
<td></td>
<td>

```
^Caccept: Interrupted system call
```

</td>
</tr>
</table>
</html>



## Información adicional

 * Documentación del estándar OpenAPI:
   * https://spec.openapis.org/oas/v3.1.1
 * Editor en línea (*online*) *Swagger Editor*:
   * https://editor.swagger.io/
 * Generación de código y documentación con *Swagger Codegen*:
   * https://github.com/swagger-api/swagger-codegen
 * Ejemplos de uso de OpenAPI con Python fastAPI y pydantic:
   * https://data-ai.theodo.com/en/technical-blog/fastapi-pydantic-powerful-duo
   * https://medium.com/codenx/fastapi-pydantic-d809e046007f
   * https://www.geeksforgeeks.org/fastapi-pydantic/
   * https://realpython.com/fastapi-python-web-apis/


