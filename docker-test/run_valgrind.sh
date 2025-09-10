#!/bin/bash
set -euo pipefail

SCENE="${1-}"

echo "=== Running Valgrind Memory Error Test ==="
echo "Scene: ${SCENE:-<none>}"
echo "========================================="

# --- Usage & input checks ----------------------------------------------------
if [ -z "${SCENE}" ]
then
    echo "Usage: ./run_valgrind.sh <scene_file>"
    echo "Available scenes:"
    ls -1 scenes/*.rt 2>/dev/null || echo "No .rt files found in scenes/"
    ls -1 scenes/miniRT_samples/*.rt 2>/dev/null || echo "No .rt files found in scenes/miniRT_samples/"
    exit 1
fi

if [ ! -f "$SCENE" ]
then
    echo "Error: Scene file '$SCENE' not found!"
    exit 1
fi

if [ ! -x ./miniRT ]
then
    echo "Error: ./miniRT not found or not executable. Build your project first."
    exit 1
fi

# --- Run Valgrind ------------------------------------------------------------
LOG_FILE="valgrind_output.txt"
: > "$LOG_FILE"

echo "Running valgrind on miniRT with scene: $SCENE"

# We deliberately allow Valgrind to return non-zero and capture it in VALGRIND_RC.
set +e
valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --errors-for-leak-kinds=definite,indirect,possible \
    --track-origins=yes \
    --show-reachable=yes \
    --suppressions=valgrind.supp \
    --verbose \
    --log-file="$LOG_FILE" \
    --error-exitcode=1 \
    --demangle=no \
    --num-callers=20 \
    --show-mismatched-frees=yes \
    --show-possibly-lost=yes \
    --gen-suppressions=all \
    --keep-debuginfo=no \
    --read-var-info=no \
    ./miniRT "$SCENE" 2>&1 \
| grep -E "(definitely lost|indirectly lost|possibly lost|Invalid read|Invalid write|Use of uninitialised value|Conditional jump|ERROR SUMMARY)" || true
VALGRIND_RC=$?
set -e

echo ""
echo "=== Valgrind Summary ==="
echo "Full output saved to: $LOG_FILE"
echo "Checking for memory errors and leaks..."

# --- Leak reporting (only non-zero bytes) ------------------------------------
has_nonzero_definite_leaks() { grep -Eq "definitely lost:\s*[1-9][0-9,]* bytes" "$LOG_FILE"; }
has_nonzero_indirect_leaks() { grep -Eq "indirectly lost:\s*[1-9][0-9,]* bytes" "$LOG_FILE"; }
has_nonzero_possible_leaks() { grep -Eq "possibly lost:\s*[1-9][0-9,]* bytes" "$LOG_FILE"; }

if has_nonzero_definite_leaks
then
    echo "❌ DEFINITE LEAKS DETECTED!"
    grep -E "definitely lost:\s*[0-9,]+ bytes" "$LOG_FILE"
else
    echo "✅ No definite leaks detected"
fi

if has_nonzero_indirect_leaks
then
    echo "❌ INDIRECT LEAKS DETECTED!"
    grep -E "indirectly lost:\s*[0-9,]+ bytes" "$LOG_FILE"
else
    echo "✅ No indirect leaks detected"
fi

if has_nonzero_possible_leaks
then
    echo "❌ POSSIBLE LEAKS DETECTED!"
    grep -E "possibly lost:\s*[0-9,]+ bytes" "$LOG_FILE"
else
    echo "✅ No possible leaks detected"
fi

# --- Invalid accesses / uninitialized ----------------------------------------
if grep -q "Invalid read" "$LOG_FILE"
then
    echo "❌ INVALID READS DETECTED!"
    echo "Details:"
    grep -A 10 -B 2 "Invalid read" "$LOG_FILE" | head -30
    echo ""
    echo "📍 EXACT ERROR LOCATION:"
    ERROR_LINE=$(grep -A 1 "Invalid read" "$LOG_FILE" | tail -1 | sed -E 's/.*at 0x[0-9A-Fa-f]+: (.*) \(in.*/\1/')
    ERROR_ADDR=$(grep -A 1 "Invalid read" "$LOG_FILE" | tail -1 | sed -E 's/.*at (0x[0-9A-Fa-f]+):.*/\1/')
    echo "   Function: ${ERROR_LINE:-unknown}"
    echo "   Address: ${ERROR_ADDR:-unknown}"
    echo "   Error: Reading from freed or invalid memory"
    echo ""
    echo "Function call stack:"
    grep -A 15 "Invalid read" "$LOG_FILE" | grep "at 0x" | head -10 || true
    echo "..."
else
    echo "✅ No invalid reads detected"
fi

if grep -q "Invalid write" "$LOG_FILE"
then
    echo "❌ INVALID WRITES DETECTED!"
    echo "Details:"
    grep -A 5 -B 2 "Invalid write" "$LOG_FILE" | head -20
    echo "..."
else
    echo "✅ No invalid writes detected"
fi

if grep -q "Use of uninitialised value" "$LOG_FILE"
then
    echo "❌ UNINITIALIZED VALUES DETECTED!"
    echo "Details:"
    grep -A 5 -B 2 "Use of uninitialised value" "$LOG_FILE" | head -20
    echo "..."
else
    echo "✅ No uninitialized values detected"
fi

if grep -q "Conditional jump" "$LOG_FILE"
then
    echo "❌ CONDITIONAL JUMPS ON UNINITIALIZED VALUES DETECTED!"
    echo "Details:"
    grep -A 5 -B 2 "Conditional jump" "$LOG_FILE" | head -20
    echo "..."
else
    echo "✅ No conditional jumps on uninitialized values detected"
fi

echo ""
echo "=== Error Summary ==="
if grep -q "ERROR SUMMARY" "$LOG_FILE"
then
    echo "Valgrind Error Summary:"
    grep -A 10 "ERROR SUMMARY" "$LOG_FILE"
fi

echo ""
echo "=== Test Complete ==="

# --- Final PASS/FAIL decision -------------------------------------------------
# PASS only when exactly "ERROR SUMMARY: 0 errors from 0 contexts" is present.
if grep -q "ERROR SUMMARY: 0 errors from 0 contexts" "$LOG_FILE"
then
    echo "✅ Valgrind PASSED (0 errors)."
    exit 0
else
    echo "❌ Valgrind FAILED (see $LOG_FILE)."
    # Use Valgrind's exit code if it failed, otherwise generic 1.
    exit $([ "$VALGRIND_RC" -ne 0 ] && echo "$VALGRIND_RC" || echo 1)
fi
