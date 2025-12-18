import asyncio
from fastmcp import Client

async def main():
    # Conectar al servidor MCP vía HTTP
    client = Client("http://127.0.0.1:8000/mcp/")

    # Abrir sesión
    async with client:
        # Listar herramientas disponibles
        tools = await client.list_tools()
        print("Herramientas disponibles:")
        for tool in tools:
            print("-", tool.name)

        # Llamar a add(1,2)
        result = await client.call_tool(
            "add",
            {"a": 1, "b": 2}
        )

        print("\nResultado:")
        print(result)

if __name__ == "__main__":
    asyncio.run(main())

