#!/bin/bash

echo "=== Debug Test Execution Flow ==="
echo "Simulating the exact execution flow from test_all.sh..."

# Simulate the test_all.sh logic
SCENE_FILES=($(find scenes -name "*.rt" -type f | sort))

echo "Found ${#SCENE_FILES[@]} scene files"
echo ""

# Find the 18th test (index 17)
if [ ${#SCENE_FILES[@]} -ge 18 ]; then
    scene="${SCENE_FILES[17]}"
    echo "Testing the 18th file: $scene"

    # Create the test result file name
    TEST_RESULT_FILE="test_results/individual_tests/test_$(basename "$scene" .rt).txt"
    echo "Test result file: $TEST_RESULT_FILE"

    if [ -f "$TEST_RESULT_FILE" ]; then
        echo "✅ Test result file exists"
        echo "File size: $(wc -c < "$TEST_RESULT_FILE") bytes"

        echo ""
        echo "=== Testing the exact logic from test_all.sh ==="

        # Test the exact grep pattern from test_all.sh
        PATTERN="❌ DEFINITE LEAKS DETECTED\|❌ INVALID READS DETECTED\|❌ INVALID WRITES DETECTED\|❌ UNINITIALIZED VALUES DETECTED\|❌ CONDITIONAL JUMPS ON UNINITIALIZED VALUES DETECTED"

        echo "Running: grep -q \"$PATTERN\" \"$TEST_RESULT_FILE\""
        if grep -q "$PATTERN" "$TEST_RESULT_FILE"; then
            echo "❌ PATTERN FOUND - Would mark as FAILED"
            echo "Found lines:"
            grep "$PATTERN" "$TEST_RESULT_FILE"
        else
            echo "✅ NO PATTERN FOUND - Should mark as PASSED"
        fi

        echo ""
        echo "Testing warning patterns:"
        WARNING_PATTERN="⚠️  INDIRECT LEAKS DETECTED\|⚠️  POSSIBLE LEAKS DETECTED"
        if grep -q "$WARNING_PATTERN" "$TEST_RESULT_FILE"; then
            echo "⚠️  WARNING PATTERN FOUND - Would mark as WARNING"
        else
            echo "✅ NO WARNING PATTERN FOUND"
        fi

        echo ""
        echo "=== Simulating the full if-else logic ==="
        if grep -q "$PATTERN" "$TEST_RESULT_FILE"; then
            echo "RESULT: ❌ FAILED"
        elif grep -q "$WARNING_PATTERN" "$TEST_RESULT_FILE"; then
            echo "RESULT: ⚠️  WARNING"
        else
            echo "RESULT: ✅ PASSED"
        fi

    else
        echo "❌ Test result file does not exist"
    fi
else
    echo "❌ Not enough scene files found"
fi

echo ""
echo "=== Checking all test result files ==="
echo "Looking for any files that might contain error patterns:"

for file in test_results/individual_tests/test_*.txt; do
    if [ -f "$file" ]; then
        if grep -q "❌ DEFINITE LEAKS DETECTED\|❌ INVALID READS DETECTED\|❌ INVALID WRITES DETECTED\|❌ UNINITIALIZED VALUES DETECTED\|❌ CONDITIONAL JUMPS ON UNINITIALIZED VALUES DETECTED" "$file"; then
            echo "❌ ERROR PATTERN FOUND in: $(basename "$file")"
            grep "❌ DEFINITE LEAKS DETECTED\|❌ INVALID READS DETECTED\|❌ INVALID WRITES DETECTED\|❌ UNINITIALIZED VALUES DETECTED\|❌ CONDITIONAL JUMPS ON UNINITIALIZED VALUES DETECTED" "$file"
        fi
    fi
done

echo ""
echo "=== Debug Complete ==="
