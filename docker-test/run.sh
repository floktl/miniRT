#!/bin/bash

echo "=== Starting miniRT Docker Container ==="
echo "Container will start in interactive mode"
echo ""

# Detect available docker-compose command
if command -v docker-compose >/dev/null 2>&1; then
    COMPOSE_CMD=(docker-compose)
elif command -v docker >/dev/null 2>&1 && docker compose version >/dev/null 2>&1; then
    COMPOSE_CMD=(docker compose)
else
    echo "❌ Neither docker-compose nor docker compose is installed." >&2
    exit 1
fi

# Start the container in detached mode
"${COMPOSE_CMD[@]}" -f docker-test/docker-compose.yml up -d

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
