#!/bin/bash

echo "Starting script execution..."

# Load NVM (Node Version Manager)
export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"

echo "Installing Node.js 14..."
nvm install 14

echo "Switching to Node.js 14..."
nvm use 14

