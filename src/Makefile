parser: parser.ypp scanner.l
		bison -d parser.ypp
		flex scanner.l
		g++ -o decaf parser.tab.cpp lex.yy.c ast/*.cpp -ll

clean:
		rm -f decaf parser.tab.* lex.yy.c **/*.gch
