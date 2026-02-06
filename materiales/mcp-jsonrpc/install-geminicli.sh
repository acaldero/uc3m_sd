#!/bin/bash
set -x

if [ ! -f $HOME/.nvm/nvm.sh ]; then
     curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.3/install.sh | bash
     export NVM_DIR="$HOME/.nvm"
     [ -s "$NVM_DIR/nvm.sh" ]          && \. "$NVM_DIR/nvm.sh"
     [ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"
fi

echo "Installing gemini-cli..."
npm install -g @google/gemini-cli

