#!/bin/bash

# Test script for miniRT scene files
# Tests all .rt files in the scenes folder and reports results

# Clear the results file at the start
RESULTS_FILE="test_results.txt"
> "$RESULTS_FILE"

echo "=== miniRT Scene File Testing Script ===" | tee -a "$RESULTS_FILE"
echo "Testing all .rt files in scenes folder..." | tee -a "$RESULTS_FILE"
echo | tee -a "$RESULTS_FILE"

# Check if miniRT executable exists
if [ ! -f "./miniRT" ]; then
    echo "Error: miniRT executable not found. Please build the project first." | tee -a "$RESULTS_FILE"
    exit 1
fi

# Initialize counters
total_files=0
correct_results=0
incorrect_results=0

# Function to determine expected behavior from filename
get_expected_behavior() {
	local filename="$1"

	# Check for invalid patterns in filename
	if [[ "$filename" == *"invalid"* ]] || [[ "$filename" == *"INVALID"* ]]; then
		# Special cases where "invalid" files are actually valid due to parser tolerance
		if [[ "$filename" == *"07_invalid_token_count_light"* ]]; then
			echo "success"  # This is actually valid due to whitespace tolerance
			return
		fi
		# Special cases for files that should still fail even with bonus features
		if [[ "$filename" == *"21_invalid_multiple_lights_mandatory_context"* ]]; then
			echo "error"  # This should still fail as it's testing mandatory context
			return
		fi
		echo "error"
	else
		# Special cases for bonus features
		if [[ "$filename" == *"05_bonus_multilights"* ]]; then
			echo "success"  # Now supports multiple lights as bonus feature
			return
		fi
		echo "success"
	fi
}

# Function to strip ANSI color codes
strip_ansi_codes() {
	local text="$1"
	# Remove ANSI escape sequences (ESC [ ... m)
	echo "$text" | sed 's/\x1b\[[0-9;]*m//g'
}

# Function to test a single file
test_file() {
    local file="$1"
    local exit_code
    local output
    local expected_behavior
    local actual_behavior
    local filename=$(basename "$file")

    echo "Testing: $file" | tee -a "$RESULTS_FILE"
    echo "----------------------------------------" | tee -a "$RESULTS_FILE"

    # Determine expected behavior
    expected_behavior=$(get_expected_behavior "$filename")
    echo "Expected: $expected_behavior" | tee -a "$RESULTS_FILE"

    # Run miniRT with the file and capture output and exit code
    output=$(./miniRT "$file" 2>&1)
    exit_code=$?

    echo "Exit code: $exit_code" | tee -a "$RESULTS_FILE"

    # Determine actual behavior
    if [ $exit_code -eq 0 ]; then
        actual_behavior="success"
        echo "Actual: ✅ SUCCESS" | tee -a "$RESULTS_FILE"
    else
        actual_behavior="error"
        echo "Actual: ❌ FAILED" | tee -a "$RESULTS_FILE"
    fi

    # Compare expected vs actual
    if [ "$expected_behavior" = "$actual_behavior" ]; then
        echo "Result: ✅ CORRECT" | tee -a "$RESULTS_FILE"
        ((correct_results++))
    else
        echo "Result: ❌ INCORRECT" | tee -a "$RESULTS_FILE"
        ((incorrect_results++))
    fi

    # Show output if there is any
    if [ -n "$output" ]; then
        echo "Output:" | tee -a "$RESULTS_FILE"
        # Show colored output in terminal, but strip ANSI codes for file
        echo "$output"
        # Strip ANSI codes and save to file
        echo "$output" | sed 's/\x1b\[[0-9;]*m//g' >> "$RESULTS_FILE"
    fi

    echo | tee -a "$RESULTS_FILE"
}

# Test all .rt files in scenes/miniRT_samples/ folder
echo "Testing files in scenes/miniRT_samples/ folder:" | tee -a "$RESULTS_FILE"
echo "================================================" | tee -a "$RESULTS_FILE"

if [ -d "scenes/miniRT_samples" ]; then
    for file in scenes/miniRT_samples/*.rt; do
        if [ -f "$file" ]; then
            # Extract just the filename without the scenes/miniRT_samples/ prefix
            filename=$(basename "$file")
            test_file "miniRT_samples/$filename"
            ((total_files++))
        fi
    done
else
    echo "Error: scenes/miniRT_samples/ directory not found" | tee -a "$RESULTS_FILE"
    exit 1
fi

# Summary
echo "=== TEST SUMMARY ===" | tee -a "$RESULTS_FILE"
echo "Total files tested: $total_files" | tee -a "$RESULTS_FILE"
echo "Correct results: $correct_results" | tee -a "$RESULTS_FILE"
echo "Incorrect results: $incorrect_results" | tee -a "$RESULTS_FILE"
echo "Accuracy: $((correct_results * 100 / total_files))%" | tee -a "$RESULTS_FILE"

if [ $incorrect_results -gt 0 ]; then
    echo | tee -a "$RESULTS_FILE"
    echo "❌ Some tests had incorrect results" | tee -a "$RESULTS_FILE"
    echo "Results saved to: $RESULTS_FILE" | tee -a "$RESULTS_FILE"
    exit 1
else
    echo | tee -a "$RESULTS_FILE"
    echo "✅ All tests had correct results!" | tee -a "$RESULTS_FILE"
    echo "Results saved to: $RESULTS_FILE" | tee -a "$RESULTS_FILE"
    exit 0
fi
