#!/bin/bash
set -x

case "$OSTYPE" in
  linux*)   ./demo-server-bash-helper.sh | nc -l -p 5000
            ;;
  darwin*)  ./demo-server-bash-helper.sh | nc -l localhost 5000
            ;; 
  *)        ./demo-server-bash-helper.sh | nc -l -p 5000
            ;;
esac

