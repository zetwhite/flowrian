SHELL = /bin/sh

sources = scanner.c syntaxTreeParser.c ast.h ast.c
headers = syntaxTreeParser.h ast.h

#exvalexpr: $(sources)
#	g++ -o $@ $(sources) 

flower : block.o node.o syntaxTreeParser.c syntaxTreeParser.h scanner.c 
	g++ -o syntaxTreeParser.c syntaxTreeParser.h scanner.c 

node.o : ast/node.hpp ast/node.cpp
	g++ -c -o $@ $< 

block.o : ast/block.cpp ast/block.hpp ast/node.hpp 
	g++ -c -o $@ $< 

syntaxTreeParser.c : parser.y
	bison -dy $< -o $@

syntaxTreeParser.h : parser.y
	bison -dy $< -o $@

scanner.c : scanner.l
	flex -o $@ $<

clean :
	rm syntaxTreeParser.c syntaxTreeParser.h scanner.c exvalexpr.exe
