#!/bin/bash

echo "=== Building miniRT Docker Image ==="
echo "This will create a Linux environment with valgrind for memory leak testing"
echo ""

# Build the Docker image
docker-compose -f docker-test/docker-compose.yml build

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Docker image built successfully!"
    echo ""
    echo "To run the container:"
    echo "  ./docker-test/run.sh"
    echo ""
    echo "To test a specific scene:"
    echo "  ./docker-test/test_scene.sh scenes/sample.rt"
    echo ""
    echo "To run all tests:"
    echo "  ./docker-test/test_all.sh"
else
    echo ""
    echo "❌ Failed to build Docker image!"
    exit 1
fi
