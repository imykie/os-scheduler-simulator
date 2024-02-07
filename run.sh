#!/bin/bash

filename="program"

if [ -x "$filename" ]; then
    rm "$filename"
    echo "removed previous executable '$filename'"
fi

echo "compiling new executable"
g++ -std=c++20 src/*.cpp src/data_structures/*.cpp src/io/*.cpp src/io/reader/*.cpp src/Timestamp/*.cpp src/schedulers/*.cpp  -o $filename
echo "finished compilation!"