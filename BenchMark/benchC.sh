#!/bin/bash

input_file="../TestFile/Cifra2/inputTest.txt"
output_file="Cifra2/prodBool2.txt"
> "$output_file"  # Svuoto file

output=""
file_rows=1000000
num_operands=2

for i in {1..500}; do
    ris=""
    output+="Esecuzione #$i: "
    ris="$(./../basicOperationBool.out "$input_file" "1000000" "2")"
    echo "Esecuzione: $i -> $ris"
    output+="$ris\n"
done

# Scrivo su file contenuto di output
echo -e "$output" > "$output_file"