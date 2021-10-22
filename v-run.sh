#!/bin/bash

for file in ./data/*
do
    echo "$file"
    tmp=$(echo "$(basename $file)" | grep -Po -m 1 "(([a-z]|[A-Z])*\d+)")
    mkdir -p ./out/output/${tmp}
    filename="${tmp}_${2}${1}_$(date +"%d-%m@%H:%M:%S:%N")"

    while IFS= read -r line; do
        rm -f ./out/valgrind-out.txt

        valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=./out/valgrind-out.txt \
         ./out/knapsack ${1} ${2} "$line" >> ./out/output/${tmp}/${filename}.out   #tasktype method knapsack

        BOLD=`tput bold`

        ERRORS=$(grep -Po -m 1 "ERROR SUMMARY: \d+" ./out/valgrind-out.txt)
        SUCCESS=$(grep -Po -m 1 "\d+" <<< "${ERRORS}")

        if [[ ${SUCCESS} != 0 ]]; then
            echo ${BOLD}${ERRORS}
            if [[ ${ERRORS} == 'ERROR SUMMARY: 1' ]]; then 
                exit 1
            fi
        fi
        
        sleep 2
        
    done < "$file"
done