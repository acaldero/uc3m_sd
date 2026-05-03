#!/bin/bash
set -x

./calc_server &
sleep 1

curl "http://localhost:8080/add?a=10&b=5"

sleep 1
kill -9 %1
