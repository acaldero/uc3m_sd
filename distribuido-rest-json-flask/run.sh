#!/bin/sh
set -x

echo "Initialize flask..."
FLASK_PATH=$HOME/miniforge3/bin/
FLASK_APP=app.py FLASK_DEBUG=true  $FLASK_PATH/flask run &

sleep 2

echo " * Get initial list of arrays -> []"
curl -i http://127.0.0.1:5000/ddaa \
     -X GET

sleep 1

echo " * Add a new array to the list of arrays -> [ {name:"first", array:{}} ]"
curl -i http://127.0.0.1:5000/ddaa \
     -X POST \
     -H 'Content-Type: application/json' \
     -d '{"name":"first", "array": {}}'

sleep 1

echo " * Add a new array to the list of arrays -> [ {name:"first", array:{}}, {name:"second", array:{}} ]"
curl -i http://127.0.0.1:5000/ddaa \
     -X POST \
     -H 'Content-Type: application/json' \
     -d '{"name":"second", "array": {}}'

sleep 1

echo " * Add a new element to the array to the list of arrays -> ..."
curl -i http://127.0.0.1:5000/ddaa/first/0/value \
     -X PUT

sleep 1

echo " * Get a new array to the list of arrays -> ..."
curl -i http://127.0.0.1:5000/ddaa/first/0 \
     -X GET

sleep 1

echo " * Get initial list of array -> []"
curl -i http://127.0.0.1:5000/ddaa \
     -X GET

sleep 1

echo "Finalize flask..."
kill $(pgrep -f flask)

