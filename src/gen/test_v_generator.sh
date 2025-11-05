#!/bin/bash

# --- Configuration ---
# Exit immediately if a command exits with a non-zero status.
set -e
# Directory containing example rule/seed files
EXAMPLES_DIR="./examples"
# Temporary directory to store test outputs
TEST_OUTPUT_DIR="./v_test_outputs"


# --- Helper Functions ---
function run_test {
    local test_name=$1
    local rules_file=$2
    local seed_file=$3
    local depth=${4:-1} # Default depth is 1 if not provided

    echo "--- Running Test: $test_name ---"

    local output_dir="$TEST_OUTPUT_DIR/$test_name"

    echo "  -> Generating code..."
    ./benchGen $depth "$rules_file" "$seed_file" "$output_dir" array v

    # 2. NEW: Show the complete directory structure for debugging
    #    This is the most important step right now.
    echo "  -> Verifying generated file structure..."
    (cd "$output_dir" && ls -R)

    # 3. Compile the generated program
    echo "  -> Compiling generated program..."
    (cd "$output_dir" && make clean && make)

    # 4. Execute the program
    echo "  -> Executing program..."
    (cd "$output_dir" && ./$test_name)

    echo "  -> Test '$test_name' passed!"
}


# --- Main Script ---

# 1. Initial Setup
echo "--- Setting up test environment ---"
# Compile the main benchGen tool if it doesn't exist
if [ ! -f ./benchGen ]; then
    echo "  -> benchGen not found. Compiling..."
    make
fi
# Clean up previous test runs and create a fresh output directory
rm -rf "$TEST_OUTPUT_DIR"
mkdir -p "$TEST_OUTPUT_DIR"


# 2. Run Targeted Tests for Specific Constructs
echo
echo "========================================="
echo "  Running Targeted Construct Tests"
echo "========================================="
# Create dummy files for targeted tests
echo "" > empty_rules.txt
echo "LOOP(new)" > seed_loop.txt
echo "IF(new, new)" > seed_if.txt
echo "CALL(IF(new, new))" > seed_if_in_call.txt

run_test "single_loop" "empty_rules.txt" "seed_loop.txt"
run_test "single_if" "empty_rules.txt" "seed_if.txt"
run_test "if_in_call" "empty_rules.txt" "seed_if_in_call.txt"

# Clean up dummy files
rm empty_rules.txt seed_loop.txt seed_if.txt seed_if_in_call.txt


# 3. Run All Existing Examples
echo
echo "========================================="
echo "  Running All Examples from '$EXAMPLES_DIR'"
echo "========================================="

for example_dir in "$EXAMPLES_DIR"/ex*; do
    if [ -d "$example_dir" ]; then
        example_name=$(basename "$example_dir")
        rules="$example_dir/production_rule.txt"
        seed="$example_dir/seed_string.txt"
        
        # Check if the required files exist
        if [ -f "$rules" ] && [ -f "$seed" ]; then
            run_test "$example_name" "$rules" "$seed" 1 # Use a higher depth for examples
        else
            echo "  -> Skipping $example_name (missing rule or seed file)."
        fi
    fi
done


# 4. Final Cleanup and Success Message
echo
echo "========================================="
echo "  All V generator tests completed and compiled successfully!"
echo "========================================="
