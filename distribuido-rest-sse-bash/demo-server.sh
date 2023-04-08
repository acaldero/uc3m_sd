#!/bin/bash
set -x

./demo.sh | nc -l -p 8080

