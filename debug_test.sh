#!/bin/bash

echo "=== Debug Test Script ==="
echo "Testing the grep pattern logic on the failing test file..."

TEST_FILE="test_results/individual_tests/test_17_tricky_spacing_but_valid_if_tolerant.txt"

echo "1. Checking if test file exists:"
if [ -f "$TEST_FILE" ]; then
    echo "   ✅ File exists"
    echo "   File size: $(wc -c < "$TEST_FILE") bytes"
else
    echo "   ❌ File does not exist"
    exit 1
fi

echo ""
echo "2. Checking file content (first 10 lines):"
head -10 "$TEST_FILE"

echo ""
echo "3. Testing the exact grep pattern from test_all.sh:"
PATTERN="❌ DEFINITE LEAKS DETECTED\|❌ INVALID READS DETECTED\|❌ INVALID WRITES DETECTED\|❌ UNINITIALIZED VALUES DETECTED\|❌ CONDITIONAL JUMPS ON UNINITIALIZED VALUES DETECTED"

echo "   Pattern: $PATTERN"
echo "   Running: grep -q \"$PATTERN\" \"$TEST_FILE\""

if grep -q "$PATTERN" "$TEST_FILE"; then
    echo "   ❌ PATTERN FOUND - This would mark test as FAILED"
    echo "   Found lines:"
    grep "$PATTERN" "$TEST_FILE"
else
    echo "   ✅ NO PATTERN FOUND - This should mark test as PASSED"
fi

echo ""
echo "4. Testing individual patterns:"
echo "   Checking for '❌ DEFINITE LEAKS DETECTED':"
if grep -q "❌ DEFINITE LEAKS DETECTED" "$TEST_FILE"; then
    echo "   ❌ FOUND"
else
    echo "   ✅ NOT FOUND"
fi

echo "   Checking for '❌ INVALID READS DETECTED':"
if grep -q "❌ INVALID READS DETECTED" "$TEST_FILE"; then
    echo "   ❌ FOUND"
else
    echo "   ✅ NOT FOUND"
fi

echo "   Checking for '❌ INVALID WRITES DETECTED':"
if grep -q "❌ INVALID WRITES DETECTED" "$TEST_FILE"; then
    echo "   ❌ FOUND"
else
    echo "   ✅ NOT FOUND"
fi

echo "   Checking for '❌ UNINITIALIZED VALUES DETECTED':"
if grep -q "❌ UNINITIALIZED VALUES DETECTED" "$TEST_FILE"; then
    echo "   ❌ FOUND"
else
    echo "   ✅ NOT FOUND"
fi

echo "   Checking for '❌ CONDITIONAL JUMPS ON UNINITIALIZED VALUES DETECTED':"
if grep -q "❌ CONDITIONAL JUMPS ON UNINITIALIZED VALUES DETECTED" "$TEST_FILE"; then
    echo "   ❌ FOUND"
else
    echo "   ✅ NOT FOUND"
fi

echo ""
echo "5. Testing the warning patterns:"
echo "   Checking for '⚠️  INDIRECT LEAKS DETECTED':"
if grep -q "⚠️  INDIRECT LEAKS DETECTED" "$TEST_FILE"; then
    echo "   ⚠️  FOUND"
else
    echo "   ✅ NOT FOUND"
fi

echo "   Checking for '⚠️  POSSIBLE LEAKS DETECTED':"
if grep -q "⚠️  POSSIBLE LEAKS DETECTED" "$TEST_FILE"; then
    echo "   ⚠️  FOUND"
else
    echo "   ✅ NOT FOUND"
fi

echo ""
echo "6. Checking for any ❌ patterns in the file:"
if grep -q "❌" "$TEST_FILE"; then
    echo "   ❌ FOUND - Lines containing ❌:"
    grep "❌" "$TEST_FILE"
else
    echo "   ✅ NO ❌ patterns found"
fi

echo ""
echo "7. Checking for any ⚠️ patterns in the file:"
if grep -q "⚠️" "$TEST_FILE"; then
    echo "   ⚠️  FOUND - Lines containing ⚠️:"
    grep "⚠️" "$TEST_FILE"
else
    echo "   ✅ NO ⚠️ patterns found"
fi

echo ""
echo "=== Debug Complete ==="
