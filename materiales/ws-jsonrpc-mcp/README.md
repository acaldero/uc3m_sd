
## Sistemas Distribuidos: materiales complementarios
+ **Felix García Carballeira y Alejandro Calderón Mateos** @ arcos.inf.uc3m.es
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Servicio distribuido JSON-RPC sobre HTTP: servidor MCP de calculadora simple

### Preparación

* Hay que introducir:
  ```bash
  cd ws-jsonrpc-mcp
  ```

* Se usará uvicorn y las bibliotecas ```fastapi``` y ```fastmcp```:
  ```bash
  sudo apt install uvicorn -y
  pip3 install fastmcp fastapi --break-system-packages
  ```


### Ejecutar

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
CallToolResult(content=[TextContent(type='text', text='3',
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



## Información adicional

* [Ejemplo de Servidor MCP server](https://gofastmcp.com/tutorials/create-mcp-server)
* [How to Build an MCP Server in Python: A Complete Guide](https://scrapfly.io/blog/posts/how-to-build-an-mcp-server-in-python-a-complete-guide)

