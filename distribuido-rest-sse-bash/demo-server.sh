#!/bin/bash
set -x

case "$OSTYPE" in
  linux*)   ./demo.sh | nc -l -p 8080
            ;;
  darwin*)  ./demo.sh | nc -l localhost 8080
            ;; 
  *)        ./demo.sh | nc -l -p 8080
            ;;
esac

