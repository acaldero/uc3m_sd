#!/bin/bash
set -x

echo "Install uv..."
curl -LsSf https://astral.sh/uv/install.sh | sh

echo "Install uv/requirements..."
touch pyproject.toml
uv add --dev -r requirements.txt

