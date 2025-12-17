
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


### Ejecutar servidor y conectar a Visual Studio Code

En la sección "Add an MCP server to a workspace `mcp.json` file" de la [sección correspondiente del manual](https://code.visualstudio.com/docs/copilot/customization/mcp-servers) se indica:

1. Crear el archivo [.vscode/mcp.json](mcp.json) dentro de nuestro espacio de trabajo.
2. Seleccionar el botón de añadir servidor en el editor para agregar una plantilla para un nuevo servidor.
3. Para poder usar el ejemplo de MCP basado en STDIO del fichero [calc.py](calc.py) puede utilizar lo siguiente (cambiando python3 a python si lo precisa):
   ```json
   {
     "servers": {
       "calculator": {
         "type": "stdio",
         "command": "python3",
         "args": ["${workspaceFolder}/calc.py"]
       }
     }
   }
   ```
4. Alternativamente ejecute el mandato "MCP: Add Server" desde "Command Palette", seleccione el tipo de servidor MCP para añadir e indique la información del servidor. A continuación, seleccione el espacio de trabajo para añadir el servidor al archivo ```.vscode/mcp.json``` correspondiente.


## Información adicional

* [Use MCP servers in VS Code](https://code.visualstudio.com/docs/copilot/customization/mcp-servers)
* [Ejemplo de Servidor MCP server](https://gofastmcp.com/tutorials/create-mcp-server)
* [How to Build an MCP Server in Python: A Complete Guide](https://scrapfly.io/blog/posts/how-to-build-an-mcp-server-in-python-a-complete-guide)

