
## Sistemas Distribuidos: materiales complementarios
+ **Felix García Carballeira y Alejandro Calderón Mateos** @ arcos.inf.uc3m.es
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Servicio distribuido JSON-RPC sobre HTTP: servidor MCP de calculadora simple

 * [1. Ejecutar servidor mcp_server_calc.py y cliente mcp_client_calc.py](#-1-ejecutar-servidor-mcp_server_calcpy-y-cliente-mcp_client_calcpy)
 * [2. Ejecutar servidor mcp_server_calc.py y cliente gemini cli](#-2-ejecutar-servidor-mcp_server_calcpy-y-cliente-gemini-cli)
 * [3. Ejecutar servidor mcp_server_calc.py y cliente Visual Studio Code](#-3-ejecutar-servidor-mcp_server_calcpy-y-cliente-visual-studio-code)


## 🧪 1. Ejecutar servidor ```mcp_server_calc.py``` y cliente ```mcp_client_calc.py```

* Preparación:
  1. \[si no se tiene ya instalado\] hay que instalar los paquetes de Python de soporte MCP necesarios:
      ```bash
      python3 -m pip install -U fastapi fastmcp httpx starlette uvicorn --break-system-packages
      ```

* Los pasos generales para ejecutar son:
  * Ejecutar el servidor ```mcp_server_calc.py```
  * Ejecutar el cliente  ```mcp_client_calc.py``` 
  * Parar la ejecución del servidor<br>

  
* Un ejemplo de ejecución podría ser:
  <html>
  <table>
  <tr><th>Paso</th><th>Cliente</th><th>Servidor</th></tr>
  <tr>
  <td>1</td>
  <td></td>
  <td>

```bash
python3 ./mcp_server_calc.py
```

  </td>
  </tr>
  <tr>
  <td>2</td>
  <td>

```bash
python3 ./mcp_client_calc.py
```
```bash
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
```
```bash
INFO:   Shutting down
INFO:   Waiting for application shutdown.
INFO:   Application shutdown complete.
INFO:   Finished server process [171901]
```

  </td>
  </tr>
  </table>
  </html>


<br>


## 🧪 2. Ejecutar servidor ```mcp_server_calc.py``` y cliente ```gemini cli```

* Preparación de gemini-cli:
  1. \[si no se tiene ya instalado\] hay que instalar los paquetes de Python de soporte MCP necesarios:
      ```bash
      python3 -m pip install -U fastapi fastmcp httpx starlette uvicorn --break-system-packages
      ```
  2. \[si no se tiene ya instalado\] hay que instalar **node 24.12** y **npm**:
     ```bash
     curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.3/install.sh | bash
     export NVM_DIR="$HOME/.nvm"
     [ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"
     [ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"

     nvm install --lts
     npm install -g npm@latest
     nvm use --lts
     ```
  3. \[si no se tiene ya instalado\] hay que instalar ```gemini-cli```:
     ```bash
     npm install -g @google/gemini-cli
     ```
  4. Ejecutar ```gemini``` y hacer "Login with Google":
     ```bash
     gemini
     ```
  5. Salir de ```gemini-cli``` tras hacer "Login with Google" correctamente.
     ```bash
     /quit
     ```
     Es posible que tras pegar el token se pueda quedar bloqueado. En ese caso hay que usar otro terminal y hacer un kill al proceso.


* Los pasos generales para ejecutar son:
  * Ejecutar el servidor ```mcp_server_calc.py```
  * Configurar ```gemini cli``` para que pueda conectarse a ```mcp_server_calc.py```
  * Ejecutar ```gemini cli``` como cliente
  * Parar la ejecución del cliente y luego del servidor<br>
  

* Un ejemplo de ejecución podría ser:
   <html>
   <table>
   <tr><th>Paso</th><th>Cliente</th><th>Servidor</th></tr>
   <tr>
   <td>1</td>
   <td></td>
   <td>

```bash
python3 ./mcp_server_calc.py &
```

   </td>
   </tr>
   <tr>
   <td>2</td>
   <td>

```bash
gemini mcp add \
         --transport http mcp-calc \
         http://localhost:8000/mcp
```

  * Con ```mcp add``` crea el archivo ```.gemini/settings.json```:
    ```bash
    { 
        "mcpServers":
        {
           "mcp-calc":
           {
              "url":
              "http://localhost:8000/mcp"
           }
        }
    }
    ```

   </td>
   <td>
   </td>
   </tr>  
   <tr>
   <td>3</td>
   <td>

```bash
gemini --model gemini-2.5-flash-lite \
       --allowed-tools="add,sub,mul,div" \
       --prompt "suma 2 y 5 y da el resultado" 
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
killall python3

INFO:   Shutting down
INFO:   Waiting for application shutdown.
INFO:   Application shutdown complete.
INFO:   Finished server process [171932]
```

   </td>
   </tr>
   </table>
  </html>


<br>


## 🧪 3. Ejecutar servidor ```mcp_server_calc.py``` y cliente "Visual Studio Code"

1. Primero hay que ejecutar el servidor MCP:
   ```bash
   python3 ./mcp_server_calc.py
   ```
2. Si no se ha hecho antes, hay que dar de alta el servicio MCP en el cliente "Visual Studio Code":
   * From command line:
     <pre>
     code --add-mcp "{\"servers\":{\"mcp_calc\":{\"url\":\"http://localhost:8000/mcp/\",\"type\":\"http\"}}}"
     </pre>
   * Manual:
     <html>
     <table>
     <tr> <td>1.</td>
          <td>Hay que abrir la paleta de comandos con Ctrl-Alt-P y seleccionar "MCP: añadir servidor":<br>
          <img src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/lab-mcp-jsonrpc/images/cfg1.png" height="125"></td> </tr>
     <tr> <td>2.</td>
          <td>A continuación, hay que seleccionar servidor HTTP:<br>
          <img src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/lab-mcp-jsonrpc/images/cfg2.png" height="200"></td> </tr>
     <tr> <td>3.</td>
          <td>A continuación, hay que indicar la dirección URL:<br>
          <img src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/lab-mcp-jsonrpc/images/cfg3.png" height="100"></td> </tr>
     <tr> <td>4.</td>  <td>A continuación, hay que indicar el nombre:<br>
          <img src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/lab-mcp-jsonrpc/images/cfg4.png" height="125"></td> </tr>
     <tr> <td>5.</td>  <td>Y finalmente, hacer global (o local al espacio de trabajo):<br>
          <img src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/lab-mcp-jsonrpc/images/cfg5.png" height="125"></td> </tr>
     </table>
     </html>
4. Una vez configurado, para usar el servicio en "Visual Studio Code":
   <html>
   <table>
   <tr> <td>1.</td>
        <td>Hay que hacer click en herramientas en el chat:<br>
        <img src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/lab-mcp-jsonrpc/images/clt1.png" height="110"></td> </tr>
   <tr> <td>2.</td>
        <td>Hay que activar el servidor my-mcp-server (y las utilidades):<br>
        <img src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/lab-mcp-jsonrpc/images/clt2.png" height="250"></td> </tr>
   <tr> <td>3.</td>
        <td>Hay que indicar en el chat que se quiere "add 1 and 2 with my-mcp-server":<br>
        <img src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/lab-mcp-jsonrpc/images/clt3.png" height="250"></td> </tr>
   <tr> <td>4.</td>
        <td>Puede ser necesario dar permisos ("Allow") para usar el servicio:<br>
        <img src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/lab-mcp-jsonrpc/images/clt4.png" height="250"></td> </tr>
   <tr> <td>5.</td>
        <td>Se tiene el resultado:<br>
        <img src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/lab-mcp-jsonrpc/images/clt5.png" height="225"></td> </tr>
   </table>
   </html>


## Información adicional

* Tutorial
  * [How to Build an MCP Server in Python: A Complete Guide](https://scrapfly.io/blog/posts/how-to-build-an-mcp-server-in-python-a-complete-guide)
  * [Building a StreamableHTTP MCP server](https://mcpcat.io/guides/building-streamablehttp-mcp-server/)
  * [Use MCP servers in VS Code](https://code.visualstudio.com/docs/copilot/customization/mcp-servers)
* Ejemplo
  * [Ejemplo de Servidor MCP server](https://gofastmcp.com/tutorials/create-mcp-server)
  * [MCP server (SSE) for weather information for a specified location](https://github.com/justjoehere/mcp-weather-sse)
  * [Let's write a Remote MCP Server](https://shivdeepak.com/posts/lets-write-a-remote-mcp-server/)

