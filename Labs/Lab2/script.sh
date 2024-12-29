#!/bin/bash

yacc -d -y --debug --verbose 20201187.y
echo 'Generated the parser C file as well the header file'
g++ -w -c -o y.o y.tab.c
echo 'Generated the parser object file'
flex 20201187.l
echo 'Generated the scanner C file'
g++ -fpermissive -w -c -o l.o lex.yy.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'
g++ l.o y.o
echo 'All ready, running'
./a.exe input.txt
echo "done"
read -n 1 -s