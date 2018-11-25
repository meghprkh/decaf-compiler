parser: parser.ypp scanner.l
		bison -d parser.ypp
		flex scanner.l
		g++ -g -o decaf `llvm-config --cxxflags --ldflags --system-libs --libs all` \
							-fexceptions \
		 					parser.tab.cpp lex.yy.c ast/*.cpp -ll

clean:
		rm -f decaf parser.tab.* lex.yy.c **/*.gch
