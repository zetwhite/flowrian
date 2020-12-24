SHELL = /bin/sh

CC = g++
CFLAGS = -c
OBJS = node.o block.o parser.o scanner.o 
#exvalexpr: $(sources)
#	g++ -o $@ $(sources) 

flower : $(OBJS)
	$(CC) -o flower $(OBJS)

node.o : ast/node.cpp ast/node.hpp
	$(CC) $(CFLAGS) -o $@ $< 

block.o : ast/block.cpp ast/block.hpp 
	$(CC) $(CFLAGS) -o $@ $< 

syntaxTreeParser.c : parser.y
	bison -dy $< -o $@

syntaxTreeParser.h : parser.y
	bison -dy $< -o $@

scanner.c : scanner.l
	flex -o $@ $<

scanner.o : scanner.c 
	$(CC) $(CFLAGS) -o $@ $< 

parser.o : syntaxTreeParser.c syntaxTreeParser.h
	$(CC) $(CFLAGS) -o $@ $< 

clean :
	rm syntaxTreeParser.c syntaxTreeParser.h scanner.c flower node.o block.o scanner.o parser.o 
