#!/bin/bash

# This script refactors the provided code to be non-repetitive
# It uses the exact paths and commands from the original file.

# Loop through examples 0 to 9
for i in {0..9}; do
    echo "ex$i"

    # --- Stage 1: Generate output files for all languages ---
    LANGUAGES=("c" "cpp" "rust" "julia" "go" "v")
    for lang in "${LANGUAGES[@]}"; do
        ./benchGen 3 "examples/ex$i/production_rule.txt" "examples/ex$i/seed_string.txt" "temp_${lang}" "array" "${lang}" > "${lang}_output.txt"
    done

    # --- Stage 2: Compare every unique pair of languages ---
    for (( idx1=0; idx1<${#LANGUAGES[@]}; idx1++ )); do
        for (( idx2=idx1+1; idx2<${#LANGUAGES[@]}; idx2++ )); do
            lang1="${LANGUAGES[$idx1]}"
            lang2="${LANGUAGES[$idx2]}"

            file1="${lang1}_output.txt"
            file2="${lang2}_output.txt"

            # Run the exact diff command from the original script
            diff -q "$file1" "$file2"
        done
    done
done

# --- Final Cleanup ---
rm *_output.txt
rm -rf temp*