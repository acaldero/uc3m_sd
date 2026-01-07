
#
# Import
#

from fastapi import FastAPI
from fastmcp import FastMCP
import uvicorn


#
# A. Defime the "mcp" object
#

## Initialize FastMCP
mcp = FastMCP("calculator")

## Definie utilidades (*tools*)
@mcp.tool()
def add(a: int, b: int) -> int:
    """Add two numbers (param a and param b) and return the result."""
    return a + b

@mcp.tool()
def sub(a: int, b: int) -> int:
    """Substract two numbers (param a and param b) and return the result."""
    return a - b

@mcp.tool()
def mul(a: int, b: int) -> int:
    """Multiply two numbers (param a and param b) and return the result."""
    return a * b

@mcp.tool()
def div(a: int, b: int) -> float:
    """Divide two numbers (param a and param b) and return the result."""
    return a / b

## Define entradas (*prompts*)
@mcp.prompt()
def use_calculator(action: str, a: float, b: float) -> str:
    """Provide a template to use the calculator MCP server with two numbers (param a and param b)."""
    return f"Check that the {action} is add, substract or multiply over two numbers {a} and {b}." \
            "It can also be divide {a} by {b} if and only if {b} is no zero." \
            "If {b} is zero the result is NaN (not a number)." \
            "Use the add, sub, mul div tools to compute the result." \
            "If you don't know how to compute the result, instead of making up an answer, say that you don't know."

## Define recursos (*resources*)
@mcp.resource("file://readme")
def read_readme() -> str:
    """Read the readme markdown."""
    with open('README.md', 'r') as file:
         content = file.read()
    return content


#
# B. Defime "api" object
#

## Initialize FastAPI
mcp_app = mcp.http_app(path="/")
api = FastAPI(lifespan=mcp_app.lifespan)

## Obtener status del servicio como API REST
@api.get("/api/status")
def status():
    return {"status": "ok"}

## Monta MCP Streamable HTTP en "/mcp"
api.mount("/mcp", mcp_app)


##
## Main
##

if __name__ == "__main__":
    uvicorn.run(api, host="0.0.0.0", port=8000)

