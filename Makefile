SHELL = /bin/sh

CC = g++
CFLAGS = -c
OBJS = node.o block.o parser.o scanner.o main.o symnode.o symtab.o global.o 

flower : $(OBJS)
	$(CC) -o flower $(OBJS)

node.o : ast/node.cpp ast/node.hpp global.o 
	$(CC) $(CFLAGS) -o $@ $< 

block.o : ast/block.cpp ast/block.hpp node.o symnode.o symtab.o 
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

symnode.o : symtab/symnode.cpp symtab/symnode.hpp
	$(CC) $(CFLAGS) -o $@ $< 

symtab.o : symtab/symtab.cpp symtab/symtab.hpp symtab/symnode.hpp symtab/symnode.cpp 
	$(CC) $(CFLAGS) -o $@ $< 

main.o : main.cpp node.o block.o parser.o scanner.o symnode.o symtab.o global.o
	$(CC) $(CFLAGS) -o $@ main.cpp

clean :
	rm syntaxTreeParser.c syntaxTreeParser.h scanner.c flower *.o 
