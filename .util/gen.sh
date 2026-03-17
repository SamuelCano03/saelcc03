#!/bin/bash

file1="test.cpp"
file2="a.cpp"

bin1=".good"
bin2=".bad"

input_file="tin.txt"

output1="tou.txt"
output2="tou2.txt"

wait_time=0

g++ -o $bin1 $file1
g++ -o $bin2 $file2

generate_input() {
  local N=$((RANDOM % 1 + 1))
  # echo "1" > $input_file
  echo  "$N" > $input_file
  for ((i = 0; i < N; i++)); do
    echo "$((RANDOM % 10 + 1))" >> $input_file
  done
  
}

compare_outputs() {
  diff -q $output1 $output2 > /dev/null
  if [ $? -ne 0 ]; then
    echo "Se encontró una diferencia:"
    echo "Entrada utilizada:"
    cat $input_file
    echo "Salida del primer programa (el bueno):"
    cat $output1
    echo "Salida del segundo programa (el malo):"
    cat $output2
    exit 1
  fi
}

while true; do
  generate_input

    ./$bin1 < $input_file > $output1
    ./$bin2 < $input_file > $output2

    compare_outputs

    sleep $wait_time
  done
