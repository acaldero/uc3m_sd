#!/bin/bash
set -x

echo "Installing uv..."
curl -LsSf https://astral.sh/uv/install.sh | sh
source $HOME/.local/bin/env

echo "Installing fastAPI"
sudo apt install uvicorn python3-fastapi python3-httpx python3-starlette -y
python3 -m pip install fastmcp --break-system-packages

echo "Installing uv/requirements..."
touch pyproject.toml
uv add --dev -r requirements.txt

