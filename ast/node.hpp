#ifndef __NODE_H__
#define __NODE_H__

#include <iostream> 
#include <vector>
#include <string.h> 
#include "../symtab/symtab.hpp"
#include "../global.hpp"

using namespace std;

class Node {
public :
  vector<Node*> son; 
  int lineno = 0;
  Node(int l){
    lineno = l; 
  }
  virtual void addSons(vector<Node*>* n);
  virtual void addSon(Node* n);  
  virtual void print(); 
  virtual ITERTYPE calcType(SymTab* table);  
}; 

class CmdN : public Node {
public: 
  CMDTYPE type; 

  CmdN(CMDTYPE t, int l); 
  void print(); 

}; 

class OpN : public Node{
public : 
  OPTYPE type; 

  OpN(OPTYPE t, int l); 
  ITERTYPE calcType(SymTab* table); 
  void print(); 
}; 

class IdN : public Node{
public: 
  IDTYPE type; 
  char* value; 

  IdN(IDTYPE t, char* s, int l); 
  ITERTYPE calcType(SymTab* table); 
  void print(); 

}; 

class TypeN : public Node{
public: 
  ITERTYPE type;

  TypeN(ITERTYPE t, int l); 
  ITERTYPE calcType(SymTab* table); 
  void print(); 
}; 

class IteralN : public Node{
public: 
  ITERTYPE type; 
	union {
    int ival;
	  char *sval;
    bool bval; 
	}; 

  IteralN(ITERTYPE t, bool value, int l); 
  IteralN(ITERTYPE t, int value, int l);
  IteralN(ITERTYPE t, char* value, int l); 
  ITERTYPE calcType(SymTab* table); 
  void print(); 
}; 

#endif 