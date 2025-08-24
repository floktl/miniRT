#!/bin/bash

echo "=== Starting miniRT Docker Container ==="
echo "Container will start in interactive mode"
echo ""

# Start the container in interactive mode
docker-compose -f docker-test/docker-compose.yml up -d

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Container started successfully!"
    echo ""
    echo "To access the container:"
    echo "  docker exec -it minirt-valgrind-test bash"
    echo ""
    echo "To run valgrind test on a scene:"
    echo "  docker exec -it minirt-valgrind-test ./run_valgrind.sh scenes/sample.rt"
    echo ""
    echo "To stop the container:"
    echo "  ./docker-test/stop.sh"
else
    echo ""
    echo "❌ Failed to start container!"
    exit 1
fi
