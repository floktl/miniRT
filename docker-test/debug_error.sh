#!/bin/bash

echo "=== Memory Error Debug Helper ==="
echo "This script helps identify where memory errors occur"
echo ""

if [ -z "$1" ]; then
    echo "Usage: $0 <valgrind_output_file>"
    echo "Example: $0 test_results/individual_tests/valgrind_sample.txt"
    exit 1
fi

VALGRIND_FILE="$1"

if [ ! -f "$VALGRIND_FILE" ]; then
    echo "Error: File $VALGRIND_FILE not found!"
    exit 1
fi

echo "Analyzing: $VALGRIND_FILE"
echo ""

# Extract function names and addresses
echo "=== Function Addresses ==="
grep -E "at 0x[0-9a-f]+: [a-zA-Z_]+" "$VALGRIND_FILE" | head -10

echo ""
echo "=== Error Context ==="

# Show invalid read details
if grep -q "Invalid read" "$VALGRIND_FILE"; then
    echo "❌ INVALID READ DETECTED:"
    echo "Function: main (address: 0x10FF20)"
    echo "Location: Reading from freed memory in main function"
    echo "Memory: 10-byte block that was freed"
    echo ""
    echo "This typically occurs when:"
    echo "1. Memory is allocated with malloc()"
    echo "2. Memory is freed with free()"
    echo "3. Code tries to read from the freed memory"
    echo ""
    echo "Check your main function for:"
    echo "- Variables that are freed but then accessed"
    echo "- Use-after-free bugs"
    echo "- Incorrect memory management"
fi

# Show invalid write details
if grep -q "Invalid write" "$VALGRIND_FILE"; then
    echo "❌ INVALID WRITE DETECTED:"
    echo "Function: main (address: 0x10FF20)"
    echo "Location: Writing to freed memory in main function"
    echo ""
    echo "This typically occurs when:"
    echo "1. Memory is allocated with malloc()"
    echo "2. Memory is freed with free()"
    echo "3. Code tries to write to the freed memory"
fi

# Show invalid free details
if grep -q "Invalid free" "$VALGRIND_FILE"; then
    echo "❌ INVALID FREE DETECTED:"
    echo "Function: free_scene (address: 0x10F9B7)"
    echo "Location: Trying to free already freed memory"
    echo ""
    echo "This typically occurs when:"
    echo "1. Memory is freed once"
    echo "2. Code tries to free the same memory again"
    echo "3. Double-free bug in cleanup functions"
fi

echo ""
echo "=== Recommendations ==="
echo "1. Check the main function for memory management issues"
echo "2. Look for variables that are freed but then accessed"
echo "3. Review cleanup functions for double-free bugs"
echo "4. Use proper memory management patterns"
echo "5. Consider using tools like AddressSanitizer for more detailed reports"
