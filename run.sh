#!/bin/bash

for file in ./data/*
do
    echo "$file:"
    tmp=$(echo "$(basename $file)" | grep -Po -m 1 "(([a-z]|[A-Z])*\d+)")
    mkdir -p ./out/output/${tmp}
    filename="${tmp}_${2}${1}_$(date +"%d-%m@%H:%M:%S:%N")"
    solfilename=${tmp//R/K}

    while IFS= read -r line; do
        
        ./out/knapsack ${1} ${2} "$line" >> ./out/output/${tmp}/${filename}.out   #tasktype(d/e/c) method(0/1/2) knapsack
        
    done < "$file"

    # saving computational errors in the .err file
    awk 'NR==FNR{a[$1]=$3;next}$3!=a[$1]&&a[$1]{print "ID: "$1"   ANSWER: "$3 "   GOT: "a[$1]}' ./out/output/${tmp}/${filename}.out ./solutions/${solfilename}_sol.dat >> ./out/output/${tmp}/${filename}.err
    
    # printing error ratio
    err=$(wc -l < ./out/output/${tmp}/${filename}.err)
    echo "Error ratio: ${err}/$(wc -l < ./out/output/${tmp}/${filename}.out)"
done