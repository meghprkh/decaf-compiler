parser: parser.y scanner.l
		rm -f parser.output
		bison -vd parser.y
		flex scanner.l
		gcc -o parser parser.tab.c lex.yy.c -ll

clean:
		rm parser parser.output
