#!/bin/bash

input_file="../F9Test/RandomNeg/input.txt"
output_file="prodF9Neg.txt"
> "$output_file"  # Svuoto file

output=""
file_rows=1000000
num_operands=2

for i in {1..100}; do
    ris=""
    output+="Esecuzione #$i: "
    ris="$(./../f9Operation.out "$input_file" "1000000" "4")"
    echo "Esecuzione: $i -> $ris"
    output+="$ris\n"
done

# Scrivo su file contenuto di output
echo -e "$output" > "$output_file"