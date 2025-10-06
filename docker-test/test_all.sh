#!/bin/bash

echo "=== Testing All Scenes with Valgrind ==="
echo "This will test all .rt files found in scenes/ and scenes/miniRT_samples/"
echo ""
echo "Usage: $0 [--force-container|-c]"
echo "  --force-container, -c: Force Docker container usage even on Linux"
echo ""

# Detect OS and set execution method
OS=$(uname -s)
USE_CONTAINER=false

# Check for force container flag
if [ "$1" = "--force-container" ] || [ "$1" = "-c" ]; then
    echo "🐳 Force container mode enabled"
    USE_CONTAINER=true
elif [ "$OS" = "Linux" ]; then
    echo "🐧 Linux detected - using native valgrind"
    # Check if valgrind is installed
    if ! command -v valgrind &> /dev/null; then
        echo "❌ Valgrind not found. Please install valgrind:"
        echo "   sudo apt-get install valgrind  # Ubuntu/Debian"
        echo "   sudo yum install valgrind      # CentOS/RHEL"
        echo "   sudo dnf install valgrind      # Fedora"
        echo ""
        echo "Alternatively, use --force-container to use Docker instead"
        exit 1
    fi
    USE_CONTAINER=false
else
    echo "🍎 macOS detected - using Docker container for valgrind"
    USE_CONTAINER=true
fi

# Create test_results directory and subdirectories if they don't exist
mkdir -p test_results
mkdir -p test_results/individual_tests

# Create summary file (overwrite existing)
SUMMARY_FILE="test_results/test_summary_all.txt"
echo "=== miniRT Valgrind Test Summary ===" > "$SUMMARY_FILE"
echo "Date: $(date)" >> "$SUMMARY_FILE"
echo "OS: $OS" >> "$SUMMARY_FILE"
echo "Method: $([ "$USE_CONTAINER" = "true" ] && echo "Docker Container" || echo "Native Valgrind")" >> "$SUMMARY_FILE"
echo "" >> "$SUMMARY_FILE"

# Ensure project is compiled
echo "🔨 Ensuring project is compiled..."
if [ "$USE_CONTAINER" = "true" ]; then
    # Check if container is running
    if ! docker ps | grep -q minirt-valgrind-test; then
        echo "Starting container..."
        ./docker-test/run.sh
        if [ $? -ne 0 ]; then
            echo "❌ Failed to start container. Aborting tests."
            exit 1
        fi
    fi
    # Compile in container
    echo "Compiling project in container..."
    if [ -t 1 ]; then
        TTY_FLAGS="-it"
    else
        TTY_FLAGS="-i"
    fi
    docker exec $TTY_FLAGS minirt-valgrind-test bash -c "make re"
    if [ $? -ne 0 ]; then
        echo "❌ Failed to compile project in container. Aborting tests."
        exit 1
    fi
else
    # Compile natively
    echo "Compiling project natively..."
    make re
    if [ $? -ne 0 ]; then
        echo "❌ Failed to compile project. Aborting tests."
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
    VALGRIND_OUTPUT_FILE="test_results/individual_tests/valgrind_$(basename "$scene" .rt).txt"

    if [ "$USE_CONTAINER" = "true" ]; then
        # Use Docker container for valgrind
        # Use interactive TTY when available
        if [ -t 1 ]; then
            TTY_FLAGS="-it"
        else
            TTY_FLAGS="-i"
        fi
        docker exec $TTY_FLAGS minirt-valgrind-test bash -c "./run_valgrind.sh \"$scene\" 2>&1" > "$TEST_RESULT_FILE"

        # Copy detailed valgrind results to host if it exists
        if docker exec $TTY_FLAGS minirt-valgrind-test test -f /app/valgrind_output.txt; then
            docker cp minirt-valgrind-test:/app/valgrind_output.txt "$VALGRIND_OUTPUT_FILE"
        else
            echo "Valgrind output not found" >> "$TEST_RESULT_FILE"
        fi
    else
        # Use native valgrind on Linux
        echo "Running native valgrind on: $scene"

        # Run valgrind directly and capture both stdout and stderr
        valgrind --leak-check=full \
                 --show-leak-kinds=all \
                 --track-origins=yes \
                 --show-reachable=yes \
                 --suppressions=valgrind.supp \
                 --verbose \
                 --log-file="$VALGRIND_OUTPUT_FILE" \
                 --error-exitcode=0 \
                 --demangle=no \
                 --num-callers=20 \
                 --track-origins=yes \
                 --show-mismatched-frees=yes \
                 --show-possibly-lost=yes \
                 --gen-suppressions=all \
                 --keep-debuginfo=no \
                 --read-var-info=no \
                 ./miniRT "$scene" 2>&1 | grep -E "(definitely lost|indirectly lost|possibly lost|Invalid read|Invalid write|Use of uninitialised value|Conditional jump|ERROR SUMMARY)" > "$TEST_RESULT_FILE" || true

        # Add summary analysis to test result file
        echo "" >> "$TEST_RESULT_FILE"
        echo "=== Valgrind Summary ===" >> "$TEST_RESULT_FILE"
        echo "Full output saved to: $VALGRIND_OUTPUT_FILE" >> "$TEST_RESULT_FILE"
        echo "Checking for memory errors and leaks..." >> "$TEST_RESULT_FILE"

        # Analyze valgrind output
        if [ -f "$VALGRIND_OUTPUT_FILE" ]; then
            definitely_line=$(grep "definitely lost" "$VALGRIND_OUTPUT_FILE" 2>/dev/null || echo "")
            definitely_bytes=$(echo "$definitely_line" | awk '{print $4}' 2>/dev/null || echo "0")
            if [ "$definitely_bytes" != "0" ] && [ -n "$definitely_bytes" ]; then
                echo "❌ DEFINITE LEAKS DETECTED!" >> "$TEST_RESULT_FILE"
                echo "$definitely_line" >> "$TEST_RESULT_FILE"
            else
                echo "✅ No definite leaks detected" >> "$TEST_RESULT_FILE"
            fi

            indirect_line=$(grep "indirectly lost" "$VALGRIND_OUTPUT_FILE" 2>/dev/null || echo "")
            indirect_bytes=$(echo "$indirect_line" | awk '{print $4}' 2>/dev/null || echo "0")
            if [ "$indirect_bytes" != "0" ] && [ -n "$indirect_bytes" ]; then
                echo "⚠️  INDIRECT LEAKS DETECTED!" >> "$TEST_RESULT_FILE"
                echo "$indirect_line" >> "$TEST_RESULT_FILE"
            else
                echo "✅ No indirect leaks detected" >> "$TEST_RESULT_FILE"
            fi

            possible_line=$(grep "possibly lost" "$VALGRIND_OUTPUT_FILE" 2>/dev/null || echo "")
            possible_bytes=$(echo "$possible_line" | awk '{print $4}' 2>/dev/null || echo "0")
            if [ "$possible_bytes" != "0" ] && [ -n "$possible_bytes" ]; then
                echo "⚠️  POSSIBLE LEAKS DETECTED!" >> "$TEST_RESULT_FILE"
                echo "$possible_line" >> "$TEST_RESULT_FILE"
            else
                echo "✅ No possible leaks detected" >> "$TEST_RESULT_FILE"
            fi

            # Check for invalid reads/writes
            if grep -q "Invalid read" "$VALGRIND_OUTPUT_FILE" 2>/dev/null; then
                echo "❌ INVALID READS DETECTED!" >> "$TEST_RESULT_FILE"
            else
                echo "✅ No invalid reads detected" >> "$TEST_RESULT_FILE"
            fi

            if grep -q "Invalid write" "$VALGRIND_OUTPUT_FILE" 2>/dev/null; then
                echo "❌ INVALID WRITES DETECTED!" >> "$TEST_RESULT_FILE"
            else
                echo "✅ No invalid writes detected" >> "$TEST_RESULT_FILE"
            fi

            if grep -q "Use of uninitialised value" "$VALGRIND_OUTPUT_FILE" 2>/dev/null; then
                echo "❌ UNINITIALIZED VALUES DETECTED!" >> "$TEST_RESULT_FILE"
            else
                echo "✅ No uninitialized values detected" >> "$TEST_RESULT_FILE"
            fi

            if grep -q "Conditional jump" "$VALGRIND_OUTPUT_FILE" 2>/dev/null; then
                echo "❌ CONDITIONAL JUMPS ON UNINITIALIZED VALUES DETECTED!" >> "$TEST_RESULT_FILE"
            else
                echo "✅ No conditional jumps on uninitialized values detected" >> "$TEST_RESULT_FILE"
            fi
        fi
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

if [ "$USE_CONTAINER" = "true" ]; then
    echo ""
    echo "🐳 Tests completed using Docker container"
    echo "   To stop the container: ./docker-test/stop.sh"
else
    echo ""
    echo "🐧 Tests completed using native valgrind on Linux"
    echo "   No container cleanup needed"
fi
