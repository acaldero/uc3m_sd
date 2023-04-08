#!/bin/bash
set -x

echo "HTTP/1.1 200 OK"
echo "Access-Control-Allow-Origin: *"
echo "Content-Type: text/event-stream"
echo "Cache-Control: no-cache"
echo ""

while [ 1 ]; do
  T=$(date +%H:%M:%S)
  echo "data: {'timestamp': $T}\n\n"
  sleep 1
done
