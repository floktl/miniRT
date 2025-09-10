#!/bin/bash
set -euo pipefail

echo "=== Testing All Scenes with Valgrind ==="
echo "This will test all .rt files found in scenes/ and scenes/miniRT_samples/"
echo ""

# Create test_results directory and subdirectories if they don't exist
mkdir -p test_results/individual_tests

# Create/overwrite summary file
SUMMARY_FILE="test_results/test_summary_all.txt"
{
  echo "=== miniRT Valgrind Test Summary ==="
  echo "Date: $(date)"
  echo ""
} > "$SUMMARY_FILE"

# Ensure container exists and is running
CONTAINER="minirt-valgrind-test"

if ! docker ps --format '{{.Names}}' | grep -qx "$CONTAINER"
then
    if docker ps -a --format '{{.Names}}' | grep -qx "$CONTAINER"
    then
        echo "Starting existing container..."
        docker start "$CONTAINER" >/dev/null
    else
        echo "Creating and starting container..."
        ./docker-test/run.sh >/dev/null 2>&1
    fi
fi

# Collect *.rt files
SCENE_FILES=()
if [ -d "scenes" ]
then
    # POSIX-safe find (no -print0 needed here)
    while IFS= read -r -d '' f
    do
        SCENE_FILES+=("$f")
    done < <(find scenes -type f -name '*.rt' -print0)
fi

if [ ${#SCENE_FILES[@]} -eq 0 ]
then
    echo "❌ No .rt files found in scenes/ directory!"
    exit 1
fi

echo "Found ${#SCENE_FILES[@]} scene files to test..."
echo "Running tests (results will be saved to files)..."
echo ""

# Counters
PASSED=0
FAILED=0

for scene in "${SCENE_FILES[@]}"
do
    base="$(basename "$scene" .rt)"
    echo "Testing: ${base}.rt"

    TEST_RESULT_FILE="test_results/individual_tests/test_${base}.txt"
    VALGRIND_LOG_HOST="test_results/individual_tests/valgrind_${base}.txt"

    # Run inside container; DO NOT allocate TTY (-t)
    # Capture exit code reliably.
    set +e
    docker exec -i "$CONTAINER" bash -lc "./run_valgrind.sh \"$scene\"" > "$TEST_RESULT_FILE" 2>&1
    rc=$?
    set -e

    # Pull container-side valgrind log to host (ignore errors if not present)
    docker cp "$CONTAINER":/app/valgrind_output.txt "$VALGRIND_LOG_HOST" >/dev/null 2>&1 || true

    if [ $rc -eq 0 ]
    then
        echo "  ✅ PASSED"
        echo "  ✅ PASSED" >> "$SUMMARY_FILE"
        : $((PASSED++))
    else
        echo "  ❌ FAILED (exit code $rc)"
        echo "  ❌ FAILED (exit code $rc)" >> "$SUMMARY_FILE"
        : $((FAILED++))
    fi
done

# Summary
{
  echo ""
  echo "=== Summary Statistics ==="
  echo "Total tests: ${#SCENE_FILES[@]}"
  echo "Passed: $PASSED"
  echo "Failed: $FAILED"
} >> "$SUMMARY_FILE"

echo ""
echo "=== Test Summary ==="
echo "Total tests: ${#SCENE_FILES[@]}"
echo "✅ Passed: $PASSED"
echo "❌ Failed: $FAILED"

if [ $FAILED -eq 0 ]
then
    echo ""
    echo "🎉 All tests passed! No memory leaks or errors (per Valgrind)."
else
    echo ""
    echo "❌ Some tests failed. Check individual result files for details."
fi

echo ""
echo "Detailed results saved to: $SUMMARY_FILE"
echo "Individual test files saved to: test_results/individual_tests/"
