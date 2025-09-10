#!/bin/bash

echo "=== Testing All Scenes with Valgrind ==="
echo "This will test all .rt files found in scenes/ and scenes/miniRT_samples/"
echo ""

# Create test_results directory and subdirectories if they don't exist
mkdir -p test_results
mkdir -p test_results/individual_tests

# Create summary file (overwrite existing)
SUMMARY_FILE="test_results/test_summary_all.txt"
echo "=== miniRT Valgrind Test Summary ===" > "$SUMMARY_FILE"
echo "Date: $(date)" >> "$SUMMARY_FILE"
echo "" >> "$SUMMARY_FILE"

# Check if container is running
if ! docker ps | grep -q minirt-valgrind-test; then
    echo "Starting container..."
    ./docker-test/run.sh
    if [ $? -ne 0 ]; then
        echo "❌ Failed to start container. Aborting tests."
        exit 1
    fi
fi

# Find all .rt files
SCENE_FILES=()
if [ -d "scenes" ]; then
    SCENE_FILES+=($(find scenes -name "*.rt" -type f))
fi

if [ ${#SCENE_FILES[@]} -eq 0 ]; then
    echo "❌ No .rt files found in scenes/ directory!"
    exit 1
fi

echo "Found ${#SCENE_FILES[@]} scene files to test..."
echo "Running tests (results will be saved to files)..."
echo ""

# Initialize counters
PASSED=0
FAILED=0
WARNINGS=0

# Test each scene
for scene in "${SCENE_FILES[@]}"; do
    echo "Testing: $(basename "$scene")"

    # Create individual test result file (overwrite existing)
    TEST_RESULT_FILE="test_results/individual_tests/test_$(basename "$scene" .rt).txt"

    # Run valgrind test and capture output
    # Use interactive TTY when available
    if [ -t 1 ]; then
        TTY_FLAGS="-it"
    else
        TTY_FLAGS="-i"
    fi
    docker exec $TTY_FLAGS minirt-valgrind-test bash -c "./run_valgrind.sh \"$scene\" 2>&1" > "$TEST_RESULT_FILE"

    # Copy detailed valgrind results to host if it exists
    if docker exec $TTY_FLAGS minirt-valgrind-test test -f /app/valgrind_output.txt; then
        docker cp minirt-valgrind-test:/app/valgrind_output.txt ./test_results/individual_tests/valgrind_$(basename "$scene" .rt).txt
    else
        echo "Valgrind output not found" >> "$TEST_RESULT_FILE"
    fi

    # Analyze results
    if grep -q "❌ DEFINITE LEAKS DETECTED\|❌ INVALID READS DETECTED\|❌ INVALID WRITES DETECTED\|❌ UNINITIALIZED VALUES DETECTED\|❌ CONDITIONAL JUMPS ON UNINITIALIZED VALUES DETECTED" "$TEST_RESULT_FILE"; then
        echo "  ❌ FAILED" >> "$SUMMARY_FILE"
        echo "  ❌ FAILED"
        ((FAILED++))
    elif grep -q "⚠️  INDIRECT LEAKS DETECTED\|⚠️  POSSIBLE LEAKS DETECTED" "$TEST_RESULT_FILE"; then
        echo "  ⚠️  WARNING" >> "$SUMMARY_FILE"
        echo "  ⚠️  WARNING"
        ((WARNINGS++))
    else
        echo "  ✅ PASSED" >> "$SUMMARY_FILE"
        echo "  ✅ PASSED"
        ((PASSED++))
    fi
done

# Write summary statistics
echo "" >> "$SUMMARY_FILE"
echo "=== Summary Statistics ===" >> "$SUMMARY_FILE"
echo "Total tests: ${#SCENE_FILES[@]}" >> "$SUMMARY_FILE"
echo "Passed: $PASSED" >> "$SUMMARY_FILE"
echo "Failed: $FAILED" >> "$SUMMARY_FILE"
echo "Warnings: $WARNINGS" >> "$SUMMARY_FILE"

# Show summary in terminal
echo ""
echo "=== Test Summary ==="
echo "Total tests: ${#SCENE_FILES[@]}"
echo "✅ Passed: $PASSED"
echo "❌ Failed: $FAILED"
echo "⚠️  Warnings: $WARNINGS"

if [ $FAILED -eq 0 ] && [ $WARNINGS -eq 0 ]; then
    echo ""
    echo "🎉 All tests passed! No memory leaks detected."
elif [ $FAILED -eq 0 ]; then
    echo ""
    echo "⚠️  All tests passed but some warnings detected."
else
    echo ""
    echo "❌ Some tests failed. Check individual result files for details."
fi

echo ""
echo "Detailed results saved to: $SUMMARY_FILE"
echo "Individual test files saved to: test_results/individual_tests/"
