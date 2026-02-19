#!/bin/bash
set -x

python3 ./demo-server.py &
sleep 1

python3 -m http.server &
sleep 1

firefox http://localhost:8000/demo-client.html

killall python3


