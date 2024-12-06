flex lex_group8.l
g++ lex.yy.c -o out
./out.exe input.txt
cat output_group8.txt