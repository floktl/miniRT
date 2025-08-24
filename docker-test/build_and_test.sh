#!/bin/bash

echo "=== Building miniRT with Live Updates ==="
echo "Setting up compiler and build environment..."

# Fix the Makefile to use GCC with debug symbols
if [ -f "Makefile" ]; then
    echo "Configuring Makefile for GCC with debug symbols..."
    # Use a different approach to avoid sed issues with volume mounts
    cp Makefile Makefile.backup
    cat Makefile.backup | sed 's|CC := /usr/bin/clang|CC := gcc|g' | sed 's|CXX := /usr/bin/clang++|CXX := g++|g' | sed 's|-g0|-g|g' | sed 's/-O3/-O0/g' > Makefile
    rm Makefile.backup
fi

# Build libft first (with debug symbols)
if [ -d "libft" ]; then
    echo "Building libft with debug symbols..."
    cd libft
    if [ -f "Makefile" ]; then
        # Use a different approach to avoid sed issues with volume mounts
        cp Makefile Makefile.backup
        cat Makefile.backup | sed 's|CC := /usr/bin/clang|CC := gcc|g' | sed 's|-g0|-g|g' | sed 's/-O3/-O0/g' > Makefile
        rm Makefile.backup
    fi
    make clean && make
    cd ..
fi

# Build the main project
echo "Building main project with debug symbols..."
make clean && make all

echo "=== Build Complete ==="
echo "Ready for testing with live file updates!"
echo ""
echo "Available commands:"
echo "  ./run_valgrind.sh <scene_file>  - Test specific scene"
echo "  make test-all                    - Test all scenes"
echo "  make clean && make all          - Rebuild after changes"
