SHELL = /bin/sh

sources = scanner.c syntaxTreeParser.c node.h node.c
headers = syntaxTreeParser.h node.h

exvalexpr: $(sources)
	g++ -o $@ $(sources) 

node.o : node.cpp node.hpp
	g++ -c -o node.o node.cpp  

syntaxTreeParser.c : parser.y
	bison -dy $< -o $@

syntaxTreeParser.h : parser.y
	bison -dy $< -o $@

scanner.c : scanner.l $(headers)
	flex -o $@ $<

clean :
	rm syntaxTreeParser.c syntaxTreeParser.h scanner.c exvalexpr.exe
