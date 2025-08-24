#!/bin/bash

echo "=== Stopping miniRT Docker Container ==="

# Stop and remove the container
docker-compose -f docker-test/docker-compose.yml down

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Container stopped successfully!"
else
    echo ""
    echo "❌ Failed to stop container!"
    exit 1
fi
