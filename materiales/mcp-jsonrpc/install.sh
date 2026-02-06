#!/bin/bash
set -x

echo "Installing fastapi, fastmcp, etc...."
python3 -m pip install -U fastapi fastmcp httpx starlette uvicorn --break-system-packages

echo "Installing nvm...."
if [ ! -f $HOME/.nvm/nvm.sh ]; then
     curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.3/install.sh | bash
     export NVM_DIR="$HOME/.nvm"
     [ -s "$NVM_DIR/nvm.sh" ]          && \. "$NVM_DIR/nvm.sh"
     [ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"
fi

echo "Installing nodejs + npm...."
nvm install --lts
npm install -g npm@latest
nvm use --lts

echo "Installing gemini-cli..."
npm install -g @google/gemini-cli

