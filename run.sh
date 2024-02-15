#!/bin/bash

filename="program"

if [ -x "$filename" ]; then
    rm "$filename"
    echo "removed previous executable '$filename'"
fi

echo "compiling new executable"
g++ -g -O -Wall -std=c++17 src/*.cpp src/data_structures/*.cpp src/io/*.cpp src/io/reader/*.cpp src/io/writer/*.cpp src/timestamp/*.cpp src/schedulers/*.cpp -o $filename

if [[ $? -eq 0 ]]; then
    echo "finished compilation!"
    echo "running program"
    ./program $1
    if [[ $? -eq 0 ]]; then
        echo "Program executed successfully"
    else
        echo "Program execution failed"
    fi 
else
    echo "compilation was unsuccessfull"
fi
