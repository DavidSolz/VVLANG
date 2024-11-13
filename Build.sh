#!/bin/bash

command_exists() {
    command -v "$1" >/dev/null 2>&1
}

if ! command_exists git; then
    echo "Error: Git is not installed. Please install Git."
    exit 1
fi

if ! command_exists cmake; then
    echo "Error: CMake is not installed. Please install CMake."
    exit 1
fi

BUILD_DIR="build"

echo "Fetching submodules..."
git submodule update --init --recursive || { echo "Failed to update submodules."; exit 1; }

if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

echo "Composing dependencies..."
cmake -G "Unix Makefiles" -B "$BUILD_DIR" || { echo "CMake configuration failed"; exit 1; }

echo "Compiling project..."
cmake --build "$BUILD_DIR" || { echo "Build failed"; exit 1; }

echo "Copying configuration..."
cp -R blocks $BUILD_DIR/ || { echo "Failed to copy configuration"; exit 1; }

echo "Build completed successfully."
