#!/bin/bash

filename="program"

if [ -x "$filename" ]; then
    rm "$filename"
    echo "removed previous executable '$filename'"
fi

echo "compiling new executable"
g++ src/*.cpp src/data_structures/*.cpp -o $filename
echo "finished compilation!"