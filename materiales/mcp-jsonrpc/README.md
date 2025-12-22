
## Sistemas Distribuidos: materiales complementarios
+ **Felix García Carballeira y Alejandro Calderón Mateos** @ arcos.inf.uc3m.es
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Servicio distribuido JSON-RPC sobre HTTP: servidor MCP de calculadora simple

### Preparación

* Hay que ir al directorio de trabaja (si es necesario):
  ```bash
  cd mcp-jsonrpc
  ```

* Hay que instalar los prerrequisitos:
  * El programa ```uvicorn```:
    ```bash
    sudo apt install uvicorn -y
    ```
    O también:
    ```bash
    curl -LsSf https://astral.sh/uv/install.sh | sh
    ```
  * Las bibliotecas ```fastapi``` y ```fastmcp```:
    ```bash
    touch pyproject.toml
    uv add --dev -r requirements.txt
    ```


### Ejecutar servidor y cliente

<html>
<table>
<tr><th>Paso</th><th>Cliente</th><th>Servidor</th></tr>
<tr>
<td>1</td>
<td></td>
<td>

```bash
$ python3 ./mcp_server_calc.py
```

</td>
</tr>

<tr>
<td>2</td>
<td>

```bash
$ python3 ./mcp_client_calc.py

...
Herramientas disponibles:
  - add
  - sub
  - mul
  - div

Resultado de add(1,2):
CallToolResult(content=[TextContent(type='text',
                                    text='3',
                                    annotations=None,
                                    meta=None)],
                          structured_content={'result': 3},
                          meta=None,
                          data=3,
                          is_error=False)
...
```

</td>
<td>
</td>
</tr>

<tr>
<td>3</td>
<td></td>
<td>

```bash
^C

INFO:     Shutting down
INFO:     Waiting for application shutdown.
INFO:     Application shutdown complete.
INFO:     Finished server process [171901]
```

</td>
</tr>
</table>
</html>


### Ejecutar servidor y cliente en VCode

* Hay que ejecutar primero el servidor:
  ```bash
  $ python3 ./mcp_server_calc.py
  ```
* La primera vez, hay que configurar el servicio MCP en VCode:
  * Hay que abrir la paleta de comandos con Ctrl-Alt-P y seleccionar añadir servidor:
    ![Paso 1](images/cfg1.png) 
  * A continuación, hay que seleccionar servidor HTTP:
    ![Paso 2](images/cfg2.png) 
  * A continuación, hay que indicar la dirección URL:
    ![Paso 3](images/cfg3.png) 
  * A continuación, hay que indicar el nombre:
    ![Paso 4](images/cfg4.png) 
  * Y finalmente, hacer global (o local al espacio de trabajo):
    ![Paso 5](images/cfg5.png) 
* Para usar el servicio en VCode:
  * Hay que hacer click en herramientas en el chat:
    ![Paso 1](images/clt1.png) 
  * Hay que activar el servidor my-mcp-server (y las utilidades):
    ![Paso 2](images/clt2.png) 
  * Hay que indicar en el chat que se quiere "add 1 and 2 with my-mcp-server":
    ![Paso 3](images/clt3.png) 
  * Hay que dar permisos ("Allow") para usar el servicio:
    ![Paso 4](images/clt4.png) 
  * Se tiene el resultado:
    ![Paso 5](images/clt5.png) 


## Información adicional

* [Ejemplo de Servidor MCP server](https://gofastmcp.com/tutorials/create-mcp-server)
* [How to Build an MCP Server in Python: A Complete Guide](https://scrapfly.io/blog/posts/how-to-build-an-mcp-server-in-python-a-complete-guide)

