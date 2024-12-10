#!/bin/bash

input_file="../TestFile/Cifra2/inputTest.txt"
output_file="Cifra2/prodIntV1.txt"
> "$output_file"  # Svuoto file

output=""
file_rows=1000000
num_operands=2

(./../F3Implementation/basicOperation.out "$input_file" "1000000" "2")

# Scrivo su file contenuto di output
echo -e "$output" > "$output_file"

#Media SOMMA V1 :  4.084786666666666 ms  Op su get MSB vecchia (300 volte)
#Media SOMMA V2 :  4.081130000000002 ms OP su get MSB nuova (300 volte)
#Meida SOMMA v3 :  Media:  6.470420000000003 ms op su bool come tipo tra operazioni intermedie

#V = 3.000000
#Media altra strada : Media:  4.868576666666669 ms


#MEDIA F9V1 :
#MEDIA F9V2 :