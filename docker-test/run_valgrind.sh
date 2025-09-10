#!/bin/bash

echo "=== Running Valgrind Memory Error Test ==="
echo "Scene: $1"
echo "========================================="

if [ -z "$1" ]; then
    echo "Usage: ./run_valgrind.sh <scene_file>"
    echo "Available scenes:"
    ls -1 scenes/*.rt 2>/dev/null || echo "No .rt files found in scenes/"
    ls -1 scenes/miniRT_samples/*.rt 2>/dev/null || echo "No .rt files found in scenes/miniRT_samples/"
    exit 1
fi

if [ ! -f "$1" ]; then
    echo "Error: Scene file $1 not found!"
    exit 1
fi

echo "Running valgrind on miniRT with scene: $1"
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --show-reachable=yes \
         --suppressions=valgrind.supp \
         --verbose \
         --log-file=valgrind_output.txt \
         --error-exitcode=0 \
         --demangle=no \
         --num-callers=20 \
         --track-origins=yes \
         --show-mismatched-frees=yes \
         --show-possibly-lost=yes \
         --gen-suppressions=all \
         --keep-debuginfo=no \
         --read-var-info=no \
         ./miniRT "$1" 2>&1 | grep -E "(definitely lost|indirectly lost|possibly lost|Invalid read|Invalid write|Use of uninitialised value|Conditional jump|ERROR SUMMARY)" || true

echo ""
echo "=== Valgrind Summary ==="
echo "Full output saved to: valgrind_output.txt"
echo "Checking for memory errors and leaks..."

definitely_line=$(grep "definitely lost" valgrind_output.txt)
definitely_bytes=$(echo "$definitely_line" | awk '{print $4}')
if [ "$definitely_bytes" != "0" ]; then
    echo "❌ DEFINITE LEAKS DETECTED!"
    echo "$definitely_line"
else
    echo "✅ No definite leaks detected"
fi

indirect_line=$(grep "indirectly lost" valgrind_output.txt)
indirect_bytes=$(echo "$indirect_line" | awk '{print $4}')
if [ "$indirect_bytes" != "0" ]; then
    echo "⚠️  INDIRECT LEAKS DETECTED!"
    echo "$indirect_line"
else
    echo "✅ No indirect leaks detected"
fi

possible_line=$(grep "possibly lost" valgrind_output.txt)
possible_bytes=$(echo "$possible_line" | awk '{print $4}')
if [ "$possible_bytes" != "0" ]; then
    echo "⚠️  POSSIBLE LEAKS DETECTED!"
    echo "$possible_line"
else
    echo "✅ No possible leaks detected"
fi

# Check for invalid reads/writes
if grep -q "Invalid read" valgrind_output.txt; then
    echo "❌ INVALID READS DETECTED!"
    echo "Details:"
    grep -A 10 -B 2 "Invalid read" valgrind_output.txt | head -30
    echo ""
    echo "📍 EXACT ERROR LOCATION:"
    # Extract function name and address from Valgrind output
    ERROR_LINE=$(grep -A 1 "Invalid read" valgrind_output.txt | tail -1 | sed 's/.*at \(0x[0-9A-F]*\): \(.*\) (in.*/\2/')
    ERROR_ADDR=$(grep -A 1 "Invalid read" valgrind_output.txt | tail -1 | sed 's/.*at \(0x[0-9A-F]*\):.*/\1/')
    echo "   Function: $ERROR_LINE"
    echo "   Address: $ERROR_ADDR"
    echo "   Error: Reading from freed memory"
    echo ""
    echo "Function call stack:"
    grep -A 15 "Invalid read" valgrind_output.txt | grep "at 0x" | head -10
    echo "..."
else
    echo "✅ No invalid reads detected"
fi

if grep -q "Invalid write" valgrind_output.txt; then
    echo "❌ INVALID WRITES DETECTED!"
    echo "Details:"
    grep -A 5 -B 2 "Invalid write" valgrind_output.txt | head -20
    echo "..."
else
    echo "✅ No invalid writes detected"
fi

# Check for uninitialized values
if grep -q "Use of uninitialised value" valgrind_output.txt; then
    echo "❌ UNINITIALIZED VALUES DETECTED!"
    echo "Details:"
    grep -A 5 -B 2 "Use of uninitialised value" valgrind_output.txt | head -20
    echo "..."
else
    echo "✅ No uninitialized values detected"
fi

# Check for conditional jumps on uninitialized values
if grep -q "Conditional jump" valgrind_output.txt; then
    echo "❌ CONDITIONAL JUMPS ON UNINITIALIZED VALUES DETECTED!"
    echo "Details:"
    grep -A 5 -B 2 "Conditional jump" valgrind_output.txt | head -20
    echo "..."
else
    echo "✅ No conditional jumps on uninitialized values detected"
fi

echo ""
echo "=== Error Summary ==="
if grep -q "ERROR SUMMARY" valgrind_output.txt; then
    echo "Valgrind Error Summary:"
    grep -A 10 "ERROR SUMMARY" valgrind_output.txt
fi

echo ""
echo "=== Debug Information ==="
if grep -Eq "Invalid read|Invalid write|Invalid free|definitely lost: [1-9]" valgrind_output.txt; then
    echo "For detailed error analysis, run:"
    echo "  ./debug_error.sh valgrind_output.txt"
    echo ""
    echo "Quick error summary:"
    if grep -q "Invalid read" valgrind_output.txt; then
        ERROR_LINE=$(grep -A 1 "Invalid read" valgrind_output.txt | tail -1 | sed 's/.*at \(0x[0-9A-F]*\): \(.*\) (in.*/\2/')
        echo "- Invalid read detected in $ERROR_LINE function"
    fi
    if grep -q "Invalid write" valgrind_output.txt; then
        echo "- Invalid write detected in main function"
    fi
    if grep -q "Invalid free" valgrind_output.txt; then
        echo "- Invalid free detected in free_scene function"
    fi
    if grep -q "definitely lost: [1-9]" valgrind_output.txt; then
        echo "- Memory leak detected"
    fi
fi

echo ""
echo "=== Test Complete ==="
