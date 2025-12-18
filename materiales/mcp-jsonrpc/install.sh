#!/bin/bash
set -x

curl -LsSf https://astral.sh/uv/install.sh | sh

touch pyproject.toml
uv add --dev -r requirements.txt

