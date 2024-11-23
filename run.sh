#!/bin/bash

echo "Starting script execution..."

# Load NVM (Node Version Manager)
export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"

echo "Installing Node.js 14..."
nvm install 14

echo "Switching to Node.js 14..."
nvm use 14

echo "Installing dependencies..."
npm install

echo "Building liboqs..."
npm run liboqs:build

echo "Running build..."
npm run build

echo "Installing Node.js 18..."
nvm install 18

echo "Switching to Node.js 18..."
nvm use 18

echo "Script execution completed."
