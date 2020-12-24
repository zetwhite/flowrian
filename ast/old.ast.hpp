#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	B_SEQ, B_IF, B_WHILE, B_CMD, 
	B_DEC_FUNC, B_DEC_VAR, //B means Block
	B_FUNC_BODY, 

	U_PLUS, U_MINUS, 
	ADD, SUB, MUL, DIV, MOD, 
	ASS, GT, LT, EQ, NEQ, 

	T_ID, T_INT, T_STRING, T_FLOAT, T_VOID  //T means terminal 
} N_KIND; 

typedef union{
	int iVal; 
	char* sVal; 
} N_VALUE; 

typedef struct node{
	N_KIND kind; 
	N_VALUE value; 
	struct node* bro; 
	struct node* son; 
} Node; 

Node* makeLeaf(N_KIND kind, N_VALUE value);
Node* makeNode(N_KIND kind);

Node* makeSeq_Leaf(N_KIND under, N_VALUE value); 
Node* makeSeq_Node(N_KIND under); 

void printNode(Node *here, int spaceCnt);
void addSon(Node* parent, Node* son); 
void addBro(Node* origin, Node* bro); 
//void generateCode(Node* here);
#endif
