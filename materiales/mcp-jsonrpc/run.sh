#!/bin/bash
set -x

python3 ./mcp_server_calc.py &
sleep 3

python3 ./mcp_client_calc.py
sleep 3

killall python3

