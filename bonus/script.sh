#!/bin/bash

# Define the parameter values you want to test
restart_values=(100 200 300 400 500)

# Directory containing benchmark instances
instance_dir="/home/deecey/instances"

# Create a directory to store results
mkdir -p results

# Check if the instances directory contains .cnf files
if ! ls "$instance_dir"/*.cnf 1> /dev/null 2>&1; then
    echo "No .cnf files found in $instance_dir"
    exit 1
fi

# Loop through each parameter value and instance
for restartint in "${restart_values[@]}"; do
    for instance in "$instance_dir"/*.cnf; do
        # Extract the instance name without the .cnf extension
        instance_name=$(basename "$instance" .cnf)
        
        # If instance_name is empty, report the issue and exit
        if [ -z "$instance_name" ]; then
            echo "Error: instance_name is empty for file $instance"
            exit 1
        fi
        
        output_file="results/${instance_name}_restart${restartint}.log"
        
        # Debugging output to confirm file processing
        echo "Processing $instance with restartint=$restartint"
        echo "Output will be saved to $output_file"

        # Run CaDiCaL with the chosen parameter, force option, and -- to end options
        ./build/cadical -f --restartint="$restartint" "$instance" > "$output_file"
    done
done

