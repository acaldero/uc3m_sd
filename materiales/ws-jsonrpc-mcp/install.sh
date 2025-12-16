#!/bin/bash
set -x

sudo apt install uvicorn

pip3 install fastmcp fastapi httpx --break-system-packages

