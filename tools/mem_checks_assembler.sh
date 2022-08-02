#!/bin/bash
mkdir log/
mkdir log/assembler/
sudo rm log/assembler/*.log
for path in ../testing/test_cases/*.s
do
  file="$(basename $path .s)"
  valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="log/assembler/$file.log" ../src/assemble "$path" "out"
done
rm "out"
