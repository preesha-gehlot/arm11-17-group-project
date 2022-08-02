#!/bin/bash
mkdir log/
mkdir log/emulator/
sudo rm log/emulator/*.log

for path in $(find ../testing/test_cases/ -type f ! -name "*.*")
do
    file="$(basename $path .s)"
    valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="log/emulator/$file.log" ../src/emulate "$path"
done
