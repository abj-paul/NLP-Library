#!/bin/bash
echo "Cleaning and running."
tr 'A-Z' 'a-z' < sed-corpus.txt | tr -sc 'A-Za-z' '\n' | sort | uniq > vocabulary.txt
make clean
make
./run
