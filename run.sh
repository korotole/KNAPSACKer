#!/bin/bash

for file in ./data/*
do
    echo "$file"
    tmp=$(echo "$(basename $file)" | grep -Po -m 1 "(([a-z]|[A-Z])*\d+)")
    mkdir -p ./out/output/${tmp}
    filename="${tmp}_${2}${1}_$(date +"%d-%m@%H:%M:%S:%N")"

    while IFS= read -r line; do
        
        ./out/knapsack ${1} ${2} "$line" >> ./out/output/${tmp}/${filename}.out   #tasktype(d/e/c) method(0/1/2) knapsack
        
    done < "$file"
done