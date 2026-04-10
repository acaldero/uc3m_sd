#!/bin/bash
set -x

echo "starting MCP calc server..."
python3 ./mcp_server_calc.py &
sleep 2

echo "Add MCP server..."
rm -fr .gemini
gemini mcp add --transport http mcp-calc http://localhost:8000/mcp
sleep 2
echo "Fix 'type' field..."
echo '{ "mcpServers": { "mcp-calc": { "url": "http://localhost:8000/mcp" } } }' > .gemini/settings.json

echo "starting gemini client with prompt 'add 2 + 3'..."
echo " => Please select 'Allow' and use '/quit' to end the execution."
gemini -i "add 2 + 3"

echo "stopping MCP calc server..."
killall python3

