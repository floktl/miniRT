#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <scene_file>"
    echo "Example: $0 scenes/sample.rt"
    exit 1
fi

SCENE_FILE="$1"
TEST_RESULT_FILE="test_results/test_summary.txt"

echo "=== Testing Scene with Valgrind ==="
echo "Scene: $SCENE_FILE"
echo ""

# Create test_results directory and subdirectories if they don't exist
mkdir -p test_results
mkdir -p test_results/individual_tests

# Check if container is running
if ! docker ps | grep -q minirt-valgrind-test; then
    echo "Starting container..."
    ./docker-test/run.sh > /dev/null 2>&1
fi

# Run the valgrind test and capture output
echo "Running valgrind test..."
docker exec -it minirt-valgrind-test bash -c "./run_valgrind.sh \"$SCENE_FILE\" 2>&1" > "$TEST_RESULT_FILE"

# Copy detailed valgrind results to host (overwrite existing)
echo "Copying detailed results to host..."
docker cp minirt-valgrind-test:/app/valgrind_output.txt ./test_results/individual_tests/valgrind_$(basename "$SCENE_FILE" .rt).txt

# Analyze results and show summary
echo ""
echo "=== Test Summary ==="
if grep -q "❌ DEFINITE LEAKS DETECTED\|❌ INVALID READS DETECTED\|❌ INVALID WRITES DETECTED\|❌ UNINITIALIZED VALUES DETECTED\|❌ CONDITIONAL JUMPS ON UNINITIALIZED VALUES DETECTED" "$TEST_RESULT_FILE"; then
    echo "❌ FAILED: Memory errors detected"
    echo "   Check: $TEST_RESULT_FILE for details"
elif grep -q "⚠️  INDIRECT LEAKS DETECTED" "$TEST_RESULT_FILE"; then
    echo "⚠️  WARNING: Indirect leaks detected"
    echo "   Check: $TEST_RESULT_FILE for details"
elif grep -q "⚠️  POSSIBLE LEAKS DETECTED" "$TEST_RESULT_FILE"; then
    echo "⚠️  WARNING: Possible leaks detected"
    echo "   Check: $TEST_RESULT_FILE for details"
else
    echo "✅ PASSED: No memory errors detected"
fi

echo "Detailed results saved to: $TEST_RESULT_FILE"
echo "Valgrind output saved to: test_results/individual_tests/"
