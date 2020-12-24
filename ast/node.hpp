#ifndef __NODE_H__
#define __NODE_H__

#include <iostream> 
#include <vector>
using namespace std;

typedef enum {CMD, OP, ID, TYPE, ITERAL} NTYPE; 

typedef enum {READ, WRITE, CREATE, DELETE} CMDTYPE; 
typedef enum { ADD, SUB, MUL, MOD, DIV, GT, LT, GE, LE, EQ, NEQ, UPLUS, UMINUS} OPTYPE; 
typedef enum {FUNCID, VARID} IDTYPE; 
typedef enum {INT, STRING, VOID, FLOAT} ITERTYPE; 

class Node {
public :
  vector<Node> son; 
  virtual void print(); 
}; 

class CmdN : public Node {
  CMDTYPE type; 
  void print(); 
}; 

class OpN : public Node{
  OPTYPE type; 
  void print(); 
}; 

class IdN : public Node{
  IDTYPE type; 
  void print(); 

}; 

class TypeN : public Node{
  ITERTYPE type;
  void print(); 
}; 

class IteralN : public Node{
  ITERTYPE type; 
	union {
    int ival;
	  char *sval;
	}; 
  void print(); 
}; 

#endif 