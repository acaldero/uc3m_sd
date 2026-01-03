#!/bin/bash
set -x

echo "starting MCP calc server..."
python3 ./mcp_server_calc.py &
sleep 3

echo "starting MCP calc client..."
python3 ./mcp_client_calc.py
sleep 3

killall python3

