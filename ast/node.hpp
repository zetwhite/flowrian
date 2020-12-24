#ifndef __NODE_H__
#define __NODE_H__

#include <iostream> 
#include <vector>
using namespace std;

typedef enum {CMD, OP, ID, TYPE, ITERAL} NTYPE; 

typedef enum {READ, WRITE, CREATE, DELETE} CMDTYPE; 
typedef enum {ADD, SUB, MUL, MOD, DIV, GT, LT, GE, LE, EQ, NEQ, UPLUS, UMINUS} OPTYPE; 
typedef enum {FUNCID, VARID} IDTYPE; 
typedef enum {INT, STRING, VOID, FLOAT} ITERTYPE; 

class Node {
public :
  vector<Node*> son; 
  virtual void addSons(vector<Node*>* n);
  virtual void addSon(Node* n);  
  virtual void print(); 
}; 

class CmdN : public Node {
public: 
  CMDTYPE type; 

  CmdN(CMDTYPE t); 
  void print(); 
}; 

class OpN : public Node{
public : 
  OPTYPE type; 

  OpN(OPTYPE t); 
  void print(); 
}; 

class IdN : public Node{
public: 
  IDTYPE type; 
  char* value; 

  IdN(IDTYPE t, char* s); 
  void print(); 

}; 

class TypeN : public Node{
public: 
  ITERTYPE type;

  TypeN(ITERTYPE t); 
  void print(); 
}; 

class IteralN : public Node{
public: 
  ITERTYPE type; 
	union {
    int ival;
	  char *sval;
	}; 

  IteralN(ITERTYPE t, int value);
  IteralN(ITERTYPE t, char* value); 
  void print(); 
}; 

#endif 