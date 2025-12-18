
##
## Import
##

from fastapi import FastAPI
from fastmcp import FastMCP
import uvicorn

from mcp.server.sse         import SseServerTransport
from starlette.applications import Starlette
from starlette.routing      import Mount, Route


##
## Defime "mcp" object
##

# Initialize FastMCP
mcp = FastMCP("calculator")

## Utilidades (*tools*)
@mcp.tool()
def add(a: int, b: int) -> int:
    """Add two numbers and return the result."""
    return a + b

@mcp.tool()
def sub(a: int, b: int) -> int:
    """Substract two numbers and return the result."""
    return a - b

@mcp.tool()
def mul(a: int, b: int) -> int:
    """Multiply two numbers and return the result."""
    return a * b

@mcp.tool()
def div(a: int, b: int) -> float:
    """Divide two numbers and return the result."""
    return a / b

# Entradas (*prompts*)
@mcp.prompt()
def calculator_prompt(a: float, b: float, operation: str) -> str:
    """Prompt for calculator."""
    if   operation == "add":
         return f"The result of adding {a} and {b} is {add(a, b)}"
    elif operation == "subtract":
         return f"The result of subtracting {b} from {a} is {sub(a, b)}"
    elif operation == "multiply":
         return f"The result of multiplying {a} and {b} is {mul(a, b)}"
    elif operation == "divide":
         try:
            return f"The result of dividing {a} by {b} is {div(a, b)}"
         except ValueError as e:
            return str(e)
    else:
         return "Invalid operation. Please choose add, subtract, multiply, or divide."


##
## Defime "api" object
##

# Initialize FastAPI
mcp_app = mcp.http_app(path="/")
api = FastAPI(lifespan=mcp_app.lifespan)

## Obtener status del servicio como API REST
@api.get("/api/status")
def status():
    return {"status": "ok"}

# Monta MCP Streamable HTTP en "/mcp"
api.mount("/mcp", mcp_app)


##
## Define SSE "bridge" app
##

# El cliente abrirá SSE en /sse y enviará POSTs a /messages
def create_sse_app(mcp: FastMCP) -> Starlette:
    transport = SseServerTransport("/messages/")

    async def handle_sse(request):
        async with transport.connect_sse(
            request.scope, request.receive, request._send
        ) as streams:
            await mcp._mcp_server.run(
                streams[0],
                streams[1],
                mcp._mcp_server.create_initialization_options(),
            )

    return Starlette(
        routes=[
            Route("/sse/",      endpoint=handle_sse),
            Mount("/messages/", app=transport.handle_post_message),
        ]
    )

# monta SSE en "/mcp-sse" para no mezclar con "/mcp"
api.mount("/mcp-sse", create_sse_app(mcp))


##
## Main
##

if __name__ == "__main__":
    uvicorn.run(api, host="0.0.0.0", port=8000)

