from fastapi import FastAPI
from fastmcp import FastMCP
import uvicorn


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
def div(a: int, b: int) -> int:
    """Divide two numbers and return the result."""
    return a / b

# Entradas (*prompts*)
@mcp.prompt()
def calculator_prompt(a: float, b: float, operation: str) -> str:
    if operation == "add":
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


# Initialize FastAPI
mcp_app = mcp.http_app(path="/")
api = FastAPI(lifespan=mcp_app.lifespan)

## Get status
@api.get("/api/status")
def status():
    return {"status": "ok"}


# Mount MCP at /mcp
api.mount("/mcp", mcp_app)

if __name__ == "__main__":
    uvicorn.run(api, host="0.0.0.0", port=8000)

