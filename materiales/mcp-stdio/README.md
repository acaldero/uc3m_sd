
## Sistemas Distribuidos: materiales complementarios
+ **Felix García Carballeira y Alejandro Calderón Mateos** @ arcos.inf.uc3m.es
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Servicio JSON-RPC sobre STDIO: servidor MCP de calculadora simple

### Preparación

* Hay que introducir:
  ```bash
  cd mcp-stdio
  ```

* Se usarán las bibliotecas ```httpx```, ```uvicorn```, ```startlette```, ```fastapi``` y ```fastmcp```:
  ```bash
  curl -LsSf https://astral.sh/uv/install.sh | sh
  uv add --dev -r requirements.txt
  ```


### Ejecutar servidor y conectar a Visual Studio Code

En la sección "Add an MCP server to a workspace `mcp.json` file" de la [sección correspondiente del manual](https://code.visualstudio.com/docs/copilot/customization/mcp-servers) se indica:

1. Ejecutar el servidor:
   ```bash
   $ python3 ./calc.py
   ```
2. Crear el archivo [.vscode/mcp.json](mcp.json) dentro de nuestro espacio de trabajo.
3. Seleccionar el botón de añadir servidor en el editor para agregar una plantilla para un nuevo servidor.
4. Para poder usar el ejemplo de MCP basado en STDIO del fichero [calc.py](calc.py) puede utilizar lo siguiente (cambiando python3 a python si lo precisa):
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
5. Alternativamente ejecute el mandato "MCP: Add Server" desde "Command Palette", seleccione el tipo de servidor MCP para añadir e indique la información del servidor. A continuación, seleccione el espacio de trabajo para añadir el servidor al archivo ```.vscode/mcp.json``` correspondiente.


## Información adicional

* [Use MCP servers in VS Code](https://code.visualstudio.com/docs/copilot/customization/mcp-servers)
* [Ejemplo de Servidor MCP server](https://gofastmcp.com/tutorials/create-mcp-server)
* [How to Build an MCP Server in Python: A Complete Guide](https://scrapfly.io/blog/posts/how-to-build-an-mcp-server-in-python-a-complete-guide)

