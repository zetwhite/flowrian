#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <vector>
#include <string> 
using namespace std; 

typedef enum {CMD, OP, ID, TYPE, ITERAL} NTYPE; 

typedef enum {READ, WRITE, DELETE} CMDTYPE; 
typedef enum {ADD, SUB, MUL, MOD, DIV, GT, LT, GE, LE, EQ, NEQ, UPLUS, UMINUS} OPTYPE; 
typedef enum {FUNCID, VARID} IDTYPE; 
typedef enum {INT, STRING, VOID, BOOL, INVALID} ITERTYPE; 

string toString(ITERTYPE t); 
//vector<Block*> program;
#endif 